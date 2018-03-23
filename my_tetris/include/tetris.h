#ifndef __TETRIS_H__
# define  __TETRIS_H__

#include "../libft/libft.h"
#include "../minilibx_macos/mlx.h"
#include <time.h>

#define WIDTH 500
#define HEIGHT 650
#define TRUE 1
#define FALSE 0
#define BLOCK_SIZE 15

#define UP 126 
#define DOWN 125
#define LEFT 123
#define RIGHT 124
#define ESC 53
#define E 14
#define D 2
#define A 12
#define Q 0

#define RGB(r,g,b) r + (256 +  g) + (65536 +  b)

typedef enum
{
	J, I, S, Z, T, L, O 
}e_enum;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	int				end;
	int				bpp;
	int				size_line;
	char			*pixel;
}					t_env;

typedef struct		s_color
{
	char			r;
	char			g;
	char			b;
}					t_color;

typedef struct		s_piece
{
	int				(*piece)[4];
	int				pivot_local_x;
	int				pivot_local_y;
	t_color			color;
}					t_piece;

typedef struct		s_board
{
	t_env			*e;
	int				pos_board_x;
	int				pos_board_y;
	int				board[HEIGHT/BLOCK_SIZE][WIDTH/BLOCK_SIZE];
	int				arr_piece[7][4][4][4];
	t_piece			*curr_piece;
	e_enum			curr_bloc_num;
	int				curr_piece_num;
	t_color			arr_color[7];
	int				move_down;
	int				score;
}					t_board;

/*
 * init.c
 */
t_env				*init_mlx(void);
t_piece				*init_tetris_data(void);
t_board 			*init_board(void);
/*
 * init2.c
 */
void				init_all_pieces(t_board *b);

/*
 * display.c
 */
void				err_exit(char *msg);
void				err_exit_free(char *msg, void **ptr);
void				display_piece(t_piece *p, t_board *b);
void				display_piece2(t_board *b, int bloc, int nump);
void				display_board(t_board *b);
void				display_board_on_window(t_board *b);
/*
 *draw.c
 */
void				draw_piece(int x, int y, t_piece *p, t_board *b);
int					is_collision(int x, int y, t_piece *p, t_board *b);
/*
 * pixel.c
 */
void				put_pixel(int x, int y, t_color color, t_env *e);
void				put_box(int x, int y, t_piece *p, t_color color, t_board *b);
/*
 * destroy.c
 */
void				destroy_all(t_board **b);
int					clear_env(t_board *b);
/*
 *clear_piece.c
 */
void				clear_piece(t_piece *p, int x, int y, t_board *b);
void				clear_piece2(t_piece *p, int x, int y, t_board *b);
void				flood_fill(t_board *b, int x, int y, int visited[HEIGHT][WIDTH], t_color to_check, t_color to_set);
/*
 *
 * event.c
 */
int					key_hook(int key, t_board *b);
/*
 * piece.c
 */
void				rotate_piece(t_board *b);
void				change_piece(t_board *b);
/*
 * score.c
 */
void				score_info(t_board *b);
#endif
