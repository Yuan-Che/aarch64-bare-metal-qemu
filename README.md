# aarch64-bare-metal-qemu
simple aarch64 bare metal 'Hello World' on qemu

```shell
qemu-system-aarch64 -M phytium-board -nographic -semihosting -kernel test64.elf
```