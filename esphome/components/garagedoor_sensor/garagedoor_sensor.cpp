#include "esphome/core/log.h"
#include "garagedoor_sensor.h"
#include <Wire.h>
#include <VL53L0X.h>

namespace esphome {
namespace garagedoor_sensor {

static const char *TAG = "garagedoor.sensor";

void Garagedoor_sensor::setup() {
  // door_status->set_device_class("garage_door");
  // set_device_class("garage_door");
  Wire.begin();
  initializeSensor();
}

void Garagedoor_sensor::on_shutdown() {}

void Garagedoor_sensor::update() {
  int dist = sensor.readRangeSingleMillimeters();
  if (sensor.timeoutOccurred()) {
    ESP_LOGW(TAG, " TIMEOUT");
    initializeSensor();
  } else if (dist == 255) {  // Error condition
    ESP_LOGW(TAG, "'255' condition");
    initializeSensor();
  } else {
    // distance_sensor->publish_state(dist);
    ESP_LOGD(TAG, "Distance measured: %d mm", dist);
    bool door_open = dist < OPEN_THRESHOLD_DISTANCE;
    // door_status->publish_state(door_open);
    publish_state(door_open);
  }
}

void Garagedoor_sensor::dump_config() {}

void Garagedoor_sensor::initializeSensor() {
  sensor.setTimeout(500);
  if (!sensor.init()) {
    ESP_LOGE(TAG, "Failed to detect and initialize sensor!");
    mark_failed();
  }

  // increase timing budget to 200 ms
  sensor.setMeasurementTimingBudget(200000);
}

}  // namespace garagedoor_sensor
}  // namespace esphome
