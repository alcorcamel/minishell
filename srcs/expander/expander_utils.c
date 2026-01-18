#include "../../includes/expander.h"

char	*ft_valid_filename_finder(void)
{
	int		i;
	char	*nb;
	char	*file;

	i = 0;
	nb = ft_itoa(i);
	if (!nb)
		return (NULL);
	file = ft_strjoin("./.coucou", nb);
	if (!file)
		return (free(nb), NULL);
	while (access(file, F_OK) == 0)
	{
		free(file);
		free(nb);
		i++;
		nb = ft_itoa(i);
		if (!nb)
			return (NULL);
		file = ft_strjoin("./.coucou", nb);
		if (!file)
			return (free(nb), NULL);
	}
	return (free(nb), file);
}

int	ft_var_name_len(char *s)
{
	int	i;

	if (!s || !ft_is_var_start(s[0]))
		return (0);
	i = 0;
	while (s[i] && ft_is_var_char(s[i]))
		i++;
	return (i);
}

char	*ft_var_replace(char *line, char *found, int i, int name_len)
{
	int		found_len;
	int		after_len;
	char	*ret;

	if (!line || !found)
		return (NULL);
	found_len = ft_strlen(found);
	after_len = ft_strlen(line + i + 1 + name_len);
	ret = (char *)malloc(i + found_len + after_len + 1);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, line, i);
	ft_memcpy(ret + i, found, found_len);
	ft_memcpy(ret + i + found_len, line + i + 1 + name_len, after_len);
	ret[i + found_len + after_len] = '\0';
	return (ret);
}

int	ft_is_var_start(char c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| c == '_')
		return (1);
	return (0);
}

int	ft_is_var_char(char c)
{
	if (ft_is_var_start(c) || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
