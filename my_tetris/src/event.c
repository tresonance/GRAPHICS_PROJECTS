#include "../include/tetris.h"

void				call_next_piece(t_board *b)
{
	b->pos_board_x = 3 * WIDTH/4 - 2*BLOCK_SIZE;
	b->pos_board_y = 2 * BLOCK_SIZE + 1;
	b->curr_bloc_num = rand()%7;
	b->curr_piece_num = rand()%4;
	b->curr_piece->piece = b->arr_piece[b->curr_bloc_num][b->curr_piece_num];
	b->curr_piece->color = b->arr_color[rand()%7];
	draw_piece(b->pos_board_x, b->pos_board_y, b->curr_piece, b);
	score_info(b);
}

int					key_hook(int key, t_board *b)
{
	int				x;
	int				y;

	b->move_down = FALSE;
	if (key == ESC)
		clear_env(b);
	x = b->pos_board_x;
	y = b->pos_board_y;
	if (key == UP && (b->pos_board_y > 2 * BLOCK_SIZE))
		b->pos_board_y = b->pos_board_y - BLOCK_SIZE;
	if (key == DOWN && (b->pos_board_y < HEIGHT - 10 * BLOCK_SIZE))
	{
		b->move_down = TRUE;
		b->pos_board_y = b->pos_board_y + BLOCK_SIZE - 1;
	}
	if (key == LEFT && (b->pos_board_x > WIDTH/2 + BLOCK_SIZE))
		b->pos_board_x = b->pos_board_x - BLOCK_SIZE;
	if (key == RIGHT && (b->pos_board_x < WIDTH - 8 *BLOCK_SIZE))
		b->pos_board_x = b->pos_board_x + BLOCK_SIZE;
	if (key == A)
		rotate_piece(b);
	if (key == Q)
		change_piece(b);

	printf("[key %d]\n", key);
	clear_piece(b->curr_piece, x, y,  b);
	//clear_piece2(b->curr_piece, x, y,  b);
	
	//mlx_clear_window(b->e->mlx,b->e->win);
	//mlx_put_image_to_window(b->e->mlx, b->e->win, b->e->img, 0,0);
	draw_piece(b->pos_board_x, b->pos_board_y, b->curr_piece, b);
	score_info(b);
	if(key == DOWN && b->move_down == FALSE)
		call_next_piece(b);	
		
	return (0);
}


