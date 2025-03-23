#include "esphome/core/log.h"
#include "garagedoor_status.h"
#include <Wire.h>
#include <VL53L0X.h>

namespace esphome {
namespace garagedoor_status {

static const char *TAG = "garagedoor.status";

void garagedoor_status::setup() {
  Wire.begin();
  initializeSensor();
}

void garagedoor_status::on_shutdown() { sensor.stopContinuous(); }
void garagedoor_status::on_safe_shutdown() { sensor.stopContinuous(); }

void garagedoor_status::update() {
  unsigned long startTime = millis();
  int dist = sensor.readRangeContinuousMillimeters();
  unsigned long elapsedTime = millis() - startTime;
  ESP_LOGD(TAG, "Elapsed ms: %d ms", elapsedTime);
  if (sensor.timeoutOccurred()) {
    ESP_LOGW(TAG, " TIMEOUT");
    initializeSensor();
  } else {
    ESP_LOGD(TAG, "Distance measured: %d mm", dist);
    bool door_open = dist < dist_mm_;
    publish_state(door_open);
  }
}

void garagedoor_status::dump_config() {
  ESP_LOGCONFIG(TAG, "Garage door sensor:");
  ESP_LOGCONFIG(TAG, "  Signal rate limit: %.2f MCPS", limit_Mcps_);
  ESP_LOGCONFIG(TAG, "  Measuring timing budget: %u microseconds", budget_us_);
  ESP_LOGCONFIG(TAG, "  Threshold distance : %u mm", dist_mm_);
  if (timeout_ > 0)
    ESP_LOGCONFIG(TAG, "  Timeout period: %u milliseconds", timeout_);
  else
    ESP_LOGCONFIG(TAG, "  Timeout period: Disabled");
}

void garagedoor_status::initializeSensor() {
  ESP_LOGD(TAG, "Initializing sensor...");
  if (!sensor.init()) {
    ESP_LOGE(TAG, "Failed to detect and initialize sensor!");
    mark_failed();
  }

  sensor.setTimeout(timeout_);
  timeout_ = sensor.getTimeout();
  if (!sensor.setSignalRateLimit(limit_Mcps_)) {
    ESP_LOGE(TAG, "Failed in call to setSignalRateLimit(%.2f)!", limit_Mcps_);
    mark_failed();
  }
  limit_Mcps_ = sensor.getSignalRateLimit();
  if (!sensor.setMeasurementTimingBudget(budget_us_)) {
    ESP_LOGE(TAG, "Failed in call to setMeasurementTimingBudget! Invalid parameter value: %u mm", budget_us_);
    mark_failed();
  }

  budget_us_ = sensor.getMeasurementTimingBudget();
  sensor.startContinuous();
  ESP_LOGD(TAG, "Initialization finished.");
}

}  // namespace garagedoor_status
}  // namespace esphome
