#include "../../includes/lexer.h"
#include "../../includes/parser.h"

void	ft_free_segs(t_seg **seg)
{
	t_seg	*next;

	if (!seg || !*seg)
		return ;
	while (*seg)
	{
		next = (*seg)->next;
		ft_free((void **)&((*seg)->text));
		ft_free((void **)&(*seg));
		*seg = next;
	}
}

void	ft_free_tokens(t_token **tok)
{
	t_token	*next;

	if (!tok || !*tok)
		return ;
	while (*tok)
	{
		next = (*tok)->next;
		ft_free((void **)&((*tok)->value));
		ft_free_segs(&((*tok)->segs));
		ft_free((void **)&(*tok));
		*tok = next;
	}
}
