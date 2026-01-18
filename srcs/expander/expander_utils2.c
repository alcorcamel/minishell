
#include "../../includes/expander.h"

void	ft_free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
}

void	ft_var_translator(t_seg *segs, t_shell *shell)
{
	t_seg	*temp;

	temp = segs;
	while (temp)
	{
		if (!ft_expand_seg_vars(temp, shell))
			return ;
		temp = temp->next;
	}
}

int	ft_is_limiter(char *line, char *limiter)
{
	size_t	len;

	if (!line || !limiter)
		return (0);
	len = ft_strlen(limiter);
	return (ft_strncmp(line, limiter, len) == 0
		&& line[len] == '\n'
		&& line[len + 1] == '\0');
}


static void	ft_join_segs_until_sep_helper(t_seg *temp, size_t *size)
{
	while (temp && temp->type != SEG_SEP)
	{
		if (temp->text)
			*size += ft_strlen(temp->text);
		temp = temp->next;
	}
}

char	*ft_join_segs_until_sep(t_seg *seg)
{
	size_t	size;
	size_t	i;
	t_seg	*temp;
	char	*ret;

	size = 0;
	temp = seg;
	ft_join_segs_until_sep_helper(temp, &size);
	ret = (char *)malloc(size + 1);
	if (!ret)
		return (NULL);
	i = 0;
	temp = seg;
	while (temp && temp->type != SEG_SEP)
	{
		if (temp->text)
		{
			size = ft_strlen(temp->text);
			ft_memcpy(ret + i, temp->text, size);
			i += size;
		}
		temp = temp->next;
	}
	return (ret[i] = '\0', ret);
}
