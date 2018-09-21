/*
 * pool_alloc.h
 *
 */

#ifndef POOL_ALLOC_H_
#define POOL_ALLOC_H_

#include<stdlib.h>
#include<stdbool.h>

struct pool_block{
	size_t size;	//size of the block
	struct pool_block* next;	//pointer to next block
	int free;	// 0 if the block is free, 1 if block is occupied.
 };


// Initialize the pool allocator with a set of block sizes appropriate for this application.
// Returns true on success, false on failure.
bool pool_init(size_t* block_sizes, size_t block_size_count);

// Allocate n bytes. // Returns pointer to allocate memory on success, NULL on failure.
void* pool_malloc(size_t n);

// Release allocation pointed to by ptr.
void pool_free(void* ptr);


#endif /* POOL_ALLOC_H_ */
