/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:20:37 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:20:38 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	ft_print_err_env(void)
{
	ft_putstr_fd("minishield: env: too many arguments\n", STDERR_FILENO);
	return (1);
}

static int	ft_print_envp_for_env(t_shell *shell)
{
	t_vars	*iterator;

	iterator = shell->vars;
	while (iterator)
	{
		if (iterator->is_exported == TRUE)
		{
			if (iterator->value)
			{
				ft_printf("%s", iterator->key);
				ft_printf("=%s\n", iterator->value);
			}
		}
		iterator = iterator->next;
	}
	return (0);
}

int	ft_env(char **args, t_shell *shell)
{
	if (args[1])
		return (ft_print_err_env());
	return (ft_print_envp_for_env(shell));
}
