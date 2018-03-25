#include "../include/tetris.h"

/*void				clear_piece(t_piece *p, int x, int y, t_board *b)
{
	int				i;
	int				j;

	j = -1;
	while (++j < 4)
	{
		i = -1;
		while (++i < 4)
		{
			if(b->board[y/BLOCK_SIZE + j][x/BLOCK_SIZE + i] < 2)
				b->board[y/BLOCK_SIZE + j][x/BLOCK_SIZE + i] = 0;
			put_box(x+BLOCK_SIZE*i, y+BLOCK_SIZE*j, p, (t_color){(char)0,(char)0,(char)0}, b);
			put_pixel(x+i, y+j, (t_color){(char)0,(char)0,(char)0}, b->e);
		}
	}
}*/

void			clear_piece(t_piece *p, int x, int y, t_board *b)
{
	init_flood_visited(p->visited);
	flood_draw_piece(p, b, p->pivot_local_x, p->pivot_local_y, x, y, p->visited, FREE);
	//mlx_put_image_to_window(b->e->mlx, b->e->win,b->e->img, 0, 0);

}

