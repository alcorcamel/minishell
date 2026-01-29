/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:04:27 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:08:49 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_H
# define BASE_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <dirent.h>
# include <sys/ioctl.h>
# define _GNU_SOURCE
# include <termios.h>

extern volatile sig_atomic_t	g_signal;

typedef struct sigaction		t_sigaction;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef struct s_vars
{
	char			*key;
	char			*value;
	t_bool			is_exported;
	struct s_vars	*next;
}	t_vars;

typedef struct s_new_args
{
	char				*value;
	struct s_new_args	*next;
	t_bool				globbed;
}	t_new_args;

typedef enum e_segtype
{
	SEG_RAW,
	SEG_SQ,
	SEG_DQ,
	SEG_SEP
}	t_segtype;

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
	t_bool			limiter_quoted;
	t_bool			is_expanded;
}	t_ast;

typedef struct s_shell
{
	t_vars	*vars;
	int		last_status;
	t_ast	*root_ast;
	t_bool	should_exit;
	t_bool	interactive;
	char	*prompt;
}	t_shell;

#endif
