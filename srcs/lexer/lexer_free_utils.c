#include "../../includes/lexer.h"
#include "../../includes/parser.h"

void	ft_free_segs(t_seg **seg)
{
	t_seg	*next;
	t_seg	*tmp;

	if (!seg || !*seg)
		return ;
	tmp = *seg;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->text);
		tmp->text = NULL;
		free(tmp);
		tmp = NULL;
		tmp = next;
	}
}

void	ft_free_tokens(t_token **tok)
{
	t_token	*next;
	t_token	*tmp;

	if (!tok || !*tok)
		return ;
	tmp = *tok;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->value);
		ft_free_segs(&tmp->segs);
		free(tmp);
		tmp = NULL;
		tmp = next;
	}
}
