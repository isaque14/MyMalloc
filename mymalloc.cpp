#include "myMalloc.hpp"

#include <sys/types.h>
#include <unistd.h>


namespace mymalloc{

    void *base = NULL;

    t_block find_block(t_block *last, size_t size)
    {
        t_block b =(t_block) base;

        while (b && !(b->free && b->size >= size))
        {
            *last = b;
            b = b->next;
        }
        return (b);
    }

    t_block extend_heap(t_block last, size_t s)
    {
        t_block b;
        b = (t_block)sbrk(0);
        if (sbrk(BLOCK_SIZE + s) == (void *)-1)
            /* sbrk fails , go to die */
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
        new_ = (t_block) (b->data + s);
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
            /* First find a block */
            last = (t_block)base;
            b = find_block(&last, s);
            if (b)
            {
                /* can we split */
                if ((b->size - s) >= (BLOCK_SIZE + 4))
                    split_block(b, s);
                b->free = 0;
            }
            else
            {
                /* No fitting block , extend the heap */
                b = extend_heap(last, s);
                if (!b)
                    return (NULL);
            }
        }
        else
        {
            /* first time */
            b = extend_heap(NULL, s);
            if (!b)
                return (NULL);
            base = b;
        }
        return (b->data);
    }
}