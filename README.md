# sysproga_6_sem_01_task
## Задание: 
  1. Добавить новый системный вызов в Linux kernel
  2. Добавить новый вызов SBI
  3. Напечатать в приложении значение CSR, полученного по этой цепочке

## Что было сделано:
- В linux kernel (S-mode) добавлен новый syscall **riscv_regtbl** с номером __NR_riscv_regtbl = 245
    - Этот syscall печатаает таблицы GP и CSR регистров
- В OpenSBI (M-mode) добавлен новый sbicall **ecall_csr** с номером SBI_EXT_CSR_DUMP = 0x43535244
    - Этот sbicall возвращает значения CSR регистров

## Внесенные изменения:
- в linux: https://github.com/ZaputriaevaES/linux/compare/master...ZaputriaevaES:linux:new_system_call?expand=1
- в opensbi: https://github.com/ZaputriaevaES/opensbi/compare/master...ZaputriaevaES:opensbi:new_sbi_call?expand=1

## Видео с запуском и работой программы:
![riscv_regtbl c - sysproga_6_sem_01_task  Coder_ ezaputryaeva∕ezaputryaeva-3∕main  - Visual Studio Code 2025-05-04 14-08-45](https://github.com/user-attachments/assets/bc66597c-eaea-4a15-9783-7442f9a4c051)

## Инструкция по установке зависимостей сборке и запуску:
  - компилятор для RISC-V, QEMU и др.:
```
	sudo apt update
	sudo apt install -y libncurses5-dev libncursesw5-dev build-essential \
        git bc bison flex libssl-dev libelf-dev qemu-system-misc gcc-riscv64-linux-gnu \
        gdb-multiarch binutils-riscv64-linux-gnu cpio busybox-static
```
  - Настройка и сборка ядра linux:
```
	[~/sysproga_6_sem_01_task/linux] make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- defconfig
	[~/sysproga_6_sem_01_task/linux] echo "CONFIG_BLK_DEV_INITRD=y" >> .config
	[~/sysproga_6_sem_01_task/linux] make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- -j$(nproc)
```
  - Настройка и сборка opensbi:
```
	[~/sysproga_6_sem_01_task/opensbi] make PLATFORM=generic CROSS_COMPILE=riscv64-linux-gnu- clean 
	[~/sysproga_6_sem_01_task/opensbi] make PLATFORM=generic CROSS_COMPILE=riscv64-linux-gnu- -j$(nproc)
```
  - Сборка BusyBox для initramfs:
```
	[~/sysproga_6_sem_01_task/busybox-1.36.1] make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- defconfig
	[~/sysproga_6_sem_01_task/busybox-1.36.1] make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- menuconfig
	[~/sysproga_6_sem_01_task/busybox-1.36.1] (Settings → Build static binary (no shared libs) → [X])
	[~/sysproga_6_sem_01_task/busybox-1.36.1] make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- -j$(nproc)
	[~/sysproga_6_sem_01_task/busybox-1.36.1] make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- install
```
  - Компиляция теста:
```
	[~/sysproga_6_sem_01_task] riscv64-linux-gnu-gcc -static riscv_regtbl_test.c -o riscv_regtbl_test  
	[~/sysproga_6_sem_01_task] sudo cp riscv_regtbl_test busybox-1.36.1/_install/riscv_regtbl_test
```
  - Создание initramfs:
```
	[~/sysproga_6_sem_01_task/busybox-1.36.1/_install] find . | cpio -o -H newc > ../rootfs.cpio
```
  - Запуск QEMU:
```
	[~/sysproga_6_sem_01_task]     
        qemu-system-riscv64 \
        -M virt \
        -cpu rv64 \
        -nographic \
        -bios opensbi/build/platform/generic/firmware/fw_dynamic.bin \
        -kernel linux/arch/riscv/boot/Image \
        -initrd busybox-1.36.1/rootfs.cpio \
        -append "root=/dev/ram rdinit=/init console=ttyS0"
```
  - Запуск теста внутри QEMU:
```
	./riscv_regtbl_test
```
