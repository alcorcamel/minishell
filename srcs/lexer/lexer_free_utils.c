
#include "../../includes/lexer.h"

void	ft_free_segs(t_seg *seg)
{
	t_seg	*next;

	while (seg)
	{
		next = seg->next;
		free(seg->text);
		free(seg);
		seg = next;
	}
}

void	ft_free_tokens(t_token *tok)
{
	t_token	*next;

	while (tok)
	{
		next = tok->next;
		free(tok->value);
		ft_free_segs(tok->segs);
		free(tok);
		tok = next;
	}
}
