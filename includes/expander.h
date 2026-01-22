#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"
# include "env.h"

int		ft_explore_ast(t_ast **root, t_shell *vars);
int		ft_heredoc_expand(t_ast *n, t_shell *shell);
int		ft_restore_args(char **args);
int		ft_cmd_rebuild(t_ast *n);
int		ft_cmd_expand(t_ast *n, t_shell *shell);
int		ft_expand_seg_vars(t_seg *seg, t_shell *shell);
void	ft_free_args(char **args);
char	*ft_valid_filename_finder(void);
int		ft_var_name_len(char *s);
char	*ft_var_replace(char *line, char *found, int i, int name_len);
int		ft_is_var_start(char c);
int		ft_is_var_char(char c);
char	*ft_join_segs_until_sep(t_seg *seg);
int		ft_is_limiter(char *line, char *limiter);
void	ft_var_translator(t_seg *segs, t_shell *shell);
int		ft_is_quoted(t_ast *n);
int		ft_heredoc_rebuild(t_ast *n);
int		ft_redir_rebuild(t_ast *n);
int		ft_redir_expand(t_ast *n, t_shell *shell);
int		ft_args_handler(t_ast *n);
void	ft_expander_error(char *s, int i);
int		ft_inout_globber(t_ast *n);
void	ft_free_nargs(t_new_args *node);

#endif
