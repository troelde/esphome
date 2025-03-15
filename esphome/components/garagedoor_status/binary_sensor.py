import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import DEVICE_CLASS_GARAGE_DOOR

garagedoor_sensor_ns = cg.esphome_ns.namespace("garagedoor_status")
garagedoor_sensor_Component = garagedoor_sensor_ns.class_(
    "garagedoor_status", cg.PollingComponent, binary_sensor.BinarySensor
)

CONFIG_SCHEMA = binary_sensor.binary_sensor_schema(
    garagedoor_sensor_Component, device_class=DEVICE_CLASS_GARAGE_DOOR
).extend(cv.polling_component_schema("60s"))


async def to_code(config):
    var = await binary_sensor.new_binary_sensor(config)
    await cg.register_component(var, config)


#     var = cg.new_Pvariable(config[CONF_ID])
#    cg.add(var.set_temperature(sens))
