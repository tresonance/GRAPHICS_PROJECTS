#include "../include/tetris.h"

void				clear_piece(t_piece *p, int x, int y, t_board *b)
{
	int				i;
	int				j;

	j = -1;
	while (++j < 4 * BLOCK_SIZE && y + j < HEIGHT)
	{
		i = -1;
		while (++i < 4 * BLOCK_SIZE  && x + i < WIDTH)
		{
			b->board[(y + j)/BLOCK_SIZE][(x + i)/BLOCK_SIZE] = 0;
			//put_box(x+i, y+j, p, (t_color){(char)0,(char)0,(char)0}, b);
			put_pixel(x+i, y+j, (t_color){(char)0,(char)0,(char)0}, b->e);
		}
	}
}

int			same_color(char *pixel, int x, int y, t_color col, t_board *b)
{
	int		index;
	index = (y * b->e->size_line) + (x * b->e->bpp/8);
	return (pixel[index] == col.r && pixel[index + 1]  == col.g && pixel[index + 2]  == col.b);
}

void		flood_fill(t_board *b, int x, int y, int visited[HEIGHT][WIDTH], t_color to_check, t_color to_set)
{
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT || visited[x][y] || !same_color(b->e->pixel, x, y, to_check,b))
		return ;
		put_box(x, y, b->curr_piece, to_set, b);
		visited[y][x] = TRUE;
	flood_fill(b, x - 1, y, visited, to_check, to_set);
	flood_fill(b, x + 1, y - 1, visited, to_check, to_set);
	flood_fill(b, x - 1, y - 1, visited, to_check, to_set);
	flood_fill(b, x - 1, y + 1, visited, to_check, to_set);
	flood_fill(b, x + 1, y + 1, visited, to_check, to_set);
	flood_fill(b, x + 1, y, visited, to_check, to_set);
	flood_fill(b, x , y - 1, visited, to_check, to_set);
	flood_fill(b, x , y + 1, visited, to_check, to_set);
}

void		clear_piece2(t_piece *p, int x, int y, t_board *b)
{
	int		visited[HEIGHT][WIDTH];
	int		i;
	int		j;

	j = -1;
	while (++j < HEIGHT)
	{
		i = -1;
		while(++i < WIDTH)
		{
			visited[j][i] = FALSE;
		}
	}
	flood_fill(b, x, y, visited, p->color, (t_color){(char)0,(char)0 ,(char)0});
}
