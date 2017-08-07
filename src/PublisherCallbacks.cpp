#include "PublisherCallbacks.hpp"

void PublisherCallbacks::on_failure(const mqtt::token &asyncActionToken)
{
    this->onPublishFailure();
}

void PublisherCallbacks::on_success(const mqtt::token &asyncActionToken)
{

}