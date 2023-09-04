/************************************************ 
EXERCISE      : Fixed Size Allocator
Implmented by : Snir Holland
Reviewed by   : Chen Lev-Ron  
Date          : 23/5/2023
File          : fsa.h
*************************************************/

#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /* size_t */

typedef struct fsa fsa_t;	/*next free block (part of the pool) */

/*============================================================*/
/*
*	Suggest size fot FSAInit().
*
*	Arguments:
*		block_size - size in Bytes for each block.
*		num_of_blocks - number of blocks.
*
*	Return: recomended size in Bytes for pool.
*
*	Time complexity: O(1) best/average/worst
*	Space complexity: O(1) best/average/worst
*/
size_t FSASuggestSize(size_t block_size, size_t num_of_blocks);

/*
*	Initialized the pool.
*
*	Arguments:
*		memory - the address of the memory to manage - must be valid.
*		seg_size - size in Bytes from FSASuggestSize().
*		block_size - size in Bytes for each block.
*
*	Return:	pointer to the first free address.
*
*	Time complexity: O(n) best/average/worst
*	Space complexity: O(1) best/average/worst
*/
fsa_t *FSAInit(void *memory, size_t seg_size, size_t block_size);

/*
*	Allocate one block of memory.
*
*	Arguments:
*		fsa - pointer to the allocator - must be valid.
*
*	Return:	fsa.
*
*	Time complexity: O(1) best/average/worst
*	Space complexity: O(1) best/average/worst
*/
void *FSAAlloc(fsa_t *fsa);

/*
*	free the current block of memory.
*
*	Arguments:
*		fsa - pointer to the allocator - must be valid.
*		block - block of memory to free - must be valid.
*
*	Return:	void
*
*	Time complexity: O(1) best/average/worst
*	Space complexity: O(1) best/average/worst
*/
void FSAFree(fsa_t *fsa, void *block);

/*
*	cout the number of free blocks.
*
*	Arguments:
*		fsa - pointer to the allocator - must be valid.
*
*	Return:	number of free blocks.
*
*	Time complexity: O(n) best/average/worst
*	Space complexity: O(1) best/average/worst
*/
size_t FSACountFree(const fsa_t *fsa);


#endif   /* __FSA_H__ */


