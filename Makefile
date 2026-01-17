NAME        = minishell
CC          = cc
# CFLAGS      = -Wall -Wextra -Werror -I./includes
CFLAGS      = -I./includes 

DIR_SRCS    = srcs
DIR_OBJS    = objs
DIR_INCLUDES= includes

DIR_LEXER   = lexer
DIR_PARSER  = parser
DIR_EXPANDER= expander
DIR_BUILTINS= builtins
DIR_ENV     = env
DIR_EXECUTOR= executor

# ================= FILES =================

FILES_LEXER = lexer_free_utils.c lexer_operators.c lexer_print_err.c \
              lexer_reader.c lexer_segs.c lexer_tokens.c lexer_utils.c \
              lexer.c

FILES_PARSER = parser_ast_builder.c parser.c parser_print_err.c \
               parser_utils2.c parser_builder.c parser_free.c \
               parser_segs.c parser_utils.c

FILES_EXPANDER = expander.c

FILES_BUILTINS = built_cd.c built_echo.c built_env.c built_exit.c \
                 built_export.c built_pwd.c built_unset.c built_utils.c

FILES_EXECUTOR = exec_and.c exec_append.c exec_ast.c exec_cmd.c \
                 exec_or.c exec_pipe.c exec_redirect.c exec_root.c \
                 exec_subshell.c exec_get_path.c exec_throw_error.c exec_built.c

# FILES_ENV = env.c env_utils.c env_list.c

# ================= SRCS =================

SRCS_LEXER     = $(addprefix $(DIR_SRCS)/$(DIR_LEXER)/, $(FILES_LEXER))
SRCS_PARSER   = $(addprefix $(DIR_SRCS)/$(DIR_PARSER)/, $(FILES_PARSER))
SRCS_EXPANDER = $(addprefix $(DIR_SRCS)/$(DIR_EXPANDER)/, $(FILES_EXPANDER))
SRCS_BUILTINS = $(addprefix $(DIR_SRCS)/$(DIR_BUILTINS)/, $(FILES_BUILTINS))
SRCS_EXECUTOR = $(addprefix $(DIR_SRCS)/$(DIR_EXECUTOR)/, $(FILES_EXECUTOR))
# SRCS_ENV      = $(addprefix $(DIR_SRCS)/$(DIR_ENV)/, $(FILES_ENV))

SRCS =  $(SRCS_LEXER) $(SRCS_PARSER) $(SRCS_EXPANDER) \
        $(SRCS_BUILTINS) $(SRCS_EXECUTOR) \
        $(DIR_SRCS)/main.c

# ================= OBJS =================

OBJS = $(SRCS:$(DIR_SRCS)/%.c=$(DIR_OBJS)/%.o)

# ================= LIBFT =================

LIBFT = $(DIR_INCLUDES)/libft/libft.a

# ================= RULES =================

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline -lhistory -lncurses

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(DIR_INCLUDES)/libft

clean:
	rm -rf $(DIR_OBJS)
	make -C $(DIR_INCLUDES)/libft clean

fclean: clean
	rm -rf $(NAME)
	make -C $(DIR_INCLUDES)/libft fclean

re: fclean all

.PHONY: all clean fclean re
