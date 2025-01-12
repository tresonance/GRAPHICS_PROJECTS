#include "../include/tetris.h"

void				err_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
}

void				err_exit_free(char *msg, void **ptr)
{
	if (*ptr)
		ft_memdel((void**)ptr);
	ft_putstr_fd(msg, 2);
	exit(1);
	return ;
}


void				display_piece(t_piece *p)
{
	int				i;
	int				j;

	j = -1;
	while (++j < 4)
	{
		i = -1;
		while (++i < 4)
		{
				printf("%d ", p->piece[j][i]);
		}
		printf("\n");
	}
}

void				display_piece2(t_board *b, int bloc, int nump)
{
	int				i;
	int				j;

	j = -1;
	while (++j < 4)
	{
		i = -1;
		while (++i < 4)
		{
				printf("%d ", b->arr_piece[bloc][nump][j][i]);
		}
		printf("\n");
	}
}

void				display_board(t_board *b)
{
	int				i;
	int				j;

	j = -1;
	while (++j < HEIGHT/BLOCK_SIZE)
	{
		i = -1;
		printf("|[");
		while (++i < WIDTH/BLOCK_SIZE)
			printf("%d ", b->board[j][i]);
		printf("]|\n");
	}
	printf("\n");
}

void				display_board_on_window(t_board *b)
{
	int				i;
	int				j;
	int				step_j;
	int				step_i;
	char			*str;

	j = -1;
	step_j = 70;
	step_i = 10;
	while (++j < b->nbr_jpiece)
	{
		i = -1;
		step_j += 13;
		mlx_string_put(b->e->mlx, b->e->win, 10 , step_j, 0x00FEDC, "[");
		step_i = 20;
		while (++i < b->nbr_ipiece)
		{
			str = ft_itoa(b->board[j][i]);
			mlx_string_put(b->e->mlx, b->e->win, step_i , step_j, b->board[j][i] == 1 ? 0xFFFF00 : b->board[j][i] == BORDER ? 0xFF0000 : 0x676767, str);
			//mlx_string_put(b->e->mlx, b->e->win, 10 + 10 * i + 5 , 250 + 10 * j, 0x000000, " ");
			ft_strdel(&str);
			step_i += 6;
		}
		mlx_string_put(b->e->mlx, b->e->win,step_i , step_j, 0x00FEDC, "]");
		
	}
}
