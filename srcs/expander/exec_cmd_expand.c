#include "../../includes/executor.h"
#include "../../includes/expander.h"

static void	ft_invalid_dol_replace(t_ast *n)
{
	t_seg	*temp;
	size_t	size;

	if (!n)
		return ;
	temp = n->segs;
	while (temp)
	{
		if (temp->text)
			size = ft_strlen(temp->text);
		if (temp->text && temp->next && temp->next->type == SEG_SEP
			&& size != 0 && temp->text[size - 1] == '$')
			temp->text[size - 1] = '\x1C';
		temp = temp->next;
	}
}

static void	ft_invalid_dol_restorer(t_ast *n)
{
	t_seg	*temp;
	size_t	size;

	if (!n)
		return ;
	temp = n->segs;
	while (temp)
	{
		if (temp->text)
			size = ft_strlen(temp->text);
		if (temp->text && temp->next && temp->next->type == SEG_SEP
			&& size != 0 && temp->text[size - 1] == '\x1C')
			temp->text[size - 1] = '$';
		temp = temp->next;
	}
}

int	ft_cmd_expand(t_ast *n, t_shell *shell)
{
	if (!n || !n->segs)
		return (1);
	ft_invalid_dol_replace(n);
	if (!ft_var_translator(n, n->segs, shell))
		return (0);
	ft_invalid_dol_restorer(n);
	return (1);
}

int	ft_expand_seg_vars(t_ast *n, t_seg *seg, t_shell *shell)
{
	char	*s;

	if ((seg->type != SEG_RAW && seg->type != SEG_DQ) || !seg->text)
		return (1);
	s = ft_strchr(seg->text, '$');
	while (s)
	{
		if (*(s + 1) != '?' && ft_var_name_len(s + 1) == 0)
		{
			s = ft_strchr(s + 1, '$');
			continue ;
		}
		s = ft_expand_oneinseg(n, seg, shell, s);
		if (s == (char *)seg)
			return (0);
		if (!s)
			break ;
	}
	return (1);
}
