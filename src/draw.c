#include "../include/tetris.h"

/*int				is_collision(int x, int y, t_piece *p, t_board *b)
{
	int			i;
	int			j;

	j = -1;
	b->collied_with = 0;
	while(++j < 4)
	{
		if (y + j >= HEIGHT)
			return (TRUE);
		i = -1;
		while (++i < 4)
		{
			if(x + i >= WIDTH || x + i < WIDTH/2 - BLOCK_SIZE)
				return (TRUE);
			if (p->piece[j][i]  > 0 && b->board[y /BLOCK_SIZE + j][x/BLOCK_SIZE + i] > 0)
			{
				if (b->board[y /BLOCK_SIZE + j][x/BLOCK_SIZE + i] == BOTTOM_BORDER)
				{
					b->collied_with = BOTTOM_BORDER;
				}
			
				return (TRUE);
			}
		}
	}
	return (FALSE);
}*/

void			draw_box(int x, int y, t_piece *p, t_board *b, int flag)
{
	int			i;
	int			j;
	
	j = -1;
	while (++j < BLOCK_SIZE)
	{
			i = -1;
			while (++i < BLOCK_SIZE)
			{
				put_pixel(x + i, y + j, flag == FREE ? (t_color){(char)0,(char)0,(char)0 } : p->color, b->e);

			}
	}
	//mlx_put_image_to_window(b->e->mlx, b->e->win,b->e->img, 0, 0);
}

void			init_flood_visited(int visited[4][4])
{
	int			i;
	int			j;

	j = -1;
	while (++j < 4)
	{
		i = -1;
		while (++i < 4)
			visited[j][i] = FREE;
	}
}

void			flood_draw_piece(t_piece *p, t_board *b, int pivot_x, int pivot_y, int board_x, int board_y, int visited[4][4], int value)
{
	if (pivot_x < 0 || pivot_x >= 4 || pivot_y < 0 || pivot_y >= 4 || visited[pivot_y][pivot_x] || p->piece[pivot_y][pivot_x] == FREE)
		return ;
	visited[pivot_y][pivot_x] = BUSY;
	draw_box(board_x, board_y, p, b, value);
	b->board[board_y/BLOCK_SIZE][board_x/BLOCK_SIZE] = value;

	flood_draw_piece(p, b, pivot_x - 1, pivot_y, board_x - BLOCK_SIZE, board_y, visited, value);
	flood_draw_piece(p, b, pivot_x + 1, pivot_y, board_x + BLOCK_SIZE, board_y, visited, value);
	flood_draw_piece(p, b, pivot_x , pivot_y - 1, board_x, board_y - BLOCK_SIZE, visited, value);
	flood_draw_piece(p, b, pivot_x, pivot_y + 1, board_x, board_y + BLOCK_SIZE, visited, value);
}

void			draw_piece(int x, int y, t_piece *p, t_board *b)
{
	init_flood_visited(p->visited);
	flood_draw_piece(p, b, p->pivot_local_x, p->pivot_local_y, x, y, p->visited, BUSY);
	mlx_put_image_to_window(b->e->mlx, b->e->win,b->e->img, 0, 0);
	score_info(b);
	display_board_on_window(b);

}


/*void			draw_piece(int x, int y, t_piece *p, t_board *b)
{
	int			i;
	int			j;

	if (is_collision(x, y, p, b)){printf("collid\n");
		return ;}
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
}*/
