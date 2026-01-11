#ifndef EXECUTOR_H
# define EXECUTOR_H

#include "../../includes/base.h"
// #include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../builtins/builtins.h"

int		ft_exec_root(t_ast *node, char **envp);
int		ft_exec_pipe(t_ast *node, t_shell *shell);
int		ft_exec_cmd(t_ast *node, t_shell *shell);
int		ft_exec_subshell(t_ast *node, t_shell *shell);
int		ft_exec_or(t_ast *node, t_shell *shell);
int		ft_exec_heredoc(t_ast *node, t_shell *shell);
int		ft_exec_redirect_in(t_ast *node, t_shell *shell);
int		ft_exec_redirect_out(t_ast *node, t_shell *shell);
int		ft_exec_redirect_append(t_ast *node, t_shell *shell);
int		ft_exec_builtin(t_ast *node, t_shell *shell);
int		ft_exec_ast(t_ast *node, t_shell *shell);

#endif
