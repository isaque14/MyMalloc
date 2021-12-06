#include "mymalloc.hpp"
#include <cstdio>
#include <cstdlib>
int main(void){
    int* a;

     a = (int*)mymalloc::malloc(sizeof(int)*30);
    a[22] =1;
    printf("%d",a[22]);

    mymalloc::free(a);

    printf("%d",a[22]);

}

