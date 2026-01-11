NAME = test

make: $(NAME)

$(NAME):
	cc ./exect_test.c ./exec_subshell.c ./exec_root.c ./exec_redirect.c ./exec_pipe.c ./exec_ast.c ./exec_cmd.c ./exec_and.c  ./exec_or.c  ../../includes/libft/*.c -I.  -I../../includes/ -o $(NAME)

clear:
	rm -rf test14b.txt test19.txt test8.txt test14.txt test20.txt test17b.txt test4.txt test13.txt test17.txt test6.txt file1 file2 $(NAME)