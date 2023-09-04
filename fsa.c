/************************************************ 
EXERCISE      : Fixed Size Allocator
Implmented by : Snir Holland
Reviewed by   : Chen Lev-Ron  
Date          : 23/5/2023
File          : fsa.c
*************************************************/

#include <assert.h> /* assert */

#include "fsa.h"

#define WORD_LEN            (sizeof(size_t))
#define INVALID_BLOCK       (0)      

struct fsa
{
	size_t next;   /* address of the next block */		
};

/* Helper funciton to align a memory block */
static size_t AlignBlock(size_t block_size);

/*-------------FSASuggestSize-------------*/
size_t FSASuggestSize(size_t block_size, size_t num_of_blocks)
{	
	assert(block_size > 0);
	assert(num_of_blocks > 0);
	
	block_size = AlignBlock(block_size);
	
	return WORD_LEN + (block_size * num_of_blocks);
}
/*-------------FSAInit-------------*/
fsa_t *FSAInit(void *memory, size_t seg_size, size_t block_size)
{
	/* reserve first bytes for fsa */
	size_t offset = WORD_LEN;
	
	assert(NULL != memory);
	assert(seg_size > block_size);
	assert(0 == (size_t)memory % WORD_LEN); 
	
	block_size = AlignBlock(block_size);
	
	/* store word length in soon to be fsa */
	*(size_t*)memory = WORD_LEN;
	
	/* init the rest of the blocks */
	while(offset < seg_size - block_size)
	{
		*((char*)memory + offset) = offset + block_size;
		offset += block_size; 
	}
	
	/* mark last memory block */
	*((char*)memory + offset) = INVALID_BLOCK;

	return (fsa_t*)memory;
}

/*-------------FSAAlloc-------------*/
void *FSAAlloc(fsa_t *fsa)
{
	void *address = NULL;
	
	assert(NULL != fsa);
	
	/* store address of first free block */
	address = (char*)fsa + fsa->next;
	
	/* update fsa to point to next free block */
	fsa->next = *(size_t *)address;
	
	return address;	
}

/*-------------FSAFree-------------*/
void FSAFree(fsa_t *fsa, void *block)
{	
	assert(NULL != fsa);
	assert(0 == (size_t)block % WORD_LEN);
	
	if (NULL == block)
	{
		return;
	}
	
	*(size_t *)block = fsa->next;
	fsa->next = (size_t)block - (size_t)fsa;
}

/*-------------FSACountFree-------------*/
size_t FSACountFree(const fsa_t *fsa)
{
	size_t count = 0;
	
	size_t *runner = NULL;
	
	assert(NULL != fsa);
	
	/* runner is starting from fsa */
	runner = (size_t *)fsa;
	
	while (INVALID_BLOCK != *runner)
	{
		++count;
		
		/* runner skips between free memory addresses */
		runner = (size_t *)((char *)fsa + *(size_t *)runner);
	}
	
	return count;
}

/* Helper Function: aligns a memory block (rounding up) */
static size_t AlignBlock(size_t block_size)
{
	if (0 != block_size % WORD_LEN)
	{
		block_size = (block_size / WORD_LEN + 1) * WORD_LEN;		 
	}
	
	return block_size;
}


