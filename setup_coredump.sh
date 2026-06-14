#!/bin/bash

# Allow unlimited core dump size
ulimit -c unlimited

# Set core dump directory
mkdir -p /tmp/coredumps
echo '/tmp/coredumps/core.%e.%p' | sudo tee /proc/sys/kernel/core_pattern

echo "Core dump setup complete. Core dumps will be stored in /tmp/coredumps/"
