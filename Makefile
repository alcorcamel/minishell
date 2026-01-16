NAME=minishell
DIR_LEXER=lexer
DIR_PARSER=parser
DIR_EXPANDER=expander
DIR_BUILTINS=builtins
DIR_ENV=env
DIR_SIGNALS=signals
DIR_UTILS=utils
DIR_EXECUTOR=executor
DIR_SRCS= srcs
FILES_LEXER= lexer_free_utils.c lexer_operators.c lexer_print_err.c lexer_reader.c lexer_segs.c \
	lexer_tokens.c	lexer_utils.c
FILES_PARSER= parser_ast_builder.c parser.c parser_print_err.c parser_utils2.c
	parser_builder.c parser_free.c parser_segs.c parser_utils.c
FILES_BUILTINS= built_cd.c built_echo.c built_env.c built_exit.c built_export.c built_pwd.c built_unset.c built_utils.c
FILES_EXECUTOR= exec_and.c exec_append.c exec_ast.c exec_cmd.c exec_or.c exec_pipe.c exec_redirect.c exec_root.c exec_subshell.c exec_get_path.c exec_throw_error.c exec_built.c
FILES_EXPANDER= expander.c
SRCS_LEXER = $(addprefix $(DIR_SRCS)/, $(addprefix $(DIR_LEXER)/, $(FILES_LEXER)))
SRCS_PARSER = $(addprefix $(DIR_SRCS)/, $(addprefix $(DIR_PARSER)/, $(FILES_LEXER)))
SRCS_EXPANDER = $(addprefix $(DIR_SRCS)/, $(addprefix $(DIR_EXPANDER)/, $(FILES_EXPANDER)))
SRCS_EXECUTOR = $(addprefix $(DIR_SRCS)/, $(addprefix $(DIR_EXECUTOR)/, $(FILES_EXECUTOR)))
