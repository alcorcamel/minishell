#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "lexer.h"

/* Ton AST / segs (rappels) :
typedef enum e_segtype { SEG_RAW, SEG_SQ, SEG_DQ, SEG_SEP } t_segtype;
typedef struct s_seg { t_segtype type; char *text; struct s_seg *next; } t_seg;

typedef enum e_node_type {
    NODE_CMD, NODE_PIPE, NODE_REDIR_IN, NODE_REDIR_OUT, NODE_REDIR_APPEND,
    NODE_HEREDOC, NODE_AND, NODE_OR, NODE_SUBSHELL,
} t_node_type;

typedef struct s_ast {
    t_node_type type;
    struct s_ast *left;
    struct s_ast *right;
    char **args;
    t_seg *segs;
    char *filename;
    char *limiter;
} t_ast;
*/

static int seg_is_sep(const t_seg *s)
{
    return (s && s->type == SEG_SEP);
}

static const char *ast_type_str(t_node_type t)
{
    switch (t)
    {
        case NODE_CMD:          return "CMD";
        case NODE_PIPE:         return "PIPE";
        case NODE_REDIR_IN:     return "REDIR_IN";
        case NODE_REDIR_OUT:    return "REDIR_OUT";
        case NODE_REDIR_APPEND: return "APPEND";
        case NODE_HEREDOC:      return "HEREDOC";
        case NODE_AND:          return "AND";
        case NODE_OR:           return "OR";
        case NODE_SUBSHELL:     return "SUBSHELL";
        default:                return "UNKNOWN";
    }
}

/* Construit un aperçu lisible de la liste de segs.
   - SEG_SEP => " ␠ "
   - SEG_SQ  => '...'
   - SEG_DQ  => "..."
   - SEG_RAW => texte brut
   Troncature si ça dépasse.
*/
static void segs_preview(const t_seg *s, char *buf, size_t cap)
{
    size_t len = 0;
    int first = 1;

    if (!buf || cap == 0)
        return;
    buf[0] = '\0';

    while (s && len + 8 < cap) /* marge */
    {
        const char *txt = (s->text ? s->text : "");
        char chunk[128];

        chunk[0] = '\0';

        if (seg_is_sep(s))
            snprintf(chunk, sizeof(chunk), "%s␠", first ? "" : " ");
        else if (s->type == SEG_SQ)
            snprintf(chunk, sizeof(chunk), "%s'%s'", first ? "" : "", txt);
        else if (s->type == SEG_DQ)
            snprintf(chunk, sizeof(chunk), "%s\"%s\"", first ? "" : "", txt);
        else
            snprintf(chunk, sizeof(chunk), "%s%s", first ? "" : "", txt);

        size_t add = strlen(chunk);
        if (len + add + 1 >= cap)
            break;

        memcpy(buf + len, chunk, add);
        len += add;
        buf[len] = '\0';

        first = 0;
        s = s->next;
    }

    if (s && len + 4 < cap) {
        strcat(buf, "...");
    }
}

static void ast_print_rec(const t_ast *n, const char *prefix, int is_last)
{
    char next_prefix[1024];
    char extra[512];
    int has_left, has_right;

    if (!n)
        return;

    extra[0] = '\0';

    /* Infos supplémentaires utiles */
    if (n->type == NODE_CMD && n->segs) {
        char p[256];
        segs_preview(n->segs, p, sizeof(p));
        snprintf(extra, sizeof(extra), "  segs=[%s]", p);
    }
    else if ((n->type == NODE_REDIR_IN || n->type == NODE_REDIR_OUT
            || n->type == NODE_REDIR_APPEND || n->type == NODE_HEREDOC) && n->segs) {
        char p[256];
        segs_preview(n->segs, p, sizeof(p));
        snprintf(extra, sizeof(extra), "  arg=[%s]", p);
    }
    else if (n->type == NODE_HEREDOC && n->limiter) {
        snprintf(extra, sizeof(extra), "  limiter=\"%s\"", n->limiter);
    }
    else if ((n->type == NODE_REDIR_IN || n->type == NODE_REDIR_OUT
           || n->type == NODE_REDIR_APPEND) && n->filename) {
        snprintf(extra, sizeof(extra), "  file=\"%s\"", n->filename);
    }

    printf("%s%s%s%s\n",
        (prefix ? prefix : ""),
        (prefix && prefix[0]) ? (is_last ? "└── " : "├── ") : "",
        ast_type_str(n->type),
        extra);

    /* Prépare le préfixe pour les enfants */
    if (!prefix) prefix = "";
    snprintf(next_prefix, sizeof(next_prefix), "%s%s",
             prefix,
             (prefix[0] ? (is_last ? "    " : "│   ") : ""));

    has_left = (n->left != NULL);
    has_right = (n->right != NULL);

    if (has_left && has_right) {
        ast_print_rec(n->left,  next_prefix, 0);
        ast_print_rec(n->right, next_prefix, 1);
    } else if (has_left) {
        ast_print_rec(n->left, next_prefix, 1);
    } else if (has_right) {
        ast_print_rec(n->right, next_prefix, 1);
    }
}

void ast_print(const t_ast *root)
{
    if (!root) {
        printf("(AST) (null)\n");
        return;
    }
    /* Racine sans connecteur, puis récursion */
    printf("(AST)\n");
    ast_print_rec(root, "", 1);
}
