#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include <VL53L0X.h>

#define OPEN_THRESHOLD_DISTANCE 500  // mm

namespace esphome {
namespace garagedoor_sensor {

class Garagedoor_sensor : public PollingComponent, public binary_sensor::BinarySensor {
 public:
  //  binary_sensor::BinarySensor *door_status = new binary_sensor::BinarySensor();

  Garagedoor_sensor() : PollingComponent(2000) {}
  void setup() override;
  void on_shutdown() override;
  void update() override;
  void dump_config() override;

 private:
  void initializeSensor();
  VL53L0X sensor;
};

}  // namespace garagedoor_sensor
}  // namespace esphome
