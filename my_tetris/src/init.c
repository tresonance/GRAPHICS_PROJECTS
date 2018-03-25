#include "../include/tetris.h"

t_env					*init_mlx(void)
{
	t_env		*e;

	if (!(e = (t_env*)malloc(sizeof(t_env))))
		err_exit("Unable to allocate memory");
	if(!(e->mlx = mlx_init()))
		err_exit_free("Could not allocate\n", (void**)&e);
	if (!(e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, "MY TETRIS")))
		err_exit_free("Could not allocate\n", &e->win);
	if(!(e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT)))
	{
		err_exit_free("Could not allocate\n", &e->win);
		err_exit_free("Could not allocate\n", (void**)&e);

	}
	if (!(e->pixel = mlx_get_data_addr(e->img, &e->bpp, &e->size_line, &e->end)))
	{
		err_exit_free("Could not allocate\n", &e->img);
		err_exit_free("Could not allocate\n", &e->win);
		err_exit_free("Could not allocate\n", (void**)&e);
	}
	return (e);
}

t_piece				*init_piece_data(void)
{
	t_piece			*p;

	if (!(p = (t_piece*)malloc(sizeof(t_piece))))
		err_exit("Unable to allocate memory");
	p->pivot_local_x = 1;
	p->pivot_local_y = 2;
	p->color = (t_color){255,255,255};
	p->piece = NULL;
	return (p);
}

t_board				*init_board(void)
{
	t_board			*b;
	int				i;
	int				j;

	if (!(b = (t_board*)malloc(sizeof(t_board))))
		err_exit("Unable to allocate memory");
	b->e = init_mlx();
	b->pos_board_x = 3 * (int)WIDTH/4 -  2*(int)BLOCK_SIZE;
	b->pos_board_y = 2*(int)BLOCK_SIZE + 1;
	
	init_all_pieces(b);
	b->curr_piece = init_piece_data();
	b->curr_bloc_num = S;
	b->curr_piece_num = 0;
	b->curr_piece->piece =  b->arr_piece[b->curr_bloc_num][b->curr_piece_num];
	b->arr_color[0]= (t_color){255,5,10};
	b->arr_color[1]= (t_color){255,250,10};
	b->arr_color[2]= (t_color){255,30,250};
	b->arr_color[3]= (t_color){100,255,250};
	b->arr_color[4]= (t_color){20,255,140};
	b->arr_color[5]= (t_color){100,170,255};
	b->arr_color[6]= (t_color){170,150,255};
	
	//b->last_line = HEIGHT - 11*BLOCK_SIZE;
	b->score = 0;
	b->curr_piece->color = b->arr_color[b->curr_bloc_num];
	//score_info(b);
	b->nbr_ipiece = WIDTH/BLOCK_SIZE;
	b->nbr_jpiece = HEIGHT/BLOCK_SIZE;
	j = -1;
	while(++j < b->nbr_jpiece)
	{
		i = -1;
		while(++i < b->nbr_ipiece)
		{
			if (i == 0 || i == b->nbr_ipiece - 1)
				b->board[j][i] = BORDER;
			else if ( j == b->nbr_jpiece - 1)
				b->board[j][i] = BOTTOM_BORDER;
			else
				b->board[j][i] = FREE;
		}
	}
	return (b);
}

