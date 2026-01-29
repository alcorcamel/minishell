/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:06:44 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:06:46 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"
# include "env.h"
# include "signals.h"
# include "utils.h"

int			ft_explore_ast(t_ast **root, t_shell *vars);
int			ft_heredoc_expand(t_ast *n, t_shell *shell);
int			ft_restore_args(char **args);
int			ft_cmd_rebuild(t_ast *n);
int			ft_cmd_expand(t_ast *n, t_shell *shell);
int			ft_expand_seg_vars(t_ast *n, t_seg *seg, t_shell *shell);
void		ft_free_args(char **args);
char		*ft_valid_filename_finder(void);
int			ft_var_name_len(char *s);
char		*ft_var_replace(char *line, char *found, int i, int name_len);
int			ft_is_var_start(char c);
int			ft_is_var_char(char c);
char		*ft_join_segs_until_sep(t_seg *seg);
int			ft_is_limiter(char *line, char *limiter);
int			ft_var_translator(t_ast *n, t_seg *segs, t_shell *shell);
int			ft_is_quoted(t_ast *n);
int			ft_heredoc_rebuild(t_ast *n, t_shell *shell);
int			ft_redir_rebuild(t_ast *n);
int			ft_redir_expand(t_ast *n, t_shell *shell);
int			ft_args_handler(t_ast *n);
void		ft_expander_error(char *s, int i);
int			ft_inout_globber(t_ast *n);
void		ft_free_nargs(t_new_args *node);
int			ft_valid_star_any_inout(char *line, char *arg);
int			ft_valid_star_any(char *line, char *arg);
t_new_args	*ft_argnew(char *value);
int			ft_arg_restorer_bis(char *arg);
int			ft_spechar_counter(char *arg);
int			ft_arg_lstsize(t_new_args *lst);
int			ft_spe_arg_lstsize(t_new_args *lst);
void		ft_str_capitalizer(char *str);
int			ft_str_compare(char *s1, char *s2);
void		ft_arg_add_back(t_new_args **lst, t_new_args *new, int i);
int			ft_inout_globber(t_ast *n);
int			ft_new_args_maker(t_new_args **head, t_ast *n);
int			ft_star_anywhere(t_new_args **head, char *arg);
char		*ft_expand_oneinseg(t_ast *n, t_seg *seg, t_shell *shell, char *s);
int			ft_set_empty_cmd(t_ast *n, char *ret);
int			ft_is_empty(char *s);
int			ft_cmd_rebuild2(t_ast *n, char **ret);
int			ft_cmd_rebuild_noifs(t_ast *n);
int			ft_cmd_rebuild2_noifs(t_ast *n, char **ret);
int			ft_is_empty_noifs(char *s);

#endif
