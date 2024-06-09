import gpio4
import time

def init_input_pin(gpio_no):
    pin = gpio4.SysfsGPIO(gpio_no)
    pin.export = True
    pin.direction = 'in'
    return pin

def init_output_pin(gpio_no):
    pin = gpio4.SysfsGPIO(gpio_no)
    pin.export = True
    pin.direction = 'out'
    pin.value = 0
    return pin

def measure_distance(trig_pin, echo_pin, sound_speed):
    trig_pin.value = 1
    start_time = time.time()
    time.sleep(0.001)
    trig_pin.value = 0

    end_time = None
    while True:
        if echo_pin.value == 1:
            end_time = time.time()
            break

    time_elapsed = end_time - start_time

    distance = time_elapsed * sound_speed / 2
    return distance

if __name__ == '__main__':
    speed_of_sound = 343
    echo_gpio_np = 27
    trig_gpio_no = 26

    trig_pin = init_output_pin(trig_gpio_no)
    echo_pin = init_input_pin(echo_gpio_np)
    
    while True:
        print(measure_distance(trig_pin, echo_pin, speed_of_sound))