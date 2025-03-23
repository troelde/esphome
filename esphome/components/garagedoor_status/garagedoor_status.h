#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include <VL53L0X.h>

namespace esphome {
namespace garagedoor_status {

class garagedoor_status : public PollingComponent, public binary_sensor::BinarySensor {
 public:
  garagedoor_status() : PollingComponent(2000) {}
  void setup() override;
  void on_shutdown() override;
  void on_safe_shutdown() override;
  void update() override;
  void dump_config() override;

  void setTimeout(uint16_t timeout) { timeout_ = timeout; }
  void setRateLimit(float limit_Mcps) { limit_Mcps_ = limit_Mcps; }
  void setTimingBudget(uint32_t budget_us) { budget_us_ = budget_us; }
  void setThresholdDistance(uint16_t dist_mm) { dist_mm_ = dist_mm; }

 private:
  void initializeSensor();
  uint16_t timeout_;
  float limit_Mcps_;
  uint32_t budget_us_;
  uint16_t dist_mm_;
  VL53L0X sensor;
};

}  // namespace garagedoor_status
}  // namespace esphome
