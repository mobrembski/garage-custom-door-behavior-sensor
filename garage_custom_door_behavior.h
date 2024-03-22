#pragma once

#include "esphome/core/component.h"
#include "esphome/core/component.h"
#include "esphome/core/helpers.h"
#include "esphome/core/defines.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace garage_custom_door_behavior {

enum GarageDoorState { CLOSED = 0, OPENING, CLOSING, OPENED };


class GarageCustomDoorBehavior : public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  void register_sensor(sensor::Sensor *obj) { this->sensors_.push_back(obj); }
 private:
  std::vector<sensor::Sensor *> sensors_;
};

class GarageCustomDoorBehaviorSensor : public Component, public sensor::Sensor {
  public:
   void setup() override;
   void loop() override;
   void dump_config() override;
   void reportStateChanged(bool newState);
   void add_on_state_callback(std::function<void(GarageDoorState)> &&callback);
  private:
   void onTimeout();
   CallbackManager<void(GarageDoorState)> state_callback_{};
   uint32_t last_on;
   uint32_t last_off;
   bool lastState;
};


}  // namespace GarageCustomDoorBehavior
}  // namespace esphome