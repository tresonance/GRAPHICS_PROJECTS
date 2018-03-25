#include "../include/tetris.h"

/*void				call_next_piece(t_board *b)
{
	b->pos_board_x = 3 * WIDTH/4 - 2*BLOCK_SIZE;
	b->pos_board_y = 2 * BLOCK_SIZE;
	b->curr_bloc_num = rand()%7;
	b->curr_piece_num = rand()%4;
	b->curr_piece->piece = b->arr_piece[b->curr_bloc_num][b->curr_piece_num];
	b->curr_piece->color = b->arr_color[rand()%7];
	draw_piece(b->pos_board_x, b->pos_board_y, b->curr_piece, b);
	score_info(b);
}*/

void				is_current_piece_movable_utils(t_piece *p, int pivot_x, int pivot_y, t_board *b, int x, int y, int *result, int piece_visited_array[4][4], int board_visited_array[b->nbr_jpiece][b->nbr_ipiece])
{
	if (pivot_x < 0 || pivot_x >= 4 || pivot_y < 0 || pivot_y >= 4 || piece_visited_array[pivot_y][pivot_x] || p->piece[pivot_y][pivot_x] == FREE)
		return ;
	piece_visited_array[pivot_y][pivot_x] = BUSY;
	if (x < WIDTH/2  || x >= WIDTH || y < 0 || y >= HEIGHT || board_visited_array[y/BLOCK_SIZE][x/BLOCK_SIZE] != FREE)
	{
		*result = FALSE;
		return; 
	}
	is_current_piece_movable_utils(p, pivot_x - 1, pivot_y, b, x - BLOCK_SIZE, y, result, piece_visited_array, board_visited_array);
	is_current_piece_movable_utils(p, pivot_x + 1, pivot_y, b, x + BLOCK_SIZE, y, result, piece_visited_array, board_visited_array);
	is_current_piece_movable_utils(p, pivot_x , pivot_y - 1, b, x, y - BLOCK_SIZE, result, piece_visited_array, board_visited_array);
	is_current_piece_movable_utils(p, pivot_x , pivot_y + 1, b, x, y + BLOCK_SIZE, result, piece_visited_array, board_visited_array);
}

int					is_piece_translateble(t_piece *p, int x, int y, t_board *b)
{
	int				result;

	result = TRUE;
	clear_piece(b->curr_piece, b->pos_board_x, b->pos_board_y, b);
	init_flood_visited(p->visited);
	is_current_piece_movable_utils(p, p->pivot_local_x, p->pivot_local_y, b, x, y, &result, p->visited, b->board);
	draw_piece(b->pos_board_x, b->pos_board_y, b->curr_piece, b);
	return (result);
}

int					is_piece_rotable(t_piece *p, t_board *b)
{
	int				result;
	int				curr_num;


	result = TRUE;
	clear_piece(b->curr_piece, b->pos_board_x, b->pos_board_y, b);
	init_flood_visited(p->visited);
	curr_num = b->curr_piece_num;
	b->curr_piece_num = (b->curr_piece_num + 1)%4;
	b->curr_piece->piece = b->arr_piece[b->curr_bloc_num][b->curr_piece_num];
	is_current_piece_movable_utils(b->curr_piece, p->pivot_local_x, p->pivot_local_y, b, b->pos_board_x, b->pos_board_y, &result, p->visited, b->board);
	b->curr_piece_num = curr_num;
	b->curr_piece = p;
	draw_piece(b->pos_board_x, b->pos_board_y, p, b);
	return (result);
}

int					is_piece_changeable(t_piece *p, t_board *b)
{
	int				result;
	int				curr_bloc;


	result = TRUE;
	clear_piece(b->curr_piece, b->pos_board_x, b->pos_board_y, b);
	init_flood_visited(p->visited);
	curr_bloc = b->curr_bloc_num;
	b->curr_bloc_num = (b->curr_bloc_num + 1)%7;
	b->curr_piece->piece = b->arr_piece[b->curr_bloc_num][b->curr_piece_num];

	is_current_piece_movable_utils(b->curr_piece, p->pivot_local_x, p->pivot_local_y, b, b->pos_board_x, b->pos_board_y, &result, p->visited, b->board);
	b->curr_bloc_num = curr_bloc;
	b->curr_piece = p;
	draw_piece(b->pos_board_x, b->pos_board_y, p, b);
	return (result);
}


int					key_hook(int key, t_board *b)
{
	int				x;
	int				y;
	t_piece			*p;

	if (key == ESC)
		clear_env(b);
	x = b->pos_board_x;
	y = b->pos_board_y;
	p = b->curr_piece;
	//clear_piece(b->curr_piece, x,y, b);

	if (key == UP && is_piece_translateble(b->curr_piece, b->pos_board_x, b->pos_board_y - BLOCK_SIZE, b))
		b->pos_board_y = b->pos_board_y - BLOCK_SIZE;
	else if (key == DOWN && is_piece_translateble(b->curr_piece, b->pos_board_x, b->pos_board_y + BLOCK_SIZE, b))
		b->pos_board_y = b->pos_board_y + BLOCK_SIZE;
	else if (key == LEFT  && is_piece_translateble(b->curr_piece, b->pos_board_x - BLOCK_SIZE, b->pos_board_y, b))
		b->pos_board_x = b->pos_board_x - BLOCK_SIZE;
	else if (key == RIGHT && is_piece_translateble(b->curr_piece, b->pos_board_x + BLOCK_SIZE, b->pos_board_y, b))
		b->pos_board_x = b->pos_board_x + BLOCK_SIZE;
	else if (key == A && is_piece_rotable(b->curr_piece, b))
		rotate_piece(b);
	else if (key == Q && is_piece_changeable(b->curr_piece, b))
		change_piece(b);
	printf("[key %d]\n", key);
	
	if (key == Q || key == A)
		clear_piece(p, x,y, b);
	else
		clear_piece(b->curr_piece, x,y, b);
		
		draw_piece(b->pos_board_x, b->pos_board_y, b->curr_piece, b);
		score_info(b);
//	}
	//else 
//	{
	//	b->pos_board_x = x;
	//	b->pos_board_y = y;
	//	draw_piece(b->pos_board_x, b->pos_board_y, b->curr_piece, b);
	//	score_info(b);

//	}
		
	return (0);
}


