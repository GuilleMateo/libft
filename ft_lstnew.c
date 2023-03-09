#include "libft.h"

t_list *ft_lstnew(void *content)
{
	t_list	*link;

	if (!(link = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	link->content = (void*)content;
	link->next = NULL;
	return (link);
}