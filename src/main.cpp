#include <iostream>
#include <vector>

#include "mqtt/async_client.h"
#include "DefaultCallbacks.hpp"

using namespace std;

const long Timeout = 10000L;

int main(int argc, char* argv[])
{
    try
    {
        DefaultCallbacks defaultCallbacks;

        mqtt::connect_options connOpts;
        connOpts.set_keep_alive_interval(20);
        connOpts.set_clean_session(true);

        Client client(argv[1], std::stoi(argv[2]), "test_00", connOpts, &defaultCallbacks);

        client.connect()->wait_for(Timeout);

        std::string payload(R"({"Message": "Hello, World!"})");

        client.publish("test/topic", payload, 1)->wait_for(Timeout);
    }
    catch (const mqtt::exception&)
    {
        std::cerr << "\nERROR: Unable to connect to MQTT server: '"
                  << argv[1] << "'" << std::endl;
        return 1;
    }

    return 0;
}