#include "../../includes/executor.h"
#include "../../includes/expander.h"

static char	*ft_replace_var_helper(t_seg *segs, char *s, int j, int name_len)
{
	int		s_len;
	int		after_len;
	char	*ret;
	int		i;

	s_len = ft_strlen(s);
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

static int	ft_replace_var(char *s, t_seg *segs, int name_len)
{
	int		j;
	char	*ret;

	if (!segs || !segs->text || !s || name_len < 0)
		return (0);
	j = 0;
	while (segs->text[j] && segs->text[j] != '$')
		j++;
	if (segs->text[j] != '$')
		return (1);
	ret = ft_replace_var_helper(segs, s, j, name_len);
	if (!ret)
		return (0);
	free(segs->text);
	segs->text = ret;
	return (1);
}

static char	*ft_exp_onevar_helper(t_seg *seg, t_shell *shell, char *found)
{
	found = ft_itoa(shell->last_status);
	if (!found)
		return (NULL);
	if (!ft_replace_var(found, seg, 1))
		return (free(found), NULL);
	free(found);
	return (ft_strchr(seg->text, '$'));
}

static char	*ft_expand_one_var_in_seg(t_seg *seg, t_shell *shell, char *s)
{
	char	*name;
	char	*found;
	int		len;

	if (*(s + 1) == '?')
		return (ft_exp_onevar_helper(seg, shell, found));
	len = ft_var_name_len(s + 1);
	if (len == 0)
		return (ft_strchr(s + 1, '$'));
	name = ft_strndup(s + 1, len);
	if (!name)
		return (NULL);
	if (ft_find_vars(name, shell))
		found = ft_strdup(ft_find_vars(name, shell)->value);
	free(name);
	if (!found)
	{
		found = ft_strdup("");
		if (!found)
			return (NULL);
	}
	if (!ft_replace_var(found, seg, len))
		return (free(found), NULL);
	free(found);
	return (ft_strchr(seg->text, '$'));
}

int	ft_expand_seg_vars(t_seg *seg, t_shell *shell)
{
	char	*s;

	if ((seg->type != SEG_RAW && seg->type != SEG_DQ) || !seg->text)
		return (1);
	s = ft_strchr(seg->text, '$');
	while (s)
	{
		s = ft_expand_one_var_in_seg(seg, shell, s);
		if (!s && ft_strchr(seg->text, '$'))
			return (0);
	}
	return (1);
}
