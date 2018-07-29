#!/usr/bin/env bash
qemu-system-aarch64 -M virt -cpu cortex-a57 -nographic -kernel test64.elf -S -s &
gdb-multiarch -q -ex 'file test64.elf' -ex 'target remote localhost:1234'
kill %1
