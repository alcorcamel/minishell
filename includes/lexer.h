#ifndef LEXER_H
# define LEXER_H
# include "base.h"

t_token		*ft_lexer(char *input);
void		ft_free_segs(t_seg **seg);
void		ft_free_tokens(t_token **tok);
int			ft_add_operator(t_token **lst, char *s, int *i, int *brace);
int			ft_read_word(t_token **lst, char *s, int *i);
t_token		*ft_toknew(t_token_type type);
void		ft_tokadd_back(t_token **lst, t_token *new);
char		*ft_join_segs(t_seg *seg);
int			ft_add_seg(t_seg **segs, t_segtype type, char *start, int len);
int			ft_isspaces(char c);
int			ft_is_brace(char c);
int			ft_is_an_operator(char c);
int			ft_is_sep(char c);
char		*ft_strndup(const char *s, int n);
t_token		*ft_lexer(char *l);
void		ft_lex_err(int i, char *s);
int			ft_parser(t_token *tokens);
void		ft_pars_err(int i, char *s);

#endif
