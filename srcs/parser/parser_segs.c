
#include "../../includes/parser.h"

void free_segs(t_seg *s)
{
	t_seg *next;

	while (s)
	{
		next = s->next;
		free(s->text);
		free(s);
		s = next;
	}
}

t_seg	*seg_last(t_seg *s)
{
	if (!s)
		return (NULL);
	while (s->next)
		s = s->next;
	return (s);
}

int	seg_append_words(t_seg **dst, t_seg *src)
{
	t_seg	*last;

	if (!src)
		return (1);
	if (!dst)
		return (0);
	if (!*dst)
		return (*dst = src, 1);
	last = seg_last(*dst);
	last->next = src;
	return (1);
}

t_seg	*seg_word_separator(void)
{
	t_seg	*sep;

	sep = (t_seg *)ft_calloc(1, sizeof(t_seg));
	if (!sep)
		return (NULL);
	sep->type = SEG_SEP;
	sep->text = (char *)ft_calloc(1, sizeof(char));
	if (!sep->text)
		return (free(sep), NULL);
	sep->next = NULL;
	return (sep);
}
