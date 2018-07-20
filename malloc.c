
#include "malloc.h"
#include "libft.h"
#include <stdio.h>
#include <sys/mman.h>



static
void			print_free_list(node_t *free_list_head)
{
	printf("free list state:\n");
	while (free_list_head)
	{
		printf("address: %p\tsize: %u\n", (void*)free_list_head, free_list_head->size);
		free_list_head = free_list_head->next;
	}
}

static
void			set_chunk_header(node_t *free_list_head, size_t size)
{
	header_t	*head;

	head = (header_t*)free_list_head;
	head->size = size;
	head->magic = 1;
}

static
void			update_free_list_head(node_t **free_list_head, size_t size, size_t n, node_t *next)
{
	*free_list_head = (void*)*free_list_head + size + sizeof(header_t);
	(*free_list_head)->size = n - size - sizeof(header_t);
	(*free_list_head)->next = next;
}

static
void			*get_chunk(node_t **free_list_head, size_t size)
{
	node_t	*next;
	size_t	n;
	void	*chunk;

	while (free_list_head)
	{
		if ((*free_list_head)->size > size)
		{
			n = (*free_list_head)->size;
			next = (*free_list_head)->next;
			set_chunk_header(*free_list_head, size);
			chunk = (void*)(*free_list_head) + sizeof(header_t);
			update_free_list_head(free_list_head, size, n, next);
			
			return (chunk);
		}
		free_list_head = &(*free_list_head)->next;
	}
	return (NULL);
}

void			*ft_malloc(size_t size)
{
	static node_t	*free_list_head;
	void			*chunk;

	if (!free_list_head)
	{
		free_list_head = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
		free_list_head->size = 4096 - sizeof(node_t);
		free_list_head->next = NULL;
	}
	print_free_list(free_list_head);
	chunk = get_chunk(&free_list_head, size);
	print_free_list(free_list_head);
	return (chunk);
}

void			ft_free(void *ptr)
{
	header_t	*header;

	header = GET_HEADER(ptr);
	printf("header address: %p size: %u, magic: %u\n", header, header->size, header->magic);
}
