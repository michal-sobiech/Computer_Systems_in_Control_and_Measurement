import sys

def pwm_with_alternating_duty_cycles(duty_cycle, frequency):
    period = 1/float(frequency)
    on_time = (float(duty_cycle)/100) * period
    off_time = period - on_time
    return (on_time, off_time)

frequency = float(sys.argv[1])
for duty_cycle in sys.argv[2:]:
    on_time, off_time = pwm_with_alternating_duty_cycles(duty_cycle, frequency)
    print(f'Frequency: {frequency} Hz, duty cycle: {duty_cycle}%, 1: {on_time:.4f} s, 0: {off_time:.4f} s')