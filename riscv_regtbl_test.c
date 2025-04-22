#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

// riscv64-linux-gnu-gcc -static riscv_regtbl_test.c -o riscv_regtbl_test 

int main() 
{
    long ret = syscall(245);  // Номер вашего syscall
    printf("CSR_TIME: %ld\n", ret);
    return 0;
}