import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome import automation
from esphome.const import (
    CONF_ID,
    CONF_TRIGGER_ID,
)
from . import GarageCustomDoorBehavior, CONF_HUB_ID
from esphome.core import CORE, coroutine_with_priority

DEPENDENCIES = ['garage_custom_door_behavior']

# sensor_ns = cg.esphome_ns.namespace('sensor')
# Sensor = sensor_ns.class_('Sensor', sensor.Sensor)

CONF_ON_STATE_CHANGE = "on_state_change"

garage_custom_door_behv_ns = cg.esphome_ns.namespace('garage_custom_door_behavior')

GarageCustomDoorBehaviorSensor = garage_custom_door_behv_ns.class_(
    "GarageCustomDoorBehaviorSensor", cg.Component, sensor.Sensor
)

GarageDoorState = garage_custom_door_behv_ns.enum("GarageDoorState")

GarageDoorStateChangeTrigger = garage_custom_door_behv_ns.class_(
    "GarageDoorStateChangeTrigger", automation.Trigger.template()
)

CONFIG_SCHEMA = cv.All(
    sensor.sensor_schema(GarageCustomDoorBehaviorSensor)
    .extend(cv.COMPONENT_SCHEMA).extend({
        cv.GenerateID(): cv.declare_id(GarageCustomDoorBehaviorSensor),
        cv.GenerateID(CONF_HUB_ID): cv.use_id(GarageCustomDoorBehavior),
        cv.Optional(CONF_ON_STATE_CHANGE): automation.validate_automation(
            {
                cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(GarageDoorStateChangeTrigger),
            }
        ),
    }),
)

@coroutine_with_priority(50.0)
async def to_code(config):
        paren = await cg.get_variable(config[CONF_HUB_ID])
        var = cg.new_Pvariable(config[CONF_ID])
        await sensor.register_sensor(var, config)
        cg.add(paren.register_sensor(var))

        for conf in config.get(CONF_ON_STATE_CHANGE, []):
            trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID], var)
            await automation.build_automation(trigger, [(GarageDoorState, "state")], conf)