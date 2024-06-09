import gpio4
import math
import time


def init_pin(gpio_no):
    pin = gpio4.SysfsGPIO(gpio_no)
    pin.export = True
    pin.direction = 'out'
    pin.value = 0
    return pin

def generate_pwm_signal(duty_cycle, period, pin):
    on_time = duty_cycle * period
    off_time = period - on_time
    pin.value = 1
    time.sleep(on_time)
    pin.value = 0
    time.sleep(off_time)

def generate_sin_signal(frequency, time, pin):
    ticks_per_s = 100
    tick_length = 1/ticks_per_s
    for tick_no in range(int(time * ticks_per_s)):
        intensity = (math.sin(frequency * tick_no * tick_length) + 1) / 2
        generate_pwm_signal(intensity, tick_length, pin)

if __name__ == '__main__':
    gpio_no = 27
    frequency = 3
    time_of_working = 10
    pin = init_pin(gpio_no)
    generate_sin_signal(frequency, time_of_working, pin)
    pin.export = False