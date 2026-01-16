
#include "../../includes/parser.h"

void	ft_pars_err(int i, char *s)
{
	if (i == 1)
		printf("minishell: syntax error near unexpected token '%s'\n", s);
	else if (i == 2)
		printf("minishell: syntax error near unexpected token newline\n");

}
