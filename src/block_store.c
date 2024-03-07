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
    //int bytes = bitmap_get_bytes(result->blockMap);
    for(size_t i = 0; i < BITMAP_NUM_BLOCKS; i++){
        if(!block_store_request(result, BITMAP_START_BLOCK + i)) return NULL;
    }

    return result;
}

void block_store_destroy(block_store_t *const bs)
{
    if(bs==NULL) return;
    // Frees memory allocated to bitmap and block store
    bitmap_destroy(bs->blockMap);
    free(bs);
}

size_t block_store_allocate(block_store_t *const bs)
{
    if(bs==NULL) return SIZE_MAX;
    // Find index of first free block in block store
    size_t index = bitmap_ffz(bs->blockMap);

    // No free block is available
    if(index == SIZE_MAX) return SIZE_MAX;

    // Mark block as allocated in bitmap
    bitmap_set(bs->blockMap, index);
    return index;
}

bool block_store_request(block_store_t *const bs, const size_t block_id)
{
    // Check if pointer to block store is not NULL and block_id is within range
    if(bs==NULL || block_id > BLOCK_STORE_NUM_BLOCKS) return false;
    bitmap_t* bitmap = bs->blockMap;

    // Checks if block is marked as allocated
    if(bitmap_test(bitmap, block_id)){
        return false;
    }

    // Marks block as allocated
    bitmap_set(bitmap, block_id);
    return true;
}

void block_store_release(block_store_t *const bs, const size_t block_id)
{
    // Check if pointer to block store is not NULL and block_id is within range
    if(bs==NULL || block_id > BLOCK_STORE_NUM_BLOCKS) return;

    // Reset bit corresponding to block in bitmap
    bitmap_reset(bs->blockMap, block_id);
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