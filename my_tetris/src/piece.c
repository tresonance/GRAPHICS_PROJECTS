#include "../include/tetris.h"

void				rotate_piece(t_board *b)
{
	b->curr_piece_num = (b->curr_piece_num + 1)%4;
	b->curr_piece->piece= b->arr_piece[b->curr_bloc_num][b->curr_piece_num];
	b->curr_piece->color = b->arr_color[b->curr_bloc_num];
}

void				change_piece(t_board *b)
{
	b->curr_bloc_num = (b->curr_bloc_num + 1)%7;
	b->curr_piece->piece= b->arr_piece[b->curr_bloc_num][b->curr_piece_num];
	b->curr_piece->color = b->arr_color[b->curr_bloc_num];
}




