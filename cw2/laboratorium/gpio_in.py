import gpio4
import time

def init_output_pin(pin_no):
    pin = gpio4.SysfsGPIO(pin_no)
    pin.export = True
    pin.direction = 'out'
    pin.value = 0
    return pin

def init_input_pin(pin_no):
    pin = gpio4.SysfsGPIO(pin_no)
    pin.export = True
    pin.direction = 'in'
    return pin

if __name__ == '__main__':
    wait_time = 0.5
    output_pin_number = 27
    input_pin_number = 18
    output_pin = init_output_pin(output_pin_number)
    input_pin = init_input_pin(input_pin_number)
    while True:
        if input_pin.value == 0:
            output_pin.value ^= 1
            time.sleep(wait_time)
    else:
        output_pin.export = False
        input_pin.export = False