#include <iostream>
#include <vector>

#include "mqtt/async_client.h"

#include "DefaultCallbacks.hpp"

using namespace std;

const long Timeout = 10000L;

int main(int argc, char* argv[])
{
    mqtt::async_client client(argv[1], "test_00");

    DefaultCallbacks dcb;
    client.set_callback(dcb);

    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);

    client.connect(connOpts)->wait_for(Timeout);

    std::string payload(R"({"Message": "Hello, World!"})");

   client.publish("test/topic", payload.c_str(), payload.size(), 1, false)->wait_for(Timeout);

    return 0;
}