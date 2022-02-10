/*
 * malloc.c
 *
 *  Created on: Jul 20, 2018
 *      Author: johan
 */

#include <stdio.h>

#include <FreeRTOS.h>
#include <string.h>

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
