/*
 * pool_alloc.c
 *      Author: bhara
 */
#include <stdio.h>
#include<stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "pool_alloc.h"
/*I have used a structure (struct pool_block) to hold the information
 * about the blocks and it is also a part of the pool.
It can also be assigned outside the pool.*/

static uint8_t g_pool_heap[65536];
struct pool_block* head = (void*)g_pool_heap;
//printf("%d\n",head);
struct pool_block* last=NULL;

//assuming that the block size count can only be 2.
bool pool_init(size_t* block_sizes, size_t block_size_count) {
	int pool_end_address=(int)head+sizeof(g_pool_heap);
	for(int i=0;i<block_size_count;i++){
		if(block_sizes[i]<0 || block_sizes[i]>sizeof(g_pool_heap)){
			printf("Enter Valid Block Size (size of pool is 65536)\n");
			return false;
		}
	}
/*	I have equally divided the pool for the
	two block sizes and calculated the number of blocks for each block size.*/

	int approx_size1_blocks= (sizeof(g_pool_heap)/2)/block_sizes[0];
	int remaining_pool = sizeof(g_pool_heap);
	struct pool_block* previous=NULL;
	head->size = block_sizes[0];
	head->next= (int)head+(head->size+sizeof(struct pool_block));
	head->free=1;
	struct pool_block* temp=head->next;
	//Initialization of pool for the first block size
	for(int j=1;j<approx_size1_blocks;j++){
		temp->size=block_sizes[0];
		temp->next=(int)temp+(temp->size+sizeof(struct pool_block));
		temp->free=1;
		previous=temp;
		temp=temp->next;
		remaining_pool=remaining_pool-(block_sizes[0]+sizeof(struct pool_block));
	}
	// Initialization of the block for the next block size
	while(temp!=NULL){
		int next_address=(int)temp+(block_sizes[1]+sizeof(struct pool_block));
		if(next_address>=pool_end_address || block_sizes[1]>remaining_pool){
			previous->next=NULL;
			previous->size=pool_end_address-sizeof(struct pool_block)-(int)previous;
			last=previous;
			temp=NULL;
			return true;
		}
		else{
			temp->next=next_address;
			temp->size=block_sizes[1];
			temp->free=1;
			previous=temp;
			temp=temp->next;
			remaining_pool = remaining_pool-(block_sizes[1]+sizeof(struct pool_block));
		}
	}
	return true;
}

void* pool_malloc(size_t n) {
	struct pool_block* temp=head;
	struct pool_block* free_block=NULL;

	//I iterate throughout the pool to find a free space. and return NULL if no free space is found.

	while(temp!=last){
		if(n<=temp->size && temp->free==1){
			free_block=temp;
			free_block++;
			temp->free=0;
			return (void*)free_block;
		}
		else if(temp->next!=last){
				temp=temp->next;
		}
	}
	return (void*)free_block;
}
void pool_free(void* ptr) {
	// Implement me!
	 if(((void*)head>=ptr)&&(ptr<=(head+sizeof(g_pool_heap)))){
		 struct pool_block* block_to_free=ptr;
		 --block_to_free;
		 block_to_free->free=1;
	 }
	 else
		 printf("pointer not valid\n");
}
