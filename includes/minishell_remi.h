/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_remi.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:23:59 by demane            #+#    #+#             */
/*   Updated: 2026/01/08 00:31:54 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_REMI_H
# define MINISHELL_REMI_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_segtype
{
	SEG_RAW,// hors quotes
	SEG_SQ,// '...'
	SEG_DQ // "..."
}	t_segtype;

typedef struct	s_seg
{
	t_segtype		type;
	char			*text;// contenu SANS les quotes
	struct s_seg	*next;
} t_seg;

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
	TOKEN_LBRACKET,
	TOKEN_RBRACKET,
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
	NODE_CMD,// word
	NODE_PIPE,// |
	NODE_REDIR_IN,// <
	NODE_REDIR_OUT,// >
	NODE_REDIR_APPEND, // >>
	NODE_HEREDOC, // <<
	NODE_AND,// &&
	NODE_OR,// ||
	NODE_SUBSHELL,// (...word or pipe etc...)
}	t_node_type;

typedef struct s_ast {
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**args;
	char			*filename;
}	t_ast;

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

#endif
