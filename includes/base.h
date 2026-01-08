#ifndef TYPES_H
# define TYPES_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

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
	char			*limiter;
	char			*filename;
}	t_ast;

typedef struct s_shell
{
	char	**envp;
	t_bool	in_pipeline;
}	t_shell;

#endif
