
#include "../../includes/lexer.h"

t_token	*ft_lexer(char *l)
{
	int		i;
	t_token	*lst_begin;
	int		brace;

	i = 0;
	brace = 0;
	if (!l)
		return (NULL);
	lst_begin = NULL;
	while (l[i])
	{
		while (ft_isspaces(l[i]))
			i++;
		if (!l[i])
			break ;
		if (ft_is_brace(l[i]) || ft_is_an_operator(l[i]))
		{
			if (!ft_add_operator(&lst_begin, l, &i, &brace))
				return (ft_free_tokens(lst_begin), NULL);
		}
		else
		{
			if (!ft_read_word(&lst_begin, l, &i))
				return (ft_free_tokens(lst_begin), NULL);
		}
	}
	if (brace > 0)
		return (ft_free_tokens(lst_begin), ft_lex_err(14, ")"), NULL);
	else if (brace < 0)
		return (ft_free_tokens(lst_begin), ft_lex_err(14, "("), NULL);
	return (lst_begin);
}
