#include <iostream>

#include "DefaultCallbacks.hpp"

using namespace std;

DefaultCallbacks::~DefaultCallbacks() = default;

void DefaultCallbacks::onConnected()
{
    cout << "Connection successful!" << endl;
}

void DefaultCallbacks::onConnectionLost(const std::string &reason)
{
    cout << "Connection lost!" << endl;
}

void DefaultCallbacks::onMessageReceived(const std::string &topic, const std::string &payload)
{
    cout << "Message received:\n\t Topic: " << topic << ":\n\t Message: " << payload <<  endl;
}

void DefaultCallbacks::onMessageSent(const std::string &topic, const std::string &payload)
{
    cout << "Message sent:\n\t Topic: " << topic << ":\n\t Message: " << payload <<  endl;
}

void DefaultCallbacks::onPublishSuccess()
{
    cout << "Message published successfully" <<  endl;
}

void DefaultCallbacks::onPublishFailure()
{
    cout << "Message publish failed" <<  endl;
}

void DefaultCallbacks::onReconnectSuccess()
{

}

void DefaultCallbacks::onReconnectFailure()
{

}
