#include <iostream>
#include <cstring>

#include "mqtt/async_client.h"

using namespace std;

long Timeout = 10000L;

int main(int argc, char* argv[])
{
    mqtt::async_client client(argv[1], "test_00");

    mqtt::callback cb;
    client.set_callback(cb);

    mqtt::token_ptr connectOk = client.connect();
    cout << "Connecting.." << endl;

    connectOk->wait_for(Timeout);

    cout << "Connection Established!" << endl;

    // Now try with itemized publish.
    const char *payload = "";
    mqtt::token_ptr publishOk = client.publish("test/topic", payload, strlen(payload) + 1, 1, false);
    publishOk->wait_for(Timeout);
    cout << "Payload sent!" << endl;

    return 0;
}
