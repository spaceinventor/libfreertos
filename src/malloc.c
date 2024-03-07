/*
 * malloc.c
 *
 *  Created on: Jul 20, 2018
 *      Author: johan
 */

#include <FreeRTOS.h>
#include <portable.h>
#include <string.h>
#include <task.h>

void * malloc(size_t size) {
	return pvPortMalloc(size);
}

void * calloc(size_t n, size_t size) {
	void * data = malloc(n * size);
	memset(data, 0, n * size);
	return data;
}

void free(void * ptr) {
	vPortFree(ptr);
}

typedef struct A_BLOCK_LINK {
  struct A_BLOCK_LINK *pxNextFreeBlock; /*<< The next free block in the list. */
  size_t xBlockSize;                    /*<< The size of the free block. */
} BlockLink_t;

static const size_t xHeapStructSize =
    (sizeof(BlockLink_t) + ((size_t)(portBYTE_ALIGNMENT - 1))) &
    ~((size_t)portBYTE_ALIGNMENT_MASK);

static const size_t xBlockAllocatedBit = ((size_t)1) << ((sizeof(size_t) * sizeof(uint8_t) * 8) - 1);

void *pvPortRealloc(void *pv, size_t xNewSize) {
  printf("free: %u\n", xPortGetFreeHeapSize());
  vTaskSuspendAll();
  if (pv == NULL) {
    // If pv is NULL, then the call is equivalent to malloc(size)
    (void)xTaskResumeAll();
    return pvPortMalloc(xNewSize);
  }

  if (xNewSize == 0) {
    // If size is zero and pv is not NULL, then the call is equivalent to
    vPortFree(pv);
    (void)xTaskResumeAll();
    return NULL;
  }

  // Cast to a BlockLink_t pointer, stepping back to find the block metadata
  BlockLink_t *pxBlock = (BlockLink_t *)(((uint8_t *)pv) - xHeapStructSize);

  // Check if block size is already correct
  if ((pxBlock->xBlockSize & ~xBlockAllocatedBit) ==
      xNewSize + xHeapStructSize) {
    (void)xTaskResumeAll();
    return pv;  // No need to reallocate
  }
  /* TODO
    check next block if empty xBlockAllocatedBit
    has space for current xBlockSize merging into it only if heapMINIMUM_BLOCK_SIZE 

    this is maybe not possible as the next pointer is set to NULL when handed over to application
    and we do not have access to the start and end pointers from here
  */

  // Allocate new block
  void *pvNew = pvPortMalloc(xNewSize);

  if (pvNew != NULL) {
    // Copy old data to new block
    memcpy(pvNew, pv,
           (pxBlock->xBlockSize & ~xBlockAllocatedBit) - xHeapStructSize);

    // Free old block
    vPortFree(pv);
  }

  (void)xTaskResumeAll();
  return pvNew;
}

void *realloc(void *pv, size_t xNewSize) {
    return pvPortRealloc(pv, xNewSize);
}
