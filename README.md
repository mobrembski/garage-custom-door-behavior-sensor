# Garage-Custom-Door-Behavior ESPHome component
## Background
I had an Bennica garage door controller. This controller has an ability to be externally controlled by 2 inputs - one for opening door, and second one for closing door.

But problem with this controller is with outputs. It has one "Warning light" output which has 4 states:
- Turned on all the time when door is closed.
- Turned off all the time when door is open.
- Blinking fast (1s) when it is opening.
- Blinking slowly (2s) when it is closing.

Since i dont find an easy way how to integrate this output into ***Template cover*** component in ESPHome, i've wrote this customized one.

## Configuration:
Add component to folder *my_components* . Then use following config:

    external_components:
      - source:
          type: local
          path: my_components
    ...
    garage_custom_door_behavior:
      id: garage_custom_door_behv
    ...
    cover:
      - platform: template
        device_class: garage
        id: left_gate_cover
        name: "Left Gate"
    
    sensor:
      - platform: garage_custom_door_behavior
        name: Test
        garage_custom_door_behavior_id: garage_custom_door_behv
        id: garage_custom_door_behv_left
        on_state_change:
          - logger.log:
              format: "Left Garage door state change: %d"
              args: [ 'state' ]
          - lambda: |-
              switch(state)
              {
                case 0:
                {
                  id(left_gate_cover).position = COVER_CLOSED;
                  id(left_gate_cover).current_operation = COVER_OPERATION_IDLE;
                  break;
                }
                case 1:
                {
                  id(left_gate_cover).position = COVER_CLOSED;
                  id(left_gate_cover).current_operation = COVER_OPERATION_OPENING;
                  break;
                }
                case 2:
                {
                  id(left_gate_cover).position = COVER_OPEN;
                  id(left_gate_cover).current_operation = COVER_OPERATION_CLOSING;
                  break;
                }
                case 3:
                {
                  id(left_gate_cover).position = COVER_OPEN;
                  id(left_gate_cover).current_operation = COVER_OPERATION_IDLE;
                  break;
                }
              }
              id(left_gate_cover).publish_state();
    binary_sensors:
        - platform: gpio
        name: "Left Gate State"
        id: left_gate_state
        pin: 3
        filters:
         - delayed_on_off: 50ms
        on_press:
        - lambda: 'id(garage_custom_door_behv_left).reportStateChanged(true);'
        on_release:
        - lambda: 'id(garage_custom_door_behv_left).reportStateChanged(false);'

## Customization
You can open ***garage_custom_door_behavior_sensor.cpp*** and fix consts there if they're better suits you:
    #define MINIMUM_PULSE_WIDTH 800
    #define MAXIMUM_PULSE_WIDTH 2500
    #define MIN_LONG_PULSE 2000
    #define MAX_SHORT_PULSE 1000