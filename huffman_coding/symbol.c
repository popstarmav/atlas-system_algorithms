#include <stdlib.h>
#include "huffman.h"

/**
 * symbol_create - Creates a symbol_t data structure
 * @data: The data to be stored in the structure
 * @freq: Its associated frequency
 *
 * Return: A pointer to the created structure, or NULL if it fails
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbol;

	/* Allocate memory for the symbol structure */
	symbol = malloc(sizeof(symbol_t));
	if (symbol == NULL)
		return (NULL);

	/* Initialize the structure fields */
	symbol->data = data;
	symbol->freq = freq;

	return (symbol);
}

