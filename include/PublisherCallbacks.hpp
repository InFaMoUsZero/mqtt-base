#ifndef PUBLISHERCALLBACKS_HPP
#define PUBLISHERCALLBACKS_HPP

#include <mqtt/iaction_listener.h>

class PublisherCallbacks : public mqtt::iaction_listener
{
public:
    virtual void onPublishSuccess() = 0;
    virtual void onPublishFailure() = 0;

private:
    void on_failure(const mqtt::token &asyncActionToken) override;
    void on_success(const mqtt::token &asyncActionToken) override;

};

#endif //PUBLISHERCALLBACKS_HPP
