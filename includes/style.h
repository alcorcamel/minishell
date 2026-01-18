#ifndef STYLE_H
# define STYLE_H

# include "base.h"
# include "env.h"

# define C_GRAY		"\033[90m"
# define C_RESET	"\001\033[0m\002"
# define C_BLUE		"\001\033[34m\002" // Minishield
# define C_GREEN	"\001\033[32m\002" // Path
# define C_RED		"\001\033[31m\002" // Error status
# define C_YELLOW	"\001\033[33m\002" // Optional extra


void	ft_print_boot(void);
char	*ft_generate_prompt(t_shell *shell);
void	ft_boot_loading(void);

#endif