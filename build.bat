nasm -f bin boothuguinicompiler.asm -o boot.bin
qemu-system-x86_64 boot.bin