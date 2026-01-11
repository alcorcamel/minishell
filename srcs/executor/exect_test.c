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

void print_test_result(char *name, int expected, int got)
{
	if (expected == got)
		printf("✅ %s (return = %d)\n", name, got);
	else
		printf("❌ %s (expected %d, got %d)\n", name, expected, got);
}

// ----------------------- TESTS -----------------------

void test1_cmd_echo(char **envp)
{
	t_ast *cmd = ast_cmd((char *[]){"/usr/bin/echo", "hello", NULL});
	int ret = ft_exec_root(cmd, envp);
	print_test_result("1. CMD echo hello", 0, ret);
}

void test2_pipe_echo_wc(char **envp)
{
	t_ast *pipe = ast_pipe(
		ast_cmd((char *[]){"/usr/bin/echo", "hello", NULL}),
		ast_cmd((char *[]){"/usr/bin/wc", "-c", NULL})
	);
	int ret = ft_exec_root(pipe, envp);
	print_test_result("2. PIPE echo | wc", 0, ret);
}

void test3_pipe_multiple(char **envp)
{
	t_ast *pipe = ast_pipe(
		ast_pipe(
			ast_cmd((char *[]){"/usr/bin/echo", "hello", NULL}),
			ast_cmd((char *[]){"/bin/cat", NULL})
		),
		ast_cmd((char *[]){"/usr/bin/wc", "-c", NULL})
	);
	int ret = ft_exec_root(pipe, envp);
	print_test_result("3. PIPE echo | cat | wc", 0, ret);
}

void test4_redir_out(char **envp)
{
	t_ast *redir = ast_redir_out(
		ast_cmd((char *[]){"/usr/bin/echo", "test4", NULL}),
		"test4.txt"
	);
	int ret = ft_exec_root(redir, envp);
	print_test_result("4. REDIR_OUT echo > file", 0, ret);
}

void test5_redir_in_pipe(char **envp)
{
	t_ast *pipe = ast_pipe(
		ast_cmd((char *[]){"/bin/cat", NULL}),
		ast_redir_in(ast_cmd((char *[]){"/usr/bin/wc", NULL}), "test4.txt")
	);
	int ret = ft_exec_root(pipe, envp);
	print_test_result("5. PIPE cat | wc < file", 0, ret);
}

void test6_subshell_redir(char **envp)
{
	t_ast *redir = ast_redir_out(
		ast_subshell(ast_cmd((char *[]){"/usr/bin/echo", "hello", NULL})),
		"test6.txt"
	);
	int ret = ft_exec_root(redir, envp);
	print_test_result("6. SUBSHELL (echo) > file", 0, ret);
}

void test7_subshell_pipe(char **envp)
{
	t_ast *pipe = ast_pipe(
		ast_subshell(ast_cmd((char *[]){"/usr/bin/echo", "hello", NULL})),
		ast_subshell(ast_cmd((char *[]){"/usr/bin/wc", "-c", NULL}))
	);
	int ret = ft_exec_root(pipe, envp);
	print_test_result("7. PIPE (echo) | (wc)", 0, ret);
}

void test8_pipe_subshell_redir(char **envp)
{
	t_ast *pipe = ast_pipe(
		ast_subshell(ast_redir_out(ast_cmd((char *[]){"/usr/bin/echo", "hi", NULL}), "test8.txt")),
		ast_subshell(ast_cmd((char *[]){"/usr/bin/wc", "-c", NULL}))
	);
	int ret = ft_exec_root(pipe, envp);
	print_test_result("8. PIPE (echo > file) | (wc)", 0, ret);
}

void test9_nested_subshells(char **envp)
{
	t_ast *sub = ast_subshell(
		ast_subshell(ast_cmd((char *[]){"/usr/bin/echo", "nested", NULL}))
	);
	int ret = ft_exec_root(sub, envp);
	print_test_result("9. Nested SUBSHELLS ((echo))", 0, ret);
}

void test10_complex_pipe_subshell(char **envp)
{
	t_ast *pipe = ast_pipe(
		ast_subshell(ast_pipe(
			ast_cmd((char *[]){"/usr/bin/echo", "a", NULL}),
			ast_cmd((char *[]){"/bin/cat", NULL})
		)),
		ast_subshell(ast_pipe(
			ast_cmd((char *[]){"/usr/bin/wc", "-c", NULL}),
			ast_cmd((char *[]){"/bin/cat", NULL})
		))
	);
	int ret = ft_exec_root(pipe, envp);
	print_test_result("10. Complex PIPE + SUBSHELLS", 0, ret);
}

// ------------------- tests avancés -------------------

void test11_cat_pipe_wc(char **envp)
{
	t_ast *pipe = ast_pipe(
		ast_cmd((char *[]){"/bin/cat", NULL}),
		ast_cmd((char *[]){"/usr/bin/wc", "-l", NULL})
	);
	int ret = ft_exec_root(pipe, envp);
	print_test_result("11. CMD cat | wc -l", 0, ret);
}

void test12_echo_pipe_subshell_wc(char **envp)
{
	t_ast *pipe = ast_pipe(
		ast_cmd((char *[]){"/usr/bin/echo", "hello\nworld", NULL}),
		ast_subshell(ast_cmd((char *[]){"/usr/bin/wc", "-l", NULL}))
	);
	int ret = ft_exec_root(pipe, envp);
	print_test_result("12. PIPE echo | (wc -l)", 0, ret);
}

void test13_pipe_redir_in_out(char **envp)
{
	t_ast *pipe = ast_pipe(
		ast_redir_in(ast_cmd((char *[]){"/bin/cat", NULL}), "test4.txt"),
		ast_redir_out(ast_cmd((char *[]){"/usr/bin/wc", "-c", NULL}), "test13.txt")
	);
	int ret = ft_exec_root(pipe, envp);
	print_test_result("13. PIPE < file | wc > file", 0, ret);
}

void test14_subshell_pipe_redir(char **envp)
{
	t_ast *pipe = ast_pipe(
		ast_subshell(ast_redir_out(ast_cmd((char *[]){"/usr/bin/echo", "hi", NULL}), "test14.txt")),
		ast_redir_out(ast_subshell(ast_cmd((char *[]){"/usr/bin/wc", "-c", NULL})), "test14b.txt")
	);
	int ret = ft_exec_root(pipe, envp);
	print_test_result("14. PIPE (echo > file) | (wc > file)", 0, ret);
}

void test15_double_pipe_subshell(char **envp)
{
	t_ast *pipe = ast_pipe(
		ast_pipe(
			ast_subshell(ast_cmd((char *[]){"/usr/bin/echo", "x", NULL})),
			ast_subshell(ast_cmd((char *[]){"/bin/cat", NULL}))
		),
		ast_subshell(ast_cmd((char *[]){"/usr/bin/wc", "-c", NULL}))
	);
	int ret = ft_exec_root(pipe, envp);
	print_test_result("15. Double PIPE + SUBSHELLS", 0, ret);
}

void test16_pipe_cat_subshell(char **envp)
{
	t_ast *pipe = ast_pipe(
		ast_cmd((char *[]){"/usr/bin/echo", "signal test", NULL}),
		ast_subshell(ast_cmd((char *[]){"/bin/cat", NULL}))
	);
	int ret = ft_exec_root(pipe, envp);
	print_test_result("16. PIPE echo | (cat) signal test", 0, ret);
}

void test17_nested_pipe_subshell_redir(char **envp)
{
	t_ast *pipe = ast_pipe(
		ast_subshell(ast_redir_out(ast_pipe(
			ast_cmd((char *[]){"/usr/bin/echo", "nested", NULL}),
			ast_cmd((char *[]){"/bin/cat", NULL})
		), "test17.txt")),
		ast_subshell(ast_redir_out(ast_cmd((char *[]){"/usr/bin/wc", "-c", NULL}), "test17b.txt"))
	);
	int ret = ft_exec_root(pipe, envp);
	print_test_result("17. Nested PIPE + SUBSHELLS + REDIR", 0, ret);
}

void test18_multiple_pipes_subshells(char **envp)
{
	t_ast *pipe = ast_pipe(
		ast_pipe(
			ast_subshell(ast_cmd((char *[]){"/usr/bin/echo", "multi", NULL})),
			ast_subshell(ast_cmd((char *[]){"/bin/cat", NULL}))
		),
		ast_pipe(
			ast_subshell(ast_cmd((char *[]){"/usr/bin/wc", "-c", NULL})),
			ast_subshell(ast_cmd((char *[]){"/bin/cat", NULL}))
		)
	);
	int ret = ft_exec_root(pipe, envp);
	print_test_result("18. Multiple PIPE + SUBSHELLS", 0, ret);
}

void test19_subshell_redir_pipe(char **envp)
{
	t_ast *pipe = ast_pipe(
		ast_subshell(ast_redir_out(ast_cmd((char *[]){"/usr/bin/echo", "hello", NULL}), "test19.txt")),
		ast_cmd((char *[]){"/bin/cat", NULL})
	);
	int ret = ft_exec_root(pipe, envp);
	print_test_result("19. SUBSHELL > file | cat", 0, ret);
}

void test20_complex_nested(char **envp)
{
	t_ast *pipe = ast_pipe(
		ast_pipe(
			ast_subshell(ast_redir_out(ast_cmd((char *[]){"/usr/bin/echo", "final", NULL}), "test20.txt")),
			ast_subshell(ast_pipe(
				ast_cmd((char *[]){"/bin/cat", NULL}),
				ast_cmd((char *[]){"/usr/bin/wc", "-c", NULL})
			))
		),
		ast_subshell(ast_redir_in(ast_cmd((char *[]){"/usr/bin/wc", "-c", NULL}), "test20.txt"))
	);
	int ret = ft_exec_root(pipe, envp);
	print_test_result("20. Complex nested PIPE + SUBSHELLS + REDIR", 0, ret);
}

// ----------------------- MAIN -----------------------

int main(int ac, char **av, char **envp)
{
	printf("===== EXEC_AST STRESS TESTS =====\n");

	test1_cmd_echo(envp);
	test2_pipe_echo_wc(envp);
	test3_pipe_multiple(envp);
	test4_redir_out(envp);
	test5_redir_in_pipe(envp);
	test6_subshell_redir(envp);
	test7_subshell_pipe(envp);
	test8_pipe_subshell_redir(envp);
	test9_nested_subshells(envp);
	test10_complex_pipe_subshell(envp);
	test11_cat_pipe_wc(envp);
	test12_echo_pipe_subshell_wc(envp);
	test13_pipe_redir_in_out(envp);
	test14_subshell_pipe_redir(envp);
	test15_double_pipe_subshell(envp);
	test16_pipe_cat_subshell(envp);
	test17_nested_pipe_subshell_redir(envp);
	test18_multiple_pipes_subshells(envp);
	test19_subshell_redir_pipe(envp);
	test20_complex_nested(envp);

	printf("===== END OF TESTS =====\n");
	return 0;
}

