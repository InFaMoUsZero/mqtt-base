#include "ClientCallbacks.hpp"

mqtt::ClientCallbacks::~ClientCallbacks() = default;

void mqtt::ClientCallbacks::connected(const mqtt::string &cause)
{
    this->onConnected();
}

void mqtt::ClientCallbacks::connection_lost(const mqtt::string &cause)
{
    this->onConnectionLost(cause);
}

void mqtt::ClientCallbacks::message_arrived(mqtt::const_message_ptr msg)
{
    const auto& topic = msg->get_topic();
    const auto& message = msg->get_payload();

    this->onMessageReceived(topic, message);
}

void mqtt::ClientCallbacks::delivery_complete(mqtt::delivery_token_ptr tok)
{
    const auto message = tok->get_message();
    const auto& topic = message->get_topic();
    const auto& payload = message->get_payload();

    this->onMessageSent(topic, payload);
}
