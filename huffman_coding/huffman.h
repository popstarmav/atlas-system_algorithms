#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdlib.h>
#include "heap/heap.h"

/**
 * struct symbol_s - Stores a char and its associated frequency
 *
 * @data: The character
 * @freq: The associated frequency
 */
typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;

/* Function prototypes */
symbol_t *symbol_create(char data, size_t freq);
int huffman_extract_and_insert(heap_t *priority_queue);
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);

#endif /* HUFFMAN_H */

