#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include <VL53L0X.h>

#define OPEN_THRESHOLD_DISTANCE 500  // mm

namespace esphome {
namespace garagedoor_status {

class garagedoor_status : public PollingComponent, public binary_sensor::BinarySensor {
 public:
  garagedoor_status() : PollingComponent(2000) {}
  void setup() override;
  void on_shutdown() override;
  void update() override;
  void dump_config() override;

 private:
  void initializeSensor();
  VL53L0X sensor;
};

}  // namespace garagedoor_status
}  // namespace esphome
