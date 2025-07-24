#include "./expand.h"

void *alloc(ssize_t);

t_expander *new_expander()
{
    t_expander *expander;

    expander = alloc(sizeof(t_expander));
    expander->queue = NULL;
    expander->old_len = 0;
    expander->new_len = 0;
    expander->is_default = true;

    return (expander);
}

t_expander *get_expander(bool recreate)
{
    static t_expander *expander = NULL;

    if (!expander || recreate)
        expander = new_expander();

    return (expander);
}