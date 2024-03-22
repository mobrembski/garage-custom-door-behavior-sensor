#include "esphome/core/hal.h"
#include "esphome/core/log.h"
#include "garage_custom_door_behavior.h"

namespace esphome {
namespace garage_custom_door_behavior {

static const char *TAG = "GarageCustomDoorBehavior";


void GarageCustomDoorBehavior::setup() {

}

void GarageCustomDoorBehavior::loop() {

}

void GarageCustomDoorBehavior::dump_config(){
    ESP_LOGCONFIG(TAG, "GarageCustomDoorBehavior");
}

}  // namespace empty_component
}  // namespace esphome