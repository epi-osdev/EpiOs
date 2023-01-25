#include "memory/malloc.h"
#include "memory/malloc/sectors.h"
#include "drivers/heap.h"

void *init_malloc(size_t size)
{
    void *heap_start = get_heap_addr();
    header_t *header = (header_t *)heap_start;

    init_block(header, size);
    return header->ptr;
}

void *malloc(size_t size)
{
    size = padding_size(size);
    static uint8_t first_malloc = 1;
    if (first_malloc) {
        first_malloc = 0;
        return init_malloc(size);
    }
    header_t *first_block = get_first_block();
    init_block(first_block, size);
    return first_block->ptr;
}