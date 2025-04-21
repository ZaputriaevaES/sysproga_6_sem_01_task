# sysproga_6_sem_01_task
Задание: 
  1. Добавить новый системный вызов в Linux kernel
  2. Добавить новый вызов SBI
  3. Напечатать в приложении значение CSR, полученного по этой цепочке

Установленные зависимости:
  - компилятор для RISC-V, QEMU и др.
```
sudo apt install -y build-essential git bc bison flex libssl-dev libelf-dev \
qemu-system-misc gcc-riscv64-linux-gnu gdb-multiarch
```
  - исходники ядра Linux для RISC-V
```
git clone https://github.com/torvalds/linux.git
cd linux
git checkout v6.6
make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- defconfig
```
