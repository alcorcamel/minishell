#ifndef BASE_H
# define BASE_H

# include "./libft/libft.h"
# include "./libft/get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_vars
{
	char			*key;
	char			*value;
	struct s_vars	*next;
}	t_vars;

typedef	struct s_exit
{
	int		status;
	t_bool	is_exited;
}	t_exit;


typedef struct s_shell
{
	char	**envp;
	t_vars	*vars;
	t_exit	ctrl_exit;
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


#endif
