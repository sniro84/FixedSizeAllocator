/************************************************ 
EXERCISE      : Fixed Size Allocator
Implmented by : Snir Holland
Reviewed by   : Chen Lev-Ron    
Date          : 23/5/2023
File          : fsa_test.c
*************************************************/

#include "fsa.h"
#include <stdio.h>
#include <stdlib.h>


/* Test Functions */
static void TestFSASuggestSize();
static void TestFSAInit();
static void TestFSAAlloc();
static void TestFSAFree();
static void TestFSACountFree();

int main()
{
	TestFSASuggestSize();
	
	TestFSAInit();
	
	TestFSAAlloc();
	
	TestFSAFree();
	
	TestFSACountFree();
		
	return(0);
}

/*-------------TestFSASuggestSize-------------*/
static void TestFSASuggestSize()
{
	size_t test_count = 3;
	
	(88 == FSASuggestSize(5,10)) ? --test_count : test_count;
	(56 == FSASuggestSize(16,3)) ? --test_count : test_count;
	(104 == FSASuggestSize(17,4)) ? --test_count : test_count;
	
	printf("--------Testing FSASuggestSize()-----\t");
	
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");	
}

static void TestFSAInit()
{
	char *buf = (char*)malloc(100 * sizeof(char));
	size_t sug_size = FSASuggestSize(13,6);
	
	size_t block_size = 8;
	
	fsa_t *fsa = FSAInit(buf, sug_size, block_size);

	printf("--------Testing FSAInit()-----------\t");
	
	(NULL != fsa) ? printf("Success\n") : printf("Failure\n");
	
	free(buf);	
}

static void TestFSAAlloc()
{
	void *memory1 = NULL;
	void *memory2 = NULL;
	
	char *buf = (char*)malloc(100 * sizeof(char));
	
	size_t sug_size = FSASuggestSize(16,5);  /*98 */
	size_t block_size = 16;
	
	size_t test_count = 2;
	
	fsa_t *fsa = FSAInit(buf, sug_size, block_size);  
	
	memory1 = FSAAlloc(fsa);
	memory2 = FSAAlloc(fsa);
	
	printf("--------Testing FSAAlloc()-----------\t");

	(24 == *(size_t*)memory1) ? --test_count : test_count;
	(40 == *(size_t*)memory2) ? --test_count : test_count;
	
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");
	
	free(buf);	
}

static void TestFSAFree()
{
	void *memory1 = NULL;
	void *memory2 = NULL;
	
	char *buf = (char*)malloc(100 * sizeof(char));
	
	size_t sug_size = FSASuggestSize(16,5);  /*98 */
	size_t block_size = 16;
	
	size_t test_count = 4;
	
	fsa_t *fsa = FSAInit(buf, sug_size, block_size);  
	
	memory1 = FSAAlloc(fsa);
	memory2 = FSAAlloc(fsa);
	

	(24 == *(size_t*)memory1) ? --test_count : test_count;
	(40 == *(size_t*)memory2) ? --test_count : test_count;
	
	printf("--------Testing FSAFree()-----------\t");
	
	FSAFree(fsa , memory1);
	FSAFree(fsa , memory2);
	
	(40 == *(size_t*)memory1) ? --test_count : test_count;
	(8  == *(size_t*)memory2) ? --test_count : test_count;
	
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");
	
	free(buf);
}

static void TestFSACountFree()
{
	void *memory1 = NULL;
	void *memory2 = NULL;
	
	char *buf = (char*)malloc(100 * sizeof(char));
	
	size_t sug_size = FSASuggestSize(16,5);  /*98 */
	size_t block_size = 16;
	
	size_t test_count = 2;
	
	fsa_t *fsa = FSAInit(buf, sug_size, block_size);  
	
	memory1 = FSAAlloc(fsa);
	memory2 = FSAAlloc(fsa);
	
	(3 == FSACountFree(fsa)) ? --test_count : test_count;
	
	printf("--------Testing FSACountFree()-------\t");
	
	FSAFree(fsa , memory1);
	FSAFree(fsa , memory2);
	
	(5 == FSACountFree(fsa)) ? --test_count : test_count;

	(0 == test_count) ? printf("Success\n") : printf("Failure\n");
	
	free(buf);
}



