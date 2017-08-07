#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "mqtt/async_client.h"

// Forward declarations
namespace mqtt
{
    class ClientCallbacks;
    class delivery_token;
}

enum QoS
{
    AtMostOnce = 0,
    AtLeastOnce = 1,
    ExactlyOnce = 2
};

class Client : public virtual mqtt::iaction_listener
{
public:
    Client(const std::string& address, int port, const std::string& clientId,
           const mqtt::connect_options& options, void* callbacks = nullptr);

    mqtt::token_ptr connect();
    mqtt::token_ptr disconnect();

    mqtt::delivery_token* publish(const std::string& topic, const std::string& payload,
                                  QoS quality, bool retained = false);

    // Getters
    const mqtt::connect_options& getOptions();
    const std::string& getServerAddress();
    const std::string& getClientId();
    const int getServerPort();
    const std::chrono::seconds& getReconnectInterval();

    // Setters
    void setReconnectInterval(const std::chrono::seconds& interval);

private:
    void reconnect();

    // Reconnect listener callbacks
    void on_failure(const mqtt::token &asyncActionToken) override;
    void on_success(const mqtt::token &asyncActionToken) override;

private:
    std::unique_ptr<mqtt::async_client> m_pAsyncClient;
    std::unique_ptr<mqtt::ClientCallbacks> m_pClientCallbacks;

    mqtt::connect_options m_connectionOptions;
    std::string m_serverAddress;
    int m_serverPort;
    std::chrono::seconds m_reconnectInterval;
    std::string m_clientId;
};

#endif //CLIENT_HPP
