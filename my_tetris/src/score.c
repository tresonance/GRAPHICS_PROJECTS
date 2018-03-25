#include "../include/tetris.h"

void			score_info(t_board *b)
{
	char		*score;
	int			i;

	score = ft_itoa(b->score);
	mlx_string_put(b->e->mlx, b->e->win, 10, 5, 0x00FEDC, "-------------");

	mlx_string_put(b->e->mlx, b->e->win, 480, 50, 0x0000FF, "I");
	mlx_string_put(b->e->mlx, b->e->win, 480, 70, 0x00FEDC, "B");
	mlx_string_put(b->e->mlx, b->e->win, 480, 90, 0x00FF00, "T");
	mlx_string_put(b->e->mlx, b->e->win, 480, 110, 0x00FEDC, "R");
	mlx_string_put(b->e->mlx, b->e->win, 480, 130, 0xFF0000, "A");
	mlx_string_put(b->e->mlx, b->e->win, 480, 150, 0x00FEDC, "0");
	mlx_string_put(b->e->mlx, b->e->win, 480, 170, 0x0000FF, "R");
	mlx_string_put(b->e->mlx, b->e->win, 480, 190, 0x00FEDC, "E");
	mlx_string_put(b->e->mlx, b->e->win, 10, 50, 0x00FF00, "S C H O O L 4 2");

	i = 10;
	while (++i < HEIGHT - 2*BLOCK_SIZE)
	{
		mlx_string_put(b->e->mlx, b->e->win, WIDTH/2 - BLOCK_SIZE, i, 0xFF0000, "+");
		i += 20;
	}

	
	mlx_string_put(b->e->mlx, b->e->win, 10, 15, 0x00FEDC, "|");
	mlx_string_put(b->e->mlx, b->e->win, 130, 15, 0x00FEDC, "|");
	mlx_string_put(b->e->mlx, b->e->win, 130, 35, 0x00FEDC, "|");
	mlx_string_put(b->e->mlx, b->e->win, 10, 35, 0x00FEDC, "|");
	mlx_string_put(b->e->mlx, b->e->win, 30, 20, 0x00FEDC, "SCORE:");
	mlx_string_put(b->e->mlx, b->e->win, 100, 20, 0xFF0000, score);
	mlx_string_put(b->e->mlx, b->e->win, 10, 35, 0x00FEDC, "-------------");
	ft_strdel(&score);
}

