#include "../../includes/style.h"

void	ft_print_boot(void)
{
	ft_printf(
		C_BLUE
		"\n"
		"\n"
		"\n"
		"\n"
		"    ███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████╗██╗  ██╗██╗███████╗██╗     ██████╗\n"
		"    ████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════╝██║  ██║██║██╔════╝██║     ██╔══██╗\n"
		"    ██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████╗███████║██║█████╗  ██║     ██║  ██║\n"
		"    ██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██║██╔══██║██║██╔══╝  ██║     ██║  ██║\n"
		"    ██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████║██║  ██║██║███████╗███████╗██████╔╝\n"
		"    ╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════╝╚═╝  ╚═╝╚═╝╚══════╝╚══════╝╚═════╝\n"
		"\n"
		"\n"
		"\n"
		"\n"
		C_RESET);
}

char	*ft_shorten_path(char *cwd, t_shell *shell)
{
	char	*home;
	size_t	home_len;
	size_t	len;
	char	*short_path;

	home = ft_find_vars("HOME", shell)->value;
	if (!home)
		return (ft_strdup(cwd));
	home_len = ft_strlen(home);
	if (ft_strncmp(cwd, home, home_len) == 0)
	{
		len = ft_strlen(cwd) - home_len + 2;
		short_path = (char *)malloc(len);
		if (!short_path)
			return (ft_strdup(cwd));

		short_path[0] = '~';
		short_path[1] = '\0';
		ft_strlcat(short_path, cwd + home_len, len);
		return (short_path);
	}

	return (ft_strdup(cwd));
}


char	*ft_generate_prompt(t_shell *shell)
{
	char	*cwd;
	char	*path;
	char	*status_color;
	char	*prompt;
	size_t	prompt_len;

	cwd = getcwd(NULL, 0);
	path = ft_shorten_path(cwd, shell);
	ft_free((void **)&cwd);
	if (shell->last_status == 0)
		status_color = C_GREEN;
	else
		status_color = C_RED;
	prompt_len = ft_strlen(path) + 64;
	prompt = (char *)malloc(prompt_len);
	if (!prompt)
		return (ft_free((void **)path), ft_strdup("> "));
	prompt[0] = '\0';
	ft_strlcat(prompt, C_BLUE, prompt_len);
	ft_strlcat(prompt, "minishield ", prompt_len);
	ft_strlcat(prompt, C_RESET, prompt_len);
	ft_strlcat(prompt, status_color, prompt_len);
	ft_strlcat(prompt, path, prompt_len);
	ft_strlcat(prompt, C_RESET, prompt_len);
	ft_strlcat(prompt, " ❯ ", prompt_len);
	ft_free((void **)&path);
	return (prompt);
}
