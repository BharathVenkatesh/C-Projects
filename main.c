/*
 * main.c
 *
 *  Created on: Sep 20, 2018
 *      Author: bhara
 */

#ifndef MAIN_C_
#define MAIN_C_

#include <stdio.h>
#include<stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "pool_alloc.h"


int main(void){
	size_t block_sizes[2]={4096, 2048};
	int block_size_count=2;
	if(block_size_count>2){
		printf("There can only be two different block sizes");
		return 0;
	}
	pool_init(block_sizes,block_size_count);
	//printf("%d\n", x);
	int* block1=(int*)pool_malloc(2040);
	printf("%p\n",block1);
	return 0;
}


#endif /* MAIN_C_ */
