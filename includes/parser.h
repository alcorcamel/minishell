
#ifndef PARSER_H
# define PARSER_H

# include "base.h"

void		free_segs(t_seg *s);
t_seg		*seg_last(t_seg *s);
int			seg_append_words(t_seg **dst, t_seg *src);
t_seg		*seg_word_separator(void);
int			ft_is_operator(t_token *cur);
int			ft_is_paren(t_token *cur);
int			ft_is_redir(t_token *cur);
t_ast		*ft_ast_new(t_node_type type);
t_ast		*ft_ast_new_bin(t_node_type type, t_ast *left, t_ast *right);
t_ast		*ft_ast_new_cmd(t_seg *segs);
t_ast		*ft_ast_new_subshell(t_ast *subshell);
t_ast		*ft_ast_new_redir(t_token_type op, t_seg *segs, t_ast *left);
t_ast		*ft_build_and_or(t_token **cur);
t_ast		*ft_build_pipe(t_token **cur);
t_ast		*ft_build_subshell(t_token **cur);
t_ast		*ft_parse_subshell(t_token **cur);
t_ast		*ft_parse_simple(t_token **cur);
void		free_ast(t_ast **root);
void		ft_pars_err(int i, char *s);

#endif
