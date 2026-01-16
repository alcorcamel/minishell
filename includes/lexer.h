
/*
========PARSER========

struct t_arg qui stocke les segs
struct t_redirs qui stocke le type de l'op, les segs, hd_exp (0/1 si limiter entre quote ou pas)

------build_pipe------
commence par appeler parse_cmd (qui va forcement s arreter sur | (ou autre op sup) si trouve)
while (|)
{ il avance, right = parse_cmd, construit un nouveau noeud, le met au dessus }
retourne left, la racine du pipe construit

------parse_cmd-------

solution preferee:
une fonction parse la liste sans modifier le * cur principal, pour voir si (
si aucun, elle appelle parser_simple
sinon:
- sur redir + WORD (obligatoire), stocke ds les struct respectives
- sur redir_hd + WORD (limiter), stocke ds les struct resp ac hd_exp (0/1 si limiter entre quote ou pas)
si ( il appelle &&_|| qui creent inside (t_ast)
il se retrouve ensuite sur ), le passe

il a déjà inside = AST renvoyé par parse_and_or
il fabrique :
root = NODE_SUBSHELL(left = inside)

- sur redir + WORD (obligatoire), stocke ds les struct respectives
- sur redir_hd + WORD (limiter), stocke ds les struct resp ac hd_exp (0/1 si limiter entre quote ou pas)
il transfo chaque redir en noeud unaire:
root = REDIR(op, target_segs, left = root)

-----parse_simple-----
stop sur un tok sup: | && || ) ou NULL
- sur WORD il prend le token->segs (et eventuellement sa value)
(via un fnct qui copie le pointeur et met token->segs a NULL)
- sur redir + WORD (obligatoire), stocke ds les struct respectives
- sur redir_hd + WORD (limiter), stocke ds les struct resp ac hd_exp (0/1 si limiter entre quote ou pas)

FAUT FAIRE UN PUSH FRONT SUR LA LISTE DE REDIRS POUR QUE L EXECUTEUR LES LISE A LENVERS ET LES EXEC CORRECTEMENT
FAUT GERER > out sans args ds le NODE_CMD

Au stop il cree le NODE_CMD ac une liste de t_arg contenant les listes de T-seg de chaque WORD
pour que: cmd > a > b
devienne:
REDIR_OUT(a,
  left = REDIR_OUT(b,
          left = CMD(cmd)))
root = REDIR(b, root)
root = REDIR(a, root)




DS LE PARSER, REFUSER REDIRS + SUBSHELL

*/
#ifndef LEXER_H
# define LEXER_H

# include "base.h"
// clear; cc ./srcs/lexer/*.c ./srcs/lexer/*.h ./includes/libft/libft.h ./includes/libft/libft.a -lreadline -lhistory -lncurses

t_token		*ft_lexer(char *input);
void		ft_free_segs(t_seg *seg);
void		ft_free_tokens(t_token *tok);
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
