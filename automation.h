#pragma once

#include "esphome/core/defines.h"

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "garage_custom_door_behavior.h"

namespace esphome {
namespace garage_custom_door_behavior {

class GarageDoorStateChangeTrigger : public Trigger<GarageDoorState> {
 public:
  explicit GarageDoorStateChangeTrigger(GarageCustomDoorBehaviorSensor *parent) {
    parent->add_on_state_callback([this, parent](GarageDoorState state) {
        return trigger(state);
    });
  }
};

} // namespace garage_custom_door_behavior
} // namespace esphome