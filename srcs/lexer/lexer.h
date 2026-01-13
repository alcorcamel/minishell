
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
# include "../../../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_shell
{
	char	**envp;
}	t_shell;

typedef enum e_segtype
{
	SEG_RAW,
	SEG_SQ,
	SEG_DQ,
	SEG_SEP
}	t_segtype;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_seg
{
	t_segtype		type;
	char			*text;
	struct s_seg	*next;
}	t_seg;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_seg			*segs;
	struct s_token	*next;
}	t_token;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
	NODE_HEREDOC,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL,
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**args;
	t_seg			*segs;
	char			*filename;
	char			*limiter;
}	t_ast;

// clear; cc ./srcs/lexer/*.c ./srcs/lexer/*.h ./includes/libft/libft.h ./includes/libft/*.c -lreadline -lhistory -lncurses

t_token		*ft_lexer(char *input);
void		ft_free_segs(t_seg *seg);
void		ft_free_tokens(t_token *tok);
int			ft_add_operator(t_token **lst, char *s, int *i);
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
/*-------------parser--------------*/
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
/*--------------executor-------------*/
int			ft_exec_root(t_ast *node, t_shell *shell);
int			ft_exec_pipe(t_ast *node, t_shell *shell);
int			ft_exec_cmd(t_ast *node, t_shell *shell);
int			ft_exec_subshell(t_ast *node, t_shell *shell);
int			ft_exec_or(t_ast *node, t_shell *shell);
int			ft_exec_heredoc(t_ast *node, t_shell *shell);
int			ft_exec_redirect_in(t_ast *node, t_shell *shell);
int			ft_exec_redirect_out(t_ast *node, t_shell *shell);
int			ft_exec_redirect_append(t_ast *node, t_shell *shell);
int			ft_exec_builtin(t_ast *node, t_shell *shell);
int			ft_exec_and(t_ast *node, t_shell *shell);
int			ft_exec_or(t_ast *node, t_shell *shell);
int			ft_exec_ast(t_ast *node, t_shell *shell);

void		ast_print(const t_ast *root);

#endif
