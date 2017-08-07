#include <iostream>
#include <vector>

#include "mqtt/async_client.h"
#include "DefaultCallbacks.hpp"

using namespace std;

const long Timeout = 10000L;

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

// Global subscriber function callback
void onTopicRecieved(const std::string& topic)
{
    switch(str2int(topic.c_str()))
    {
        case str2int("test/topic"):
            cout << "global subscriber function called: test/topic" << endl;
            break;
        case str2int("global/test/topic"):
            cout << "global subscriber function called: global/test/topic" << endl;
            break;
    }
}

int main(int argc, char* argv[])
{
    try
    {
        mqtt::connect_options connOpts;
        connOpts.set_keep_alive_interval(20);
        connOpts.set_clean_session(true);

        Client client(argv[1], std::stoi(argv[2]), "test_00", connOpts, new DefaultCallbacks);

        client.connect()->wait_for(Timeout);

        std::string payload(R"({"Message": "Hello, World!"})");

        client.publish("test/topic", payload, QoS::AtLeastOnce)->wait_for(Timeout);
    }
    catch (const mqtt::exception&)
    {
        cerr << "\nERROR: Unable to connect to MQTT server: '"
                  << argv[1] << ":'" << argv[2] << "'" << endl;

    }

    return 0;
}