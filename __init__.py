import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.const import (
    CONF_ID,
    CONF_TRIGGER_ID
)
from esphome.core import CORE, coroutine_with_priority

AUTO_LOAD = ['sensor']
MULTI_CONF = True

CONF_HUB_ID = 'garage_custom_door_behavior_id'

garage_custom_door_behv_ns = cg.esphome_ns.namespace('garage_custom_door_behavior')
GarageCustomDoorBehavior = garage_custom_door_behv_ns.class_('GarageCustomDoorBehavior', cg.Component)


CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(GarageCustomDoorBehavior),
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    