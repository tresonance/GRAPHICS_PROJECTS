#include "../include/tetris.h"

int				is_collision(int x, int y, t_piece *p, t_board *b)
{
	int			i;
	int			j;

	j = -1;
	while(++j < 4)
	{
		if (y + j >= HEIGHT)
			return (TRUE);
		i = -1;
		while (++i < 4)
		{
			if(x + i >= WIDTH)
				return (TRUE);
			if (p->piece[j][i]  > 0 && b->board[y /BLOCK_SIZE + j][x/BLOCK_SIZE + i] > 0 )
				return (TRUE);
		}
	}
	return (FALSE);
}

void			draw_box(int x, int y, t_piece *p, t_board *b)
{
	int			i;
	int			j;
	
	j = -1;
	while (++j < BLOCK_SIZE)
	{
			i = -1;
			while (++i < BLOCK_SIZE)
			{
				put_pixel(x + i, y + j, p->color, b->e);

			}
	}
	//mlx_put_image_to_window(b->t->e->mlx, b->t->e->win,b->t->e->img, 0, 0);
}

void			draw_piece(int x, int y, t_piece *p, t_board *b)
{
	int			i;
	int			j;

	if (is_collision(x, y, p, b))
		return ;
	j = -1;
	while (++j < 4)
	{
		i = -1;
		while (++i < 4)
		{
			if(p->piece[j][i])
			{
				b->board[y/BLOCK_SIZE + j][x/BLOCK_SIZE + i] = 1;
				draw_box(x + BLOCK_SIZE * i, y + BLOCK_SIZE * j, p, b);
			}
		}
	}
	mlx_put_image_to_window(b->e->mlx, b->e->win,b->e->img, 0, 0);
	score_info(b);
	display_board_on_window(b);
}
