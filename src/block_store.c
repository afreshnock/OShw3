#include <stdio.h>
#include <stdint.h>
#include "bitmap.h"
#include "block_store.h"
// include more if you need

// You might find this handy.  I put it around unused parameters, but you should
// remove it before you submit. Just allows things to compile initially.
#define UNUSED(x) (void)(x)

struct block_store{
    uint8_t data[BLOCK_STORE_NUM_BLOCKS];  //pointer to start of block array
    bitmap_t *blockMap;                     //bitmap to store block meta data
};

block_store_t *block_store_create()
{
    // Creates new block initialized to 0
    block_store_t* result = calloc(1, sizeof(block_store_t));

    // Sets bitmap field to overlay BITMAP_SIZE_BLOCKS on BITMAP_START_BLOCK
    result->blockMap = bitmap_overlay(BITMAP_SIZE_BITS, result->data+BITMAP_START_BLOCK);

    // Marks the blocks used by bitmaps
    int bytes = bitmap_get_bytes(result->blockMap);
    for(int i=0; i<bytes; i++){
        if(!block_store_request(result, i+BITMAP_START_BLOCK)) return NULL;
    }

    return result;
}

void block_store_destroy(block_store_t *const bs)
{
    if(bs==NULL) return;
    bitmap_destroy(bs->blockMap);
    free(bs);
}

size_t block_store_allocate(block_store_t *const bs)
{
    //if(bs==NULL) return SIZE_MAX;
    UNUSED(bs);
    return 0;
}

bool block_store_request(block_store_t *const bs, const size_t block_id)
{
    bitmap_t* bitmap = bs->blockMap;

    if(bitmap_test(bitmap, block_id)){
        return false;
    }

    bitmap_set(bitmap, block_id);
    return true;
}

void block_store_release(block_store_t *const bs, const size_t block_id)
{
    UNUSED(bs);
    UNUSED(block_id);
}

size_t block_store_get_used_blocks(const block_store_t *const bs)
{
    UNUSED(bs);
    return 0;
}

size_t block_store_get_free_blocks(const block_store_t *const bs)
{
    UNUSED(bs);
    return 0;
}

size_t block_store_get_total_blocks()
{
    return BLOCK_STORE_NUM_BLOCKS;
}

size_t block_store_read(const block_store_t *const bs, const size_t block_id, void *buffer)
{
    UNUSED(bs);
    UNUSED(block_id);
    UNUSED(buffer);
    return 0;
}

size_t block_store_write(block_store_t *const bs, const size_t block_id, const void *buffer)
{
    UNUSED(bs);
    UNUSED(block_id);
    UNUSED(buffer);
    return 0;
}

block_store_t *block_store_deserialize(const char *const filename)
{
    UNUSED(filename);
    return NULL;
}

size_t block_store_serialize(const block_store_t *const bs, const char *const filename)
{
    UNUSED(bs);
    UNUSED(filename);
    return 0;
}