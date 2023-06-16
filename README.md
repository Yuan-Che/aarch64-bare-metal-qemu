# aarch64-bare-metal-qemu
simple aarch64 bare metal 'Hello World' on qemu

```shell
qemu-system-aarch64 -M phytium-board -nographic -semihosting -kernel test64.elf -rtc clock=vm -S -s
```

To debug the program:
```shell
gdb-multiarch -q -ex 'file test64.elf' -ex 'target remote localhost:1234'
# To test whether the timer is independent from the host.
b test64.c:100
c
```