#include "../include/tetris.h"

void			put_pixel(int x, int y, t_color color, t_env *e)
{
	int				index;

	if (x >= 0  && y >= 0  && x < WIDTH - 2*BLOCK_SIZE  && y < HEIGHT- 2*BLOCK_SIZE)
	{
		index = y * e->size_line + (x * e->bpp/8);
		e->pixel[index] = color.r;
		e->pixel[++index] = color.g;
		e->pixel[++index] = color.b;
	}
}

void			put_box(int x, int y, t_piece *p, t_color color, t_board *b)
{
	int			i;
	int			j;
	
	j = -1;
	while (++j < BLOCK_SIZE)
	{
			i = -1;
			while (++i < BLOCK_SIZE)
			{
				put_pixel(x + i, y + j, color, b->e);

			}
	}
	//mlx_put_image_to_window(b->t->e->mlx, b->t->e->win,b->t->e->img, 0, 0);
}

