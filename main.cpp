#include "mymalloc.hpp"
#include <cstdio>
#include <cstdlib>
int main(void){
    int* a;

    a = (int*)mymalloc::malloc(20);
    printf("%ld",sizeof(a));


}
