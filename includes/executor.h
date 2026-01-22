#ifndef EXECUTOR_H
# define EXECUTOR_H

// #include "../lexer/lexer.h"
#include "parser.h"
#include "expander.h"
#include "builtins.h"
#include "utils.h"

// int			ft_exec_root(t_ast *node, t_shell *shell);
int			ft_exec_pipe(t_ast *node, t_shell *shell);
int			ft_exec_cmd(t_ast *node, t_shell *shell);
int			ft_exec_subshell(t_ast *node, t_shell *shell);
int			ft_exec_or(t_ast *node, t_shell *shell);
int			ft_exec_here_doc(t_ast *node, t_shell *shell);
int			ft_exec_redirect_in(t_ast *node, t_shell *shell);
int			ft_exec_redirect_out(t_ast *node, t_shell *shell);
int			ft_exec_append(t_ast *node, t_shell *shell);
int			ft_exec_builtin(t_ast *node, t_shell *shell);
int			ft_exec_and(t_ast *node, t_shell *shell);
int			ft_exec_or(t_ast *node, t_shell *shell);
int			ft_exec_ast(t_ast *node, t_shell *shell);
char		*ft_get_path(t_ast *node, t_shell *shell);
int			ft_throw_error(char *err_p);
int			ft_throw_error_cmd_not_found(char *err_p);
int			ft_exec_built(t_ast *node, t_shell *shell);
t_bool		ft_is_directory(char *path);
int			ft_throw_error_cmd(char *cmd);

#endif
