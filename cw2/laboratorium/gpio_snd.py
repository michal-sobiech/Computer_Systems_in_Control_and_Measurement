import gpio4
import time

def init_output_pin(gpio_no):
    pin = gpio4.SysfsGPIO(gpio_no)
    pin.export = True
    pin.direction = 'out'
    return pin

def generate_note_pwm(duty_cycle, note_time, frequency, pin):
    period = 1/frequency
    start_time = time.time()
    while True:
        time_elapsed = time.time() - start_time
        if time_elapsed + period > note_time:
            return
        generate_pwm_signal(duty_cycle, period, pin)

def generate_pwm_signal(duty_cycle, period, pin):
    on_time = duty_cycle * period
    off_time = period - on_time
    pin.value = 1
    time.sleep(on_time)
    pin.value = 0
    time.sleep(off_time)

if __name__ == '__main__':
    key_frequencies = [
        65.41,
        73.42,
        82.41,
        87.31,
        98.00,
        110.00,
        123.47,
        130.81,
        146.83,
        164.81,
        174.61,
        196.00,
        220.00,
        246.94
    ]
    key_frequencies_next_octave = [4 * f for f in key_frequencies]
    output_pin_no = 27
    key_time = 0.25
    duty_cycle = 0.5
    output_pin = init_output_pin(output_pin_no)

    for f in key_frequencies + key_frequencies_next_octave:
        generate_note_pwm(duty_cycle, key_time, f, output_pin)