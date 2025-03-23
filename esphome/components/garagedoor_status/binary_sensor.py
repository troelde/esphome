import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import CONF_TIMEOUT, DEVICE_CLASS_GARAGE_DOOR

CONF_RATE_LIMIT = "rate_limit"
CONF_TIMING_BUDGET = "timing_budget_us"
CONF_THRESHOLD_DISTANCE_MM = "threshold_distance_mm"

garagedoor_sensor_ns = cg.esphome_ns.namespace("garagedoor_status")
garagedoor_sensor_Component = garagedoor_sensor_ns.class_(
    "garagedoor_status", cg.PollingComponent, binary_sensor.BinarySensor
)

CONFIG_SCHEMA = (
    binary_sensor.binary_sensor_schema(
        garagedoor_sensor_Component, device_class=DEVICE_CLASS_GARAGE_DOOR
    )
    .extend(
        {
            cv.Optional(CONF_TIMEOUT, default=0): cv.int_range(min=0),
            cv.Optional(CONF_RATE_LIMIT, default=0.5): cv.float_range(min=0, max=1),
            cv.Optional(CONF_TIMING_BUDGET, default=100000): cv.int_range(min=0),
            cv.Optional(CONF_THRESHOLD_DISTANCE_MM, default=500): cv.int_,
        }
    )
    .extend(cv.polling_component_schema("60s"))
)


async def to_code(config):
    var = await binary_sensor.new_binary_sensor(config)
    await cg.register_component(var, config)
    cg.add(var.setTimeout(config[CONF_TIMEOUT]))
    cg.add(var.setRateLimit(config[CONF_RATE_LIMIT]))
    cg.add(var.setTimingBudget(config[CONF_TIMING_BUDGET]))
    cg.add(var.setThresholdDistance(config[CONF_THRESHOLD_DISTANCE_MM]))
