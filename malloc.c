
typedef struct	__header_t
{
	int	size;
	int	magic;
}				header_t;

typedef struct	__node_t
{
	int				size;
	struct __node_t	*next;
}				node_t;

// mmap() returns a pointer to a chunk of free space
node_t	*head = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
head->size = 4096 - sizeof(node_t);
head->next = NULL;