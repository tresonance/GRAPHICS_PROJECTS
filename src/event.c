#include "../include/tetris.h"

void				call_next_piece(t_board *b)
{
	b->pos_board_x = 3 * WIDTH/4 - 2*BLOCK_SIZE;
	b->pos_board_y = 2 * BLOCK_SIZE;
	b->curr_bloc_num = rand()%7;
	b->curr_piece_num = rand()%4;
	b->curr_piece->piece = b->arr_piece[b->curr_bloc_num][b->curr_piece_num];
	b->curr_piece->color = b->arr_color[rand()%7];
	draw_piece(b->pos_board_x, b->pos_board_y, b->curr_piece, b);
	score_info(b);
}

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
	//if (result)
	//draw_piece(b->pos_board_x, b->pos_board_y, p, b);
	return (result);
}

int					is_piece_rotable(t_piece *p, t_board *b)
{
	int				result;
	t_piece			next_piece;

	result = TRUE;
	clear_piece(p, b->pos_board_x, b->pos_board_y, b);
	next_piece.piece = b->arr_piece[b->curr_bloc_num][(b->curr_piece_num + 1)%4];
	init_flood_visited(next_piece.visited);
	next_piece.pivot_local_x = 2;
	next_piece.pivot_local_y = 1;
	is_current_piece_movable_utils(&next_piece, next_piece.pivot_local_x, next_piece.pivot_local_y, b, b->pos_board_x, b->pos_board_y, &result, next_piece.visited, b->board);
	//if (result)
	//draw_piece(b->pos_board_x, b->pos_board_y, p, b);
	return (result);
}

int					is_piece_changeable( t_board *b)
{
	int				result;
	t_piece			next_piece;;


	result = TRUE;
	clear_piece(b->curr_piece, b->pos_board_x, b->pos_board_y, b);
	next_piece.piece = b->arr_piece[(b->curr_bloc_num + 1)%7][b->curr_piece_num];
	init_flood_visited(next_piece.visited);
	is_current_piece_movable_utils(&next_piece, next_piece.pivot_local_x, next_piece.pivot_local_y, b, b->pos_board_x, b->pos_board_y, &result, next_piece.visited, b->board);
	//draw_piece(b->pos_board_x, b->pos_board_y, p, b);
	return (result);
}


int					key_hook(int key, t_board *b)
{
	int				x;
	int				y;
	int				no_collision;
	t_piece			*p;

	if (key == ESC)
		clear_env(b);
	x = b->pos_board_x;
	y = b->pos_board_y;
	p = b->curr_piece;
	//clear_piece(b->curr_piece, x,y, b);
	
	no_collision = FALSE;
	if (key == UP && is_piece_translateble(b->curr_piece, b->pos_board_x, b->pos_board_y - BLOCK_SIZE, b) && (no_collision = TRUE))
		b->pos_board_y = b->pos_board_y - BLOCK_SIZE;
	else if (key == DOWN && is_piece_translateble(b->curr_piece, b->pos_board_x, b->pos_board_y + BLOCK_SIZE, b) && (no_collision = TRUE))
		b->pos_board_y = b->pos_board_y + BLOCK_SIZE;
	else if (key == LEFT  && is_piece_translateble(b->curr_piece, b->pos_board_x - BLOCK_SIZE, b->pos_board_y, b) && (no_collision = TRUE))
		b->pos_board_x = b->pos_board_x - BLOCK_SIZE;
	else if (key == RIGHT && is_piece_translateble(b->curr_piece, b->pos_board_x + BLOCK_SIZE, b->pos_board_y, b) && (no_collision = TRUE))
		b->pos_board_x = b->pos_board_x + BLOCK_SIZE;
	else if (key == A && is_piece_rotable(b->curr_piece, b) && (no_collision = TRUE))
		rotate_piece(b);
	else if (key == Q && is_piece_changeable( b) && (no_collision = TRUE))
		change_piece(b);
	if (no_collision == FALSE)
		ft_putstr("C O L L I S I O N\n");
	else
	{
		printf("[key %d]\n", key);
		//call_next_piece(b);
	}
	clear_piece(p, x,y, b);
	draw_piece(b->pos_board_x, b->pos_board_y, b->curr_piece, b);
	score_info(b);
	if(no_collision == FALSE)
		call_next_piece(b);
	return (0);
}


