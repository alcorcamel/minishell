#ifndef UTILS_H
# define UTILS_H

# include "base.h"
# include "parser.h"
# include "env.h"

t_bool	ft_is_directory(char *path);
void	ft_free_shell(t_shell **shell);
void	ft_perror(char *err_p);

#endif
