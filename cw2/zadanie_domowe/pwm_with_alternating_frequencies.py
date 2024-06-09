import sys

def pwm_with_alternating_frequencies(duty_cycle, frequency):
    period = 1/frequency
    on_time = (duty_cycle/100) * period
    off_time = period - on_time
    return (on_time, off_time)

duty_cycle = float(sys.argv[1])
for frequency_arg in sys.argv[2:]:
    frequency = float(frequency_arg)    
    on_time, off_time = pwm_with_alternating_frequencies(duty_cycle, frequency)
    print(f'Frequency: {frequency} Hz, duty cycle: {duty_cycle}, 1: {on_time:.4f} s, 0: {off_time:.4f} s')