#include "myMalloc.hpp"

#include <sys/types.h>
#include <unistd.h>

namespace mymalloc
{

    void *base = NULL;

    t_block find_block(t_block *last, size_t size)
    {
        t_block b = (t_block)base;

        while (b && !(b->free && b->size >= size))
        {
            *last = b;
            b = b->next;
        }
        return (b);
    }

    // t_block find_block(t_block *last, size_t size){

    //     t_block b = (t_block)base;
    //     t_block biggest;
    //     biggest->size = 0;
    //     while (b){
    //         if (b && b->free && (b->size == size))
    //             return b;
    //         if (b && b->free && (b->size > size))
    //             if(b->size > biggest->size)
    //                 biggest = b;

    //         *last = b;
    //         b = b->next;

    //     }
    //     return biggest;
    // }

    t_block extend_heap(t_block last, size_t s)
    {
        t_block b;
        b = (t_block)sbrk(0);
        if (sbrk(BLOCK_SIZE + s) == (void *)-1)
            return (NULL);
        b->size = s;
        b->next = NULL;
        if (last)
            last->next = b;

        b->free = 0;
        return b;
    }

    void split_block(t_block b, size_t s)
    {
        t_block new_;
        new_ = (t_block)(b->data + s);
        new_->size = b->size - s - BLOCK_SIZE;
        new_->next = b->next;
        new_->free = 1;
        b->size = s;
        b->next = new_;
    }

    void *malloc(size_t size)
    {
        t_block b, last;
        size_t s;
        s = align4(size);
        if (base)
        {  
            last = (t_block)base;
            b = find_block(&last, s);
            if (b)
            {
                if ((b->size - s) >= (BLOCK_SIZE + 4))
                    split_block(b, s);
                b->free = 0;
            }
            else
            { 
                b = extend_heap(last, s);
                if (!b)
                    return (NULL);
            }
        }
        else
        { 
            b = extend_heap(NULL, s);
            if (!b)
                return (NULL);
            base = b;
        }
        return (b->data);
    }

    t_block fusion(t_block b)
    {
        if (b->next && b->next->free)
        {
            b->size += BLOCK_SIZE + b->next->size;
            b->next = b->next->next;
            if (b->next)
                b->next->prev = b;
        }
        return (b);
    }

    t_block get_block(void *p)

    {
        char *tmp;
        tmp = (char *)p;
        return (t_block)(p = tmp -= BLOCK_SIZE);
    }

    int valid_addr(void *p)
    {
        if (base)
        {
            if (p > base && p < sbrk(0))
            {
                return (p == (get_block(p))->ptr);
            }
        }
        return (0);
    }

    void free(void *p)
    {
        t_block b;
        if (valid_addr(p))
        {
            b = get_block(p);
            b->free = 1;
          
            if (b->prev && b->prev->free)
                b = fusion(b->prev);
     
            if (b->next)
                fusion(b);
            else
            {
                
                if (b->prev)
                    b->prev->next = NULL;
                else
            
                    base = NULL;
                brk(b);
            }
        }
    }
}