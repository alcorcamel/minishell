
#include "../../includes/lexer.h"

static int	ft_read_sq(char *s, int *i, t_seg **segs)
{
	int	start;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	if (s[*i] != '\'')
		return (ft_lex_err(15, "\'"), 0);
	if (!ft_add_seg(segs, SEG_SQ, s + start, *i - start))
		return (0);
	(*i)++;
	return (1);
}

static int	ft_read_dq(char *s, int *i, t_seg **segs)
{
	int	start;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '"')
		(*i)++;
	if (s[*i] != '"')
		return (ft_lex_err(14, "\""), 0);
	if (!ft_add_seg(segs, SEG_DQ, s + start, *i - start))
		return (0);
	(*i)++;
	return (1);
}

static int	ft_read_normal(char *s, int *i, t_seg **segs)
{
	int	start;

	start = *i;
	while (s[*i] && !ft_is_sep(s[*i]) && s[*i] != '\'' && s[*i] != '"')
		(*i)++;
	if (*i == start)
		return (1);
	return (ft_add_seg(segs, SEG_RAW, s + start, *i - start));
}

static int	ft_read_word_helper(char *s, int *i, t_seg **segs, t_token *tok)
{
	if (s[*i] == '\'')
	{
		if (!ft_read_sq(s, i, segs))
			return (ft_free_segs(*segs), free(tok), 0);
	}
	else if (s[*i] == '"')
	{
		if (!ft_read_dq(s, i, segs))
			return (ft_free_segs(*segs), free(tok), 0);
	}
	else
	{
		if (!ft_read_normal(s, i, segs))
			return (ft_free_segs(*segs), free(tok), 0);
	}
	return (1);
}

int	ft_read_word(t_token **lst, char *s, int *i)
{
	t_token	*tok;
	t_seg	*segs;

	tok = ft_toknew(TOKEN_WORD);
	if (!tok)
		return (0);
	segs = NULL;
	while (s[*i] && !ft_is_sep(s[*i]))
	{
		if (ft_read_word_helper(s, i, &segs, tok) == 0)
			return (0);
	}
	if (!ft_add_seg(&segs, SEG_SEP, "", 0))
		return (ft_free_segs(segs), free(tok), 0);
	tok->segs = segs;
	tok->value = ft_join_segs(segs);
	if (!tok->value)
		return (ft_free_segs(segs), free(tok), 0);
	ft_tokadd_back(lst, tok);
	return (1);
}
