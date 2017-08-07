#include "Client.hpp"
#include "ClientCallbacks.hpp"

Client::Client(const std::string& address, int port, const std::string& clientId, mqtt::connect_options& options, mqtt::ClientCallbacks* callbacks)
    : m_connectionOptions(options),
      m_pCallbacks(std::unique_ptr<mqtt::ClientCallbacks>(callbacks)),
      m_serverAddress(address),
      m_serverPort(port),
      m_clientId(clientId),
      m_reconnectInterval(std::chrono::seconds(10))
{
    auto connectionStr = m_serverAddress + ":" + std::to_string(m_serverPort);
    m_pAsyncClient = std::unique_ptr<mqtt::async_client>(new mqtt::async_client(connectionStr, m_clientId));
}

mqtt::token_ptr Client::disconnect()
{
    return m_pAsyncClient->disconnect();
}

mqtt::token_ptr Client::connect()
{
    return m_pAsyncClient->connect(m_connectionOptions, nullptr, *this);
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

void Client::setReconnectInterval(std::chrono::seconds interval)
{
    m_reconnectInterval = interval;
}

mqtt::delivery_token* Client::publish(const std::string &topic, const std::string &payload, int QoS, bool retained)
{
    return m_pAsyncClient->publish(topic, payload.c_str(), payload.size(), QoS, retained).get();
}

const std::chrono::seconds Client::getReconnectInterval()
{
    return m_reconnectInterval;
}

void Client::reconnect()
{
    std::this_thread::sleep_for((this->getReconnectInterval()));

    try
    {
        this->connect();
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Error: " << exc.what() << std::endl;
        exit(1);
    }
}

void Client::on_failure(const mqtt::token &asyncActionToken)
{
    m_pCallbacks->onReconnectFailure();
    this->reconnect();
}

void Client::on_success(const mqtt::token &asyncActionToken)
{
    m_pCallbacks->onReconnectSuccess();
}