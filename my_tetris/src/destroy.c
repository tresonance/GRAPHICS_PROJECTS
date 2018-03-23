#include "../include/tetris.h"

void				destroy_all(t_board **b)
{
	if (*b)
	{
		(*b)->e->pixel ? ft_memdel((void**)&(*b)->e->pixel) : 0;
		(*b)->e->img ? ft_memdel((void**)&(*b)->e->img) : 0;
		(*b)->e->win ? ft_memdel((void**)&(*b)->e->win): 0;
		//(void)(*t)->e;
		(*b)->e ? ft_memdel((void**)(*b)->e): 0;
		ft_memdel((void**)*b);
	}
}

int					clear_env(t_board *b)
{
	destroy_all(&b);
	exit(1);
	return (0);
}
