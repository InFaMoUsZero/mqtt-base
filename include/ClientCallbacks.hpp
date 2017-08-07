#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "mqtt/callback.h"
#include "Client.hpp"

namespace mqtt
{
    class ClientCallbacks : public mqtt::callback
    {
    public:
        ~ClientCallbacks() override;

        virtual void onConnected() = 0;
        virtual void onConnectionLost(const std::string &reason) = 0;
        virtual void onMessageReceived(const std::string &topic, const std::string &payload) = 0;

        // Callback to indicate that a message was delivered to the server.
        // It is called for a message with a QOS >= 1
        virtual void onMessageSent(const std::string &topic, const std::string &payload) = 0;

        virtual void onReconnectSuccess() = 0;
        virtual void onReconnectFailure() = 0;

    private:
        void connected(const mqtt::string &cause) override;
        void connection_lost(const mqtt::string &cause) override;
        void message_arrived(mqtt::const_message_ptr msg) override;
        void delivery_complete(mqtt::delivery_token_ptr tok) override;
    };
}

#endif //CALLBACKS_H