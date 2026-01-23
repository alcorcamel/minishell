#include "../../includes/executor.h"
#include "../../includes/expander.h"

static void	ft_seg_printer(t_ast *n)
{
	t_seg	*temp;
	size_t	i;
	size_t	size;

	if (!n)
		return ;
	temp = n->segs;
	printf("'");
	while (temp)
	{
		if (temp->text)
			size = ft_strlen(temp->text);
		else if (temp->type == SEG_SEP)
			printf("'");
		i = -1;
		while (++i < size)
			printf("%c", temp->text[i]);
		temp = temp->next;
	}
	printf("\n");
}

static void ft_invalid_dol_replace(t_ast *n)
{
	t_seg	*temp;
	int		i;
	size_t	size;

	if (!n)
		return ;
	temp = n->segs;
	while (temp)
	{
		if (temp->text)
			size = ft_strlen(temp->text);
		if (temp->text && temp->next && temp->next->type == SEG_SEP
			&& temp->text[size - 1] == '$')
			temp->text[size - 1] = '\x1C';
		temp = temp->next;
	}
}

static void ft_invalid_dol_restorer(t_ast *n)
{
	t_seg	*temp;
	int		i;
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
	t_seg	*segs;

	segs = n->segs;
	if (!segs)
		return (0);
	ft_invalid_dol_replace(n);
	if (!ft_var_translator(n, segs, shell))
		return (0);
	ft_invalid_dol_restorer(n);
	return (1);
}
