#include <iostream>

#include "DefaultCallbacks.hpp"

using namespace std;

DefaultCallbacks::DefaultCallbacks() = default;
DefaultCallbacks::~DefaultCallbacks() = default;

void DefaultCallbacks::connected()
{
    cout << "Connection successful!" << endl;
}

void DefaultCallbacks::connectionLost(const std::string& reason)
{
    cout << "Connection lost!" << endl;
}

void DefaultCallbacks::messageReceived(const std::string& topic, const std::string& payload)
{
    cout << "Message received:\n\t Topic: " << topic << ":\n\t Message: " << payload <<  endl;
}

void DefaultCallbacks::messageSent(const std::string& topic, const std::string& payload)
{
    cout << "Message sent:\n\t Topic: " << topic << ":\n\t Message: " << payload <<  endl;
}