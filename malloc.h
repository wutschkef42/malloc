/*
**	The memory area allocated to the heap is divided into chunks of various sizes.
**	Each chunk has a header and its remainder is available for use as a data block.
**	There are two types of chunks: INUSE and FREE
**	An INUSE chunk is one that has been allocated to an application via a malloc()
**	The application uses the data block of the chunk, it does not access the header
**	INUSE chunks have headers of 8 bytes -> what do they store? Probably the size of the chunk and the INUSE status
**	
**	FREE and INUSE chunks have the same struct layout but are used in different ways (akin to unions)
**	INUSE chunks are traversed by pointer arithmetic, whereas FREE chunks are traversed as circular doubly linked lists

**	CHUNK LAYOUT
**	
**	         HEADER
**	|----------------------|
**	| size of prev chunk   | 8 bytes, exists if prev chunk is FREE
**	| size of chunk        | 8 bytes, take 2 LSBs as flags for a) mmapped chunk b) Previous chunk is in use
**	|----------------------|
**
**
**
**	Memory, once free()'d is stored in linked lists called bins, sorted by size
**	Fastbins go up to 80 bytes and are not coalesced with surrounding chunks on free()
**	They are not sorted and only have singular linked lists
**	There are ten fast bins with real chunk sizes ranging from 16 to 88 bytes
**	=> The fast bins serve TINY allocations

**	SMALL allocations are less than 512 byes
**	LARGE allocations are over 512 byes and under 128 kilobytes

*/


#ifndef MALLOC_H
# define MALLOC_H
# include <unistd.h>

# define GET_HEADER(node) (void*)node - sizeof(header_t)

/* 
** used by free to determine the size of an allocated region
** immediately precedes the pointers returned by malloc 
** free uses pointer arithmetic to get a reference to the header
**
** void free(void *ptr) {
**	header_t *hptr = (void *)ptr - sizeof(header_t);
**	...
*/

typedef struct	__header_t
{
	int	size;
	int	magic;
}				header_t;


/*
** free list node (address to free chunk of memory)
** points to a free chunk of memory
** stores size information about the free chunk
** and a reference to the next free chunk (address of the next free chunk in the mmapped page)
*/

typedef struct	__node_t
{
	int				size;
	struct __node_t	*next;
}				node_t;


/* 
** malloc library api functions
*/

void			*ft_malloc(size_t size);
void			ft_free(void *ptr);

#endif