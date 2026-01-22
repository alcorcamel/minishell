#include "../../includes/utils.h"

t_bool	ft_is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (FALSE);
	if (S_ISDIR(st.st_mode) == 0)
		return (FALSE);
	return (TRUE);
}
