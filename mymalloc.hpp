#pragma once
#include <sys/types.h>
#include <unistd.h>
namespace mymalloc{

    #define align4(x) (((((x)-1) >> 2) << 2) + 4)
    #define BLOCK_SIZE 12

    
    extern void * base;
    typedef struct s_block *t_block;
    struct s_block
    {
        size_t size;
        t_block next;
        int free;
        char data[1];
    };

    int init(size_t);
    void* malloc(size_t);
    bool free(void*);
    void split_block(t_block , size_t );
    t_block extend_heap(t_block , size_t);
    t_block find_block(t_block*, size_t );
}