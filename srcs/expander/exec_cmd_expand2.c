#include "../../includes/executor.h"
#include "../../includes/expander.h"

static char	*ft_replace_var_helper(t_seg *segs, char *s, int j, int name_len)
{
	int		s_len;
	int		after_len;
	char	*ret;
	int		i;

	s_len = ft_strlen(s);
	ret = NULL;
	after_len = ft_strlen(segs->text + j + 1 + name_len);
	ret = (char *)malloc(j + s_len + after_len + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < j)
		ret[i] = segs->text[i];
	ft_memcpy(ret + i, s, s_len);
	i += s_len;
	ft_memcpy(ret + i, segs->text + j + 1 + name_len, after_len);
	i += after_len;
	ret[i] = '\0';
	return (ret);
}

static int	ft_replace_var(char *s, t_seg *segs, int j, int name_len)
{
	char	*ret;

	if (!segs || !segs->text || !s || name_len < 0 || j < 0)
		return (0);
	if (!segs->text[j] || segs->text[j] != '$')
		return (1);
	ret = ft_replace_var_helper(segs, s, j, name_len);
	if (!ret)
		return (0);
	free(segs->text);
	segs->text = ret;
	return (1);
}

static char	*ft_exp_onevar_helper(t_seg *seg, t_shell *shell, int j)
{
	char	*found;

	found = ft_itoa(shell->last_status);
	if (!found)
		return ((char *)seg);
	if (!ft_replace_var(found, seg, j, 1))
		return (free(found), (char *)seg);
	free(found);
	return (ft_strchr(seg->text + j + 1, '$'));
}

int	ft_varinseg2(char **name, t_shell *sh, char **f, t_ast *n)
{
	if (ft_find_vars(*name, sh))
	{
		*f = ft_strdup(ft_find_vars(*name, sh)->value);
		if (!(*f))
			return (0);
	}
	free(*name);
	if (!(*f))
	{
		*f = ft_strdup("");
		n->is_expanded = 1;
		if (!(*f))
			return (free(*name), 0);
	}
	return (1);
}

char	*ft_expand_one_varinseg(t_ast *n, t_seg *seg, t_shell *shell, char *s)
{
	char	*name;
	char	*found;
	int		len;
	int		j;
	int		found_len;

	found = NULL;
	j = (s - seg->text);
	if (*(s + 1) == '?')
		return (ft_exp_onevar_helper(seg, shell, j));
	len = ft_var_name_len(s + 1);
	if (len == 0)
		return (ft_strchr(s + 1, '$'));
	name = ft_strndup(s + 1, len);
	if (!name)
		return ((char *)seg);
	if (!ft_varinseg2(&name, shell, &found, n))
		return ((char *)seg);
	found_len = ft_strlen(found);
	if (!ft_replace_var(found, seg, j, len))
		return (free(found), (char *)seg);
	free(found);
	return (ft_strchr(seg->text + j + found_len, '$'));
}
