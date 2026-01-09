#include "executor.h"

t_ast *new_node(t_node_type type)
{
	t_ast	*node;

	node = calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
}

t_ast *ast_cmd(char **args)
{
	t_ast *node = new_node(NODE_CMD);
	node->args = args;
	return (node);
}

t_ast *ast_pipe(t_ast *left, t_ast *right)
{
	t_ast *node = new_node(NODE_PIPE);
	node->left = left;
	node->right = right;
	return (node);
}

t_ast *ast_redir_out(t_ast *cmd, char *filename)
{
	t_ast *node = new_node(NODE_REDIR_OUT);
	node->left = cmd;
	node->right = NULL;
	node->filename = filename;
	return (node);
}

void print_test_result(char *name, int expected, int got)
{
	if (expected == got)
		printf("✅ %s (return = %d)\n", name, got);
	else
		printf("❌ %s (expected %d, got %d)\n", name, expected, got);
}

void test_cmd_echo(t_shell *shell)
{
	char *args[] = {"/usr/bin/echo", "hello", NULL};
	t_ast *cmd;
	int ret;

	cmd = ast_cmd(args);
	ret = ft_exec_ast(cmd, shell);

	print_test_result("CMD echo hello", 0, ret);
}

void test_pipe_echo_wc(t_shell *shell)
{
	t_ast *left;
	t_ast *right;
	t_ast *pipe;
	int ret;

	left = ast_cmd((char *[]){"/usr/bin/echo", "hello", NULL});
	right = ast_cmd((char *[]){"/usr/bin/wc", "-c", NULL});
	pipe = ast_pipe(left, right);

	ret = ft_exec_ast(pipe, shell);
	print_test_result("PIPE echo | wc", 0, ret);
}

void test_redir_out(t_shell *shell)
{
	t_ast *cmd;
	t_ast *redir;
	int ret;

	cmd = ast_cmd((char *[]){"/usr/bin/echo", "hello", NULL});
	redir = ast_redir_out(cmd, "out_test.txt");

	ret = ft_exec_ast(redir, shell);
	print_test_result("REDIR_OUT echo > file", 0, ret);
}

void test_redir_out2(t_shell *shell)
{
	t_ast *cmd;
	t_ast *redir;
	int ret;

	cmd = ast_cmd((char *[]){"/usr/bin/echo", "akim", NULL});
	redir = ast_redir_out(cmd, "out_test2.txt");

	ret = ft_exec_ast(redir, shell);
	print_test_result("REDIR_OUT echo > file", 0, ret);
}

void test_pipe_nested(t_shell *shell)
{
	t_ast *n1;
	t_ast *n2;
	t_ast *n3;
	t_ast *pipe1;
	t_ast *pipe2;
	int ret;

	n1 = ast_cmd((char *[]){"/usr/bin/echo", "hello", NULL});
	n2 = ast_cmd((char *[]){"/bin/cat", NULL});
	n3 = ast_cmd((char *[]){"/usr/bin/wc", "-c", NULL});

	pipe1 = ast_pipe(n1, n2);     // echo | cat
	pipe2 = ast_pipe(pipe1, n3);  // (echo | cat) | wc

	ret = ft_exec_ast(pipe2, shell);
	print_test_result("PIPE echo | cat | wc", 0, ret);
}

void test_subshell_redir_out(t_shell *shell)
{
	t_ast *cmd;
	t_ast *subshell;
	t_ast *redir;
	int ret;

	// echo hello
	cmd = ast_cmd((char *[]){"/usr/bin/echo", "hello", NULL});

	// (echo hello)
	subshell = new_node(NODE_SUBSHELL);
	subshell->left = cmd;

	// (echo hello) > out.txt
	redir = ast_redir_out(subshell, "out_subshell.txt");

	ret = ft_exec_ast(redir, shell);
	print_test_result("SUBSHELL (echo) > file", 0, ret);
}




int main(int ac, char **av, char **envp)
{
	t_shell shell;

	memset(&shell, 0, sizeof(t_shell));
	shell.envp = envp;
	shell.in_pipeline = FALSE;
	printf("===== EXEC_AST TESTS =====\n");

	// test_cmd_echo(&shell);
	// test_pipe_echo_wc(&shell);
	// test_redir_out(&shell);
	test_subshell_redir_out(&shell);

	printf("==========================\n");
	return (0);
}



