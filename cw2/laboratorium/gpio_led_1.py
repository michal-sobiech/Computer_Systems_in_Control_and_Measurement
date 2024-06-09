import gpio4
import time

led_gpio_no = 27
iteration_count = 10
interval_time = 1

led_pin = gpio4.SysfsGPIO(led_gpio_no)
led_pin.export = True
led_pin.direction = 'out'
led_pin.value = 0

for i in range(iteration_count):
    led_pin.value = 1
    time.sleep(interval_time)
    led_pin.value = 0
    time.sleep(interval_time)

led_pin.export = False