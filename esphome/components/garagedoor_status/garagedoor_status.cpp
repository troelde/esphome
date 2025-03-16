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
    bool door_open = dist < OPEN_THRESHOLD_DISTANCE;
    publish_state(door_open);
  }
}

void garagedoor_status::dump_config() {}

void garagedoor_status::initializeSensor() {
  if (!sensor.init()) {
    ESP_LOGE(TAG, "Failed to detect and initialize sensor!");
    mark_failed();
  }

  sensor.setTimeout(30);

  sensor.startContinuous();
}

}  // namespace garagedoor_status
}  // namespace esphome
