//
// Created by lee on 8/6/17.
//

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "mqtt/callback.h"

namespace mqtt
{
    class Callbacks : public mqtt::callback
    {
    public:
        Callbacks();
        ~Callbacks() override;

        virtual void connected() = 0;
        virtual void connectionLost(const std::string& reason) = 0;
        virtual void messageReceived(const std::string& topic, const std::string& payload) = 0;
        virtual void messageSent(const std::string& topic, const std::string& payload) = 0;

    private:
        void connected(const mqtt::string &cause) override;
        void connection_lost(const mqtt::string &cause) override;
        void message_arrived(mqtt::const_message_ptr msg) override;
        void delivery_complete(mqtt::delivery_token_ptr tok) override;
    };
}

#endif //CALLBACKS_H