#ifndef DEFAULTCALLBACKS_H
#define DEFAULTCALLBACKS_H

#include <iostream>

#include "Callbacks.hpp"

class DefaultCallbacks : public mqtt::Callbacks
{
public:
    DefaultCallbacks();
    ~DefaultCallbacks() override;

    void connected() override;
    void connectionLost(const std::string& reason) override;
    void messageReceived(const std::string& topic, const std::string& payload) override;
    void messageSent(const std::string& topic, const std::string& payload) override;
};

#endif //DEFAULTCALLBACKS_H
