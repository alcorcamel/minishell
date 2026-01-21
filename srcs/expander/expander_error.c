#include "../../includes/expander.h"

void	ft_expander_error(char *s, int i)
{
	if (i == 1)
		printf("bash: %s: ambigous redirect", s);
}
