#ifndef MINISHELL_H
# define MINISHELL_H

# include "./base.h"
# include "../srcs/lexer/lexer.h"
# include "../srcs/parser/parser.h"

t_token		*ft_lexer(char *input);
void		*ft_exec_ast(t_ast *node);

#endif
