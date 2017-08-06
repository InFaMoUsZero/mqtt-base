//
// Created by lee on 8/6/17.
//

#include "Callbacks.hpp"

mqtt::Callbacks::Callbacks()
{

}

mqtt::Callbacks::~Callbacks() = default;

void mqtt::Callbacks::connected(const mqtt::string &cause)
{
    this->connected();
}

void mqtt::Callbacks::connection_lost(const mqtt::string &cause)
{
    this->connectionLost(cause);
}

void mqtt::Callbacks::message_arrived(mqtt::const_message_ptr msg)
{
    const auto& topic = msg->get_topic();
    const auto& message = msg->get_payload();

    this->messageReceived(topic, message);
}

void mqtt::Callbacks::delivery_complete(mqtt::delivery_token_ptr tok)
{
    const auto message = tok->get_message();
    const auto& topic = message->get_topic();
    const auto& payload = message->get_payload();

    this->messageSent(topic, payload);
}
