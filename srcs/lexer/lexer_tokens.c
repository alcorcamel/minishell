#include "lexer.h"

t_token	*ft_toknew(t_token_type type)
{
	t_token	*ret;

	ret = (t_token *)malloc(sizeof(t_token));
	if (!ret)
		return (NULL);
	ret->type = type;
	ret->value = NULL;
	ret->segs = NULL;
	ret->next = NULL;
	return (ret);
}

void	ft_tokadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
