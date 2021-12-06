#include "../src/mymalloc/mymalloc.hpp"
#include "../src/mymallinfo/mymallinfo.hpp"
#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <malloc.h>

#include <stdlib.h>
#include <string.h>

// teste verifica se o valor alocado eh correto
void alloc_test(int n)
{
    int *integers = (int *)mymalloc::malloc(sizeof(int) * n);
    float *floating = (float *)mymalloc::malloc(sizeof(float) * n);

    for (int i = 1; i <= n; i++)
    {
        integers[i] = n;
        floating[i] = (float)(n + n / 10.0);
    }

    for (int i = 1; i <= n; i++)
    {
        assert(integers[i] == n);
        assert(floating[i] == (float)(n + n / 10.0));
    }
}
// teste verifica se o valor alocado em matrizes eh correto
void matrix_alloc_test(int n, int m)
{
    int **integers = (int **)mymalloc::malloc(sizeof(int *) * n);

    for (int i = 0; i < n; i++)
    {
        integers[i] = (int *)mymalloc::malloc(sizeof(int) * m);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            integers[i][j] = i + j;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            assert(integers[i][j] == i + j);
        }
    }
}

void malloc_free(int n)
{

    void *ptr = sbrk(0);
    int *integers = (int *)mymalloc::malloc(sizeof(int) * n);
    //assert(integers == NULL);

    for (int i = 1; i <= n; i++)
    {
        integers[i] = n;
    }
    void *mid_ptr = sbrk(0);
    assert(integers != NULL);

    mymalloc::free(integers);
    void *end_ptr = sbrk(0);
    assert(ptr == mid_ptr);
}

void display_mallinfo2(void)
{
    struct mymallinfo::mallinfo mi;

    mi = mymallinfo::mallinfo();

    //printf("Total non-mmapped bytes (arena):       %u\n", mi.arena);
    printf("# of free chunks (ordblks):            %u\n", mi.ordblks);
    //printf("# of free fastbin blocks (smblks):     %u\n", mi.smblks);
    //printf("# of mapped regions (hblks):           %u\n", mi.hblks);
    //printf("Bytes in mapped regions (hblkhd):      %u\n", mi.hblkhd);
    //printf("Max. total allocated space (usmblks):  %u\n", mi.usmblks);
    //printf("Free bytes held in fastbins (fsmblks): %u\n", mi.fsmblks);
    printf("Total allocated space (uordblks):      %u\n", mi.uordblks);
    printf("Total free space (fordblks):           %u\n", mi.fordblks);
    printf("Topmost releasable block (keepcost):   %u\n", mi.keepcost);
}

int main(void)
{

    display_mallinfo2();
    printf("\n");

    int* a = (int*)mymalloc::malloc(sizeof(int)*3000);

    display_mallinfo2();
    printf("\n");

    mymalloc::free(a);

    display_mallinfo2();
    printf("\n");



    alloc_test(10000000);
    
   

    matrix_alloc_test(100, 100);

    

    malloc_free(100);

   
}