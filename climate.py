import esphome.codegen as cg
import esphome.config_validation as cv

from esphome.components import climate_ir
from esphome.components import sensor

AUTO_LOAD = ["climate_ir"]

CONF_TEMPERATURE_SENSOR = "temperature_sensor"

ayce_ns = cg.esphome_ns.namespace("ayce")

AyceClimate = ayce_ns.class_(
    "AyceClimate",
    climate_ir.ClimateIR,
)

CONFIG_SCHEMA = climate_ir.climate_ir_with_receiver_schema(
    AyceClimate
).extend(
    {
        cv.Optional(CONF_TEMPERATURE_SENSOR):
            cv.use_id(sensor.Sensor),
    }
)

async def to_code(config):
    var = await climate_ir.new_climate_ir(config)

    if CONF_TEMPERATURE_SENSOR in config:
        sens = await cg.get_variable(
            config[CONF_TEMPERATURE_SENSOR]
        )
        cg.add(
            var.set_temperature_sensor(sens)
        )
