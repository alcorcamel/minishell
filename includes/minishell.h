/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:23:59 by demane            #+#    #+#             */
/*   Updated: 2026/01/06 17:54:19 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
	TOKEN_RBRACKET
}	t_token_type;

typedef struct s_token {
	t_token_type	type;
	char			*value;
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
	t_node_type		type; // type de noeud
	struct s_ast	*left;
	struct s_ast	*right;
	char			**args; // argument pour la commande
	int				infile;
	int				outfile;
	char			filename;
}	t_ast;

t_token		*ft_lexer(char *input);

#endif
