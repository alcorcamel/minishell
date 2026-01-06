/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell remi.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:23:59 by demane            #+#    #+#             */
/*   Updated: 2026/01/06 21:33:19 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef enum e_segtype {
	SEG_RAW,// hors quotes
	SEG_SQ,// '...'
	SEG_DQ // "..."
} t_segtype;

typedef struct s_seg {
	t_segtype		type;
	char			*text;// contenu SANS les quotes
	struct s_seg	*next;
} t_seg;

typedef enum e_token_type {
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
	TOKEN_EOF
}	t_token_type;

typedef struct s_token {
	t_token_type	type;
	char			*value;
	t_seg			*segs;
	struct s_token	*next;
}	t_token;

typedef enum e_node_type {
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
	char			filename;
}	t_ast;

t_token		*ft_lexer(char *input);

#endif
