# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 11:33:07 by demane            #+#    #+#              #
#    Updated: 2026/01/14 13:28:17 by demane           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.
AR = @ar rcs
RM = @rm -f

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	   ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	   ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	   ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
	   ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
	   ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	   ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	   ft_intlen.c ft_maxint.c ft_minint.c ft_has_duplicates.c ft_putnbr_base_fd.c \
	   ft_atol.c ft_free.c ft_strjoin_sep.c ft_str_is_space.c

SRCS_PRINTF = printf/ft_printf.c printf/ft_char_utils.c printf/ft_format_parser.c printf/ft_hex_utils.c printf/ft_int_utils.c \
	   printf/ft_printf_utils.c printf/ft_ptr_utils.c printf/ft_str_utils.c printf/ft_unsignedint_utils.c		\
	   printf/ft_int_utils2.c printf/ft_args_utils.c

SRCS_GNL = get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c

SRCS_BONUS =  ft_lstlast.c ft_lstdelone.c ft_lstsize.c ft_lstclear.c \
			  ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c ft_lstiter.c ft_lstmap.c

OBJS = $(SRCS:.c=.o)

OBJS_PRINTF = $(SRCS_PRINTF:.c=.o)

OBJS_GNL = $(SRCS_GNL:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_PRINTF) $(OBJS_GNL) $(OBJS_BONUS)
	$(AR) $(NAME) $(OBJS) $(OBJS_PRINTF) $(OBJS_GNL) $(OBJS_BONUS)

bonus: $(OBJS_BONUS) $(OBJS) $(NAME)
	$(AR) $(NAME) $(OBJS) $(OBJS_PRINTF) $(OBJS_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_PRINTF) $(OBJS_BONUS) $(OBJS_GNL)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
