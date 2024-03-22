#include "esphome/core/hal.h"
#include "esphome/core/log.h"
#include "garage_custom_door_behavior.h"

#define MINIMUM_PULSE_WIDTH 800
#define MAXIMUM_PULSE_WIDTH 2500
#define MIN_LONG_PULSE 2000
#define MAX_SHORT_PULSE 1000

namespace esphome {
namespace garage_custom_door_behavior {

static const char *TAG = "GarageCustomDoorBehaviorSensor";

void GarageCustomDoorBehaviorSensor::setup() {
    last_on = 0;
    last_off = millis();
    lastState = false;
}

void GarageCustomDoorBehaviorSensor::loop() {

}

void GarageCustomDoorBehaviorSensor::dump_config(){
    ESP_LOGCONFIG(TAG, "GarageCustomDoorBehaviorSensor");
}

void GarageCustomDoorBehaviorSensor::onTimeout() {
    this->state_callback_.call(lastState ? CLOSED : OPENED);
}

void GarageCustomDoorBehaviorSensor::reportStateChanged(bool newState){
    uint32_t duration = 0;
    if(newState) {
        duration = millis() - last_on;
        last_on = millis();
    }
    else {
        duration = millis() - last_off;
        last_off = millis();
    }

    if((lastState != newState) &&
       ( ( duration > MINIMUM_PULSE_WIDTH) &&
         ( duration < MAXIMUM_PULSE_WIDTH) ))
    {
        if( duration >= MIN_LONG_PULSE )
        {
            this->state_callback_.call(OPENING);
        }
        if( duration <= MAX_SHORT_PULSE )
        {
            this->state_callback_.call(CLOSING);
        }
    }

    lastState = newState;

    this->set_timeout("GarageCustomDoorBehavior", MAXIMUM_PULSE_WIDTH, [this]() { this->onTimeout(); });
}

void GarageCustomDoorBehaviorSensor::add_on_state_callback(std::function<void(GarageDoorState)> &&callback) {
  this->state_callback_.add(std::move(callback));
}


}  // namespace empty_component
}  // namespace esphome