#include <PublisherCallbacks.hpp>
#include "Client.hpp"
#include "ClientCallbacks.hpp"

Client::Client(const std::string& address, int port, const std::string& clientId,
               const mqtt::connect_options& options, void* callbacks)
    : m_connectionOptions(options),
      m_pClientCallbacks(static_cast<mqtt::ClientCallbacks*>(callbacks)),
      m_serverAddress(address),
      m_serverPort(port),
      m_clientId(clientId),
      m_reconnectInterval(std::chrono::seconds(10))
{
    auto connectionStr = m_serverAddress + ":" + std::to_string(m_serverPort);
    m_pAsyncClient = std::make_unique<mqtt::async_client>(connectionStr, m_clientId);
    m_pAsyncClient->set_callback(*m_pClientCallbacks);
}

mqtt::token_ptr Client::disconnect()
{
    return m_pAsyncClient->disconnect();
}

mqtt::token_ptr Client::connect()
{
    return m_pAsyncClient->connect(m_connectionOptions);
}

const mqtt::connect_options &Client::getOptions()
{
    return m_connectionOptions;
}

const std::string &Client::getServerAddress()
{
    return m_serverAddress;
}

const std::string &Client::getClientId()
{
    return m_clientId;
}

const int Client::getServerPort()
{
    return m_serverPort;
}

void Client::setReconnectInterval(const std::chrono::seconds& interval)
{
    m_reconnectInterval = interval;
}

mqtt::delivery_token* Client::publish(const std::string &topic, const std::string &payload,
                                      QoS quality, bool retained)
{
    m_pAsyncClient->publish(topic,
                            payload.c_str(),
                            payload.size(),
                            quality,
                            retained)->wait_for(10000L);

    if(quality == QoS::AtMostOnce)
        m_pClientCallbacks->onMessageSent(topic, payload);
}

const std::chrono::seconds& Client::getReconnectInterval()
{
    return m_reconnectInterval;
}

void Client::reconnect()
{
    std::this_thread::sleep_for((this->getReconnectInterval()));

    try
    {
        m_pAsyncClient->connect(m_connectionOptions, nullptr, *this);
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Error: " << exc.what() << std::endl;
        exit(1);
    }
}

void Client::on_failure(const mqtt::token &asyncActionToken)
{
    m_pClientCallbacks->onReconnectFailure();
    this->reconnect();
}

void Client::on_success(const mqtt::token &asyncActionToken)
{
    m_pClientCallbacks->onReconnectSuccess();
}