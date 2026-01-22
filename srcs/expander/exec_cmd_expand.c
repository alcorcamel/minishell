#include "../../includes/executor.h"
#include "../../includes/expander.h"

int	ft_cmd_expand(t_ast *n, t_shell *shell)
{
	t_seg	*segs;

	segs = n->segs;
	if (!segs)
		return (0);
	if (!ft_var_translator(segs, shell))
		return (0);
	return (1);
}
