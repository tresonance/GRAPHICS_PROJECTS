#include "../include/tetris.h"

int				main(void)
{
	t_piece		*p;
	t_board		*b;

	srand(time(NULL));
	b = init_board();
	//display_piece(b->curr_piece, b);
	//score_info(b);
	draw_piece(b->pos_board_x, b->pos_board_y, b->curr_piece, b);
	//display_piece2(b, 0, 2);
	//mlx_hook(b->e->win, 17, 18, clear_env, &b->e);
	//mlx_hook(b->e->win, 2, 3, clear_env, &b->e);
	mlx_hook(b->e->win, 2, (1L << 0), key_hook, &b->e);
	mlx_loop(b->e->mlx);
	//display_board(b);
	return (0);
}
