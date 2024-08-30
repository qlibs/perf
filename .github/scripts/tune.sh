#!/bin/bash

## todo on/off

# Disable CPU Frequency Scaling (apt install cpufrequtils)
sudo cpupower frequency-set --governor performance
# cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

# Disable Address Space Randomization
echo 0 > /proc/sys/kernel/randomize_va_space

# Disable Processor Boosting
echo 0 | sudo tee /sys/devices/system/cpu/cpufreq/boost

# Disable Turbo Mode
echo 1 > /sys/devices/system/cpu/intel_pstate/no_turbo

# Disable Hyperthreading/SMT
echo off | sudo tee /sys/devices/system/cpu/smt/control

# Restrict memory to a single socket
#numactl -m 0 -N 0 ./a.out

# Enable Huge Pages
#sudo numactl --cpunodebind=1 --membind=1 hugeadm --obey-mempolicy --pool-pages-min=1G:64
#sudo hugeadm --create-mounts
