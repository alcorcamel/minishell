#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_ast *new_node(t_node_type type)
{
	t_ast *node = calloc(1, sizeof(t_ast));
	if (!node) return NULL;
	node->type = type;
	return node;
}

t_ast *ast_cmd(char **args)
{
	t_ast *node = new_node(NODE_CMD);
	node->args = args;
	return node;
}

t_ast *ast_pipe(t_ast *left, t_ast *right)
{
	t_ast *node = new_node(NODE_PIPE);
	node->left = left;
	node->right = right;
	return node;
}

t_ast *ast_redir_out(t_ast *cmd, char *filename)
{
	t_ast *node = new_node(NODE_REDIR_OUT);
	node->left = cmd;
	node->filename = filename;
	return node;
}

t_ast *ast_redir_in(t_ast *cmd, char *filename)
{
	t_ast *node = new_node(NODE_REDIR_IN);
	node->left = cmd;
	node->filename = filename;
	return node;
}

t_ast *ast_subshell(t_ast *child)
{
	t_ast *node = new_node(NODE_SUBSHELL);
	node->left = child;
	return node;
}

t_ast *ast_and(t_ast *left, t_ast *right)
{
	t_ast *node = new_node(NODE_AND);
	node->left = left;
	node->right = right;
	return node;
}

t_ast *ast_or(t_ast *left, t_ast *right)
{
	t_ast *node = new_node(NODE_OR);
	node->left = left;
	node->right = right;
	return node;
}

void print_test_result(char *name, int expected, int got)
{
	if (expected == got)
		printf("✅ %s (return = %d)\n", name, got);
	else
		printf("❌ %s (expected %d, got %d)\n", name, expected, got);
}

void test1_cmd_echo(t_shell *shell)
{
	//echo hello
	t_ast *cmd = ast_cmd((char *[]){"", NULL});
	int ret = ft_exec_root(cmd, shell);
	print_test_result("1. CMD echo hello", 0, ret);
}

void test2_pipe_echo_wc(t_shell *shell)
{
	// echo hello | wc -c
	t_ast *pipe = ast_pipe(
		ast_cmd((char *[]){"echo", "hello", NULL}),
		ast_cmd((char *[]){"wc", "-c", NULL})
	);
	int ret = ft_exec_root(pipe, shell);
	print_test_result("2. PIPE echo | wc", 0, ret);
}

void test3_pipe_multiple(t_shell *shell)
{
	// echo hello | cat | wc -c
	t_ast *pipe = ast_pipe(
		ast_pipe(
			ast_cmd((char *[]){"echo", "hello", NULL}),
			ast_cmd((char *[]){"/bin/cat", NULL})
		),
		ast_cmd((char *[]){"wc", "-c", NULL})
	);
	int ret = ft_exec_root(pipe, shell);
	print_test_result("3. PIPE echo | cat | wc", 0, ret);
}

void test4_redir_out(t_shell *shell)
{
	// echo test4 > test4.txt
	t_ast *redir = ast_redir_out(
		ast_cmd((char *[]){"echo", "test4", NULL}),
		"test4.txt"
	);
	int ret = ft_exec_root(redir, shell);
	print_test_result("4. REDIR_OUT echo > file", 0, ret);
}

void test5_redir_in_pipe(t_shell *shell)
{
	// cat | wc < test4.txt
	t_ast *pipe = ast_pipe(
		ast_cmd((char *[]){"/bin/cat", NULL}),
		ast_redir_in(ast_cmd((char *[]){"wc", NULL}), "test4.txt")
	);
	int ret = ft_exec_root(pipe, shell);
	print_test_result("5. PIPE cat | wc < file", 0, ret);
}

void test6_subshell_redir(t_shell *shell)
{
	// (echo hello) > test6.txt
	t_ast *redir = ast_redir_out(
		ast_subshell(ast_cmd((char *[]){"echo", "hello", NULL})),
		"test6.txt"
	);
	int ret = ft_exec_root(redir, shell);
	print_test_result("6. SUBSHELL (echo) > file", 0, ret);
}

void test7_subshell_pipe(t_shell *shell)
{
	// (echo hello) | (wc -c)
	t_ast *pipe = ast_pipe(
		ast_subshell(ast_cmd((char *[]){"echo", "hello", NULL})),
		ast_subshell(ast_cmd((char *[]){"wc", "-c", NULL}))
	);
	int ret = ft_exec_root(pipe, shell);
	print_test_result("7. PIPE (echo) | (wc)", 0, ret);
}

void test8_pipe_subshell_redir(t_shell *shell)
{
	// (echo hi > test8.txt) | (wc -c)
	t_ast *pipe = ast_pipe(
		ast_subshell(ast_redir_out(ast_cmd((char *[]){"echo", "hi", NULL}), "test8.txt")),
		ast_subshell(ast_cmd((char *[]){"wc", "-c", NULL}))
	);
	int ret = ft_exec_root(pipe, shell);
	print_test_result("8. PIPE (echo > file) | (wc)", 0, ret);
}

void test9_nested_subshells(t_shell *shell)
{
	// ((echo nested))
	t_ast *sub = ast_subshell(
		ast_subshell(ast_cmd((char *[]){"echo", "nested", NULL}))
	);
	int ret = ft_exec_root(sub, shell);
	print_test_result("9. Nested SUBSHELLS ((echo))", 0, ret);
}

void test10_complex_pipe_subshell(t_shell *shell)
{
	// ((echo a | cat) | (wc -c | cat))
	t_ast *pipe = ast_pipe(
		ast_subshell(ast_pipe(
			ast_cmd((char *[]){"echo", "a", NULL}),
			ast_cmd((char *[]){"/bin/cat", NULL})
		)),
		ast_subshell(ast_pipe(
			ast_cmd((char *[]){"wc", "-c", NULL}),
			ast_cmd((char *[]){"/bin/cat", NULL})
		))
	);
	int ret = ft_exec_root(pipe, shell);
	print_test_result("10. Complex PIPE + SUBSHELLS", 0, ret);
}

void test11_cat_pipe_wc(t_shell *shell)
{
	// cat | wc -l
	t_ast *pipe = ast_pipe(
		ast_cmd((char *[]){"/bin/cat", NULL}),
		ast_cmd((char *[]){"wc", "-l", NULL})
	);
	int ret = ft_exec_root(pipe, shell);
	print_test_result("11. CMD cat | wc -l", 0, ret);
}

void test12_echo_pipe_subshell_wc(t_shell *shell)
{
	// echo "hello\nworld" | (wc -l)
	t_ast *pipe = ast_pipe(
		ast_cmd((char *[]){"echo", "hello\nworld", NULL}),
		ast_subshell(ast_cmd((char *[]){"wc", "-l", NULL}))
	);
	int ret = ft_exec_root(pipe, shell);
	print_test_result("12. PIPE echo | (wc -l)", 0, ret);
}

void test13_pipe_redir_in_out(t_shell *shell)
{
	// < test4.txt cat | wc -c > test13.txt
	t_ast *pipe = ast_pipe(
		ast_redir_in(ast_cmd((char *[]){"/bin/cat", NULL}), "test4.txt"),
		ast_redir_out(ast_cmd((char *[]){"wc", "-c", NULL}), "test13.txt")
	);
	int ret = ft_exec_root(pipe, shell);
	print_test_result("13. PIPE < file | wc > file", 0, ret);
}

void test14_subshell_pipe_redir(t_shell *shell)
{
	// (echo hi > test14.txt) | ((wc -c) > test14b.txt)
	t_ast *pipe = ast_pipe(
		ast_subshell(ast_redir_out(ast_cmd((char *[]){"echo", "hi", NULL}), "test14.txt")),
		ast_redir_out(ast_subshell(ast_cmd((char *[]){"wc", "-c", NULL})), "test14b.txt")
	);
	int ret = ft_exec_root(pipe, shell);
	print_test_result("14. PIPE (echo > file) | (wc > file)", 0, ret);
}

void test15_double_pipe_subshell(t_shell *shell)
{
	// ((echo x) | (cat)) | (wc -c)
	t_ast *pipe = ast_pipe(
		ast_pipe(
			ast_subshell(ast_cmd((char *[]){"echo", "x", NULL})),
			ast_subshell(ast_cmd((char *[]){"/bin/cat", NULL}))
		),
		ast_subshell(ast_cmd((char *[]){"wc", "-c", NULL}))
	);
	int ret = ft_exec_root(pipe, shell);
	print_test_result("15. Double PIPE + SUBSHELLS", 0, ret);
}

void test16_pipe_cat_subshell(t_shell *shell)
{
	// echo "signal test" | (cat)
	t_ast *pipe = ast_pipe(
		ast_cmd((char *[]){"echo", "signal test", NULL}),
		ast_subshell(ast_cmd((char *[]){"/bin/cat", NULL}))
	);
	int ret = ft_exec_root(pipe, shell);
	print_test_result("16. PIPE echo | (cat) signal test", 0, ret);
}

void test17_nested_pipe_subshell_redir(t_shell *shell)
{
	// ((echo nested | cat) > test17.txt) | ((wc -c) > test17b.txt)
	t_ast *pipe = ast_pipe(
		ast_subshell(ast_redir_out(ast_pipe(
			ast_cmd((char *[]){"echo", "nested", NULL}),
			ast_cmd((char *[]){"/bin/cat", NULL})
		), "test17.txt")),
		ast_subshell(ast_redir_out(ast_cmd((char *[]){"wc", "-c", NULL}), "test17b.txt"))
	);
	int ret = ft_exec_root(pipe, shell);
	print_test_result("17. Nested PIPE + SUBSHELLS + REDIR", 0, ret);
}

void test18_multiple_pipes_subshells(t_shell *shell)
{
	// ((echo multi) | (cat)) | ((wc -c) | (cat))
	t_ast *pipe = ast_pipe(
		ast_pipe(
			ast_subshell(ast_cmd((char *[]){"echo", "multi", NULL})),
			ast_subshell(ast_cmd((char *[]){"/bin/cat", NULL}))
		),
		ast_pipe(
			ast_subshell(ast_cmd((char *[]){"wc", "-c", NULL})),
			ast_subshell(ast_cmd((char *[]){"/bin/cat", NULL}))
		)
	);
	int ret = ft_exec_root(pipe, shell);
	print_test_result("18. Multiple PIPE + SUBSHELLS", 0, ret);
}

void test19_subshell_redir_pipe(t_shell *shell)
{
	// (echo hello > test19.txt) | cat
	t_ast *pipe = ast_pipe(
		ast_subshell(ast_redir_out(ast_cmd((char *[]){"echo", "hello", NULL}), "test19.txt")),
		ast_cmd((char *[]){"/bin/cat", NULL})
	);
	int ret = ft_exec_root(pipe, shell);
	print_test_result("19. SUBSHELL > file | cat", 0, ret);
}

void test20_complex_nested(t_shell *shell)
{
	// ((echo final > test20.txt) | (cat | wc -c)) | (wc -c < test20.txt)
	t_ast *pipe = ast_pipe(
		ast_pipe(
			ast_subshell(ast_redir_out(ast_cmd((char *[]){"echo", "final", NULL}), "test20.txt")),
			ast_subshell(ast_pipe(
				ast_cmd((char *[]){"/bin/cat", NULL}),
				ast_cmd((char *[]){"wc", "-c", NULL})
			))
		),
		ast_subshell(ast_redir_in(ast_cmd((char *[]){"wc", "-c", NULL}), "test20.txt"))
	);
	int ret = ft_exec_root(pipe, shell);
	print_test_result("20. Complex nested PIPE + SUBSHELLS + REDIR", 0, ret);
}

void test21_and_success(t_shell *shell)
{
	// echo hello && echo world
	t_ast *cmd = ast_and(
		ast_cmd((char *[]){"echo", "hello", NULL}),
		ast_cmd((char *[]){"echo", "world", NULL})
	);
	int ret = ft_exec_root(cmd, shell);
	print_test_result("21. AND success", 0, ret);
}

void test22_and_fail(t_shell *shell)
{
	// false && echo wontexecute
	t_ast *cmd = ast_and(
		ast_cmd((char *[]){"/bin/false", NULL}),
		ast_cmd((char *[]){"echo", "wontexecute", NULL})
	);
	int ret = ft_exec_root(cmd, shell);
	print_test_result("22. AND fail", 1, ret); // false retourne 1
}

void test23_or_success(t_shell *shell)
{
	// true || echo notexecuted
	t_ast *cmd = ast_or(
		ast_cmd((char *[]){"/bin/true", NULL}),
		ast_cmd((char *[]){"echo", "notexecuted", NULL})
	);
	int ret = ft_exec_root(cmd, shell);
	print_test_result("23. OR success", 0, ret);
}

void test24_or_fail(t_shell *shell)
{
	// false || echo executed
	t_ast *cmd = ast_or(
		ast_cmd((char *[]){"/bin/false", NULL}),
		ast_cmd((char *[]){"echo", "executed", NULL})
	);
	int ret = ft_exec_root(cmd, shell);
	print_test_result("24. OR fail", 0, ret);
}

void test25_and_pipe(t_shell *shell)
{
	// echo a | wc && echo b
	t_ast *cmd = ast_and(
		ast_pipe(
			ast_cmd((char *[]){"echo", "a", NULL}),
			ast_cmd((char *[]){"wc", "-c", NULL})
		),
		ast_cmd((char *[]){"echo", "b", NULL})
	);
	int ret = ft_exec_root(cmd, shell);
	print_test_result("25. AND with pipe", 0, ret);
}

void test26_or_pipe_fail(t_shell *shell)
{
	// false | wc || echo executed
	t_ast *cmd = ast_or(
		ast_pipe(
			ast_cmd((char *[]){"/bin/false", NULL}),
			ast_cmd((char *[]){"wc", "-c", NULL})
		),
		ast_cmd((char *[]){"echo", "executed", NULL})
	);
	int ret = ft_exec_root(cmd, shell);
	print_test_result("26. OR with pipe and fail", 0, ret);
}

void test27_and_subshell(t_shell *shell)
{
	// (echo hi) && (echo bye)
	t_ast *cmd = ast_and(
		ast_subshell(ast_cmd((char *[]){"echo", "hi", NULL})),
		ast_subshell(ast_cmd((char *[]){"echo", "bye", NULL}))
	);
	int ret = ft_exec_root(cmd, shell);
	print_test_result("27. AND with subshells", 0, ret);
}

void test28_or_subshell_fail(t_shell *shell)
{
	// (false) || (echo executed)
	t_ast *cmd = ast_or(
		ast_subshell(ast_cmd((char *[]){"/bin/false", NULL})),
		ast_subshell(ast_cmd((char *[]){"echo", "executed", NULL}))
	);
	int ret = ft_exec_root(cmd, shell);
	print_test_result("28. OR with subshells fail", 0, ret);
}

void test29_complex_and_or(t_shell *shell)
{
	// (echo a | wc) && (false || echo executed)
	t_ast *cmd = ast_and(
		ast_pipe(
			ast_cmd((char *[]){"echo", "a", NULL}),
			ast_cmd((char *[]){"wc", "-c", NULL})
		),
		ast_or(
			ast_cmd((char *[]){"/bin/false", NULL}),
			ast_cmd((char *[]){"echo", "executed", NULL})
		)
	);
	int ret = ft_exec_root(cmd, shell);
	print_test_result("29. Complex AND/OR with pipe", 0, ret);
}

void test30_and_or_subshell_redir(t_shell *shell)
{
	// ((echo a > file1) && (echo b > file2)) || (echo c > file3)
	t_ast *cmd = ast_or(
		ast_and(
			ast_redir_out(ast_cmd((char *[]){"cat", NULL}), "file1"),
			ast_redir_out(ast_cmd((char *[]){"echo", "b", NULL}), "file2")
		),
		ast_redir_out(ast_cmd((char *[]){"echo", "c", NULL}), "file3")
	);
	int ret = ft_exec_root(cmd, shell);
	print_test_result("30. AND/OR with subshells and redir", 0, ret);
}

// ----------------------- MAIN -----------------------

int main(int ac, char **av, char **envp)
{
	t_shell shell;
	shell.envp = envp;
	printf("===== EXEC_AST STRESS TESTS =====\n");

	test1_cmd_echo(&shell);
	test2_pipe_echo_wc(&shell);
	test3_pipe_multiple(&shell);
	test4_redir_out(&shell);
	test5_redir_in_pipe(&shell);
	test6_subshell_redir(&shell);
	test7_subshell_pipe(&shell);
	test8_pipe_subshell_redir(&shell);
	test9_nested_subshells(&shell);
	test10_complex_pipe_subshell(&shell);
	test11_cat_pipe_wc(&shell);
	test12_echo_pipe_subshell_wc(&shell);
	test13_pipe_redir_in_out(&shell);
	test14_subshell_pipe_redir(&shell);
	test15_double_pipe_subshell(&shell);
	test16_pipe_cat_subshell(&shell);
	test17_nested_pipe_subshell_redir(&shell);
	test18_multiple_pipes_subshells(&shell);
	test19_subshell_redir_pipe(&shell);
	test20_complex_nested(&shell);
	test21_and_success(&shell);
	test22_and_fail(&shell);
	test23_or_success(&shell);
	test24_or_fail(&shell);
	test25_and_pipe(&shell);
	test26_or_pipe_fail(&shell);
	test27_and_subshell(&shell);
	test28_or_subshell_fail(&shell);
	test29_complex_and_or(&shell);
	test30_and_or_subshell_redir(&shell);


	printf("===== END OF TESTS =====\n");
	return 0;
}

