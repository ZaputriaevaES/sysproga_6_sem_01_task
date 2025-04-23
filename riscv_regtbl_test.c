#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

// riscv64-linux-gnu-gcc -static riscv_regtbl_test.c -o riscv_regtbl_test 

int main() 
{
    syscall(245);
    return 0;
}