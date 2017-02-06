/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 19:52:56 by gtorresa          #+#    #+#             */
/*   Updated: 2016/02/10 20:39:53 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define COLOR_INC 0x0000A
# define W_W data.win_size_w
# define W_H data.win_size_h
# define C_S data.p.color_ref_len
# define C_SP data->p.color_ref_len

# include <libft.h>
# include "mlx.h"
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pthread.h>
# include <stdio.h>
# include <setjmp.h>
# include "jpeglib.h"

typedef struct		s_point
{
	float			posx[3];
	float			posy[3];
	float			scale;
	float			rot;
	int				color_off;
	int				px_color;
	int				*color_ref;
	int				color_ref_len;
	float			zoom;
	int				c_index;
	int				v_max_min[2];
}					t_point;

typedef struct		s_fdf
{
	int				**fdfx;
	int				**fdfy;
	int				x;
	int				y;
	int				v_max_min[2];
}					t_fdf;

typedef struct		s_motion
{
	int				posx;
	int				posy;
	int				zoom;
	int				rot;
	int				speed;
	struct s_motion	*next;
}					t_motion;

typedef struct		s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*pixel_img;
	int				ed;
	int				bpp;
	int				img_line;
	int				win_size_w;
	int				win_size_h;
	float			r_pxx[2];
	float			r_pxy[2];
	t_point			p;
	int				def;
	int				move;
	t_fdf			fdf;
	int				mouse_x;
	int				mouse_y;
	int				play;
	char			*filename;
	int				nbr_color;
	t_motion		*motion;
}					t_data;

typedef struct		s_line
{
	float			pos1x;
	float			pos1y;
	float			pos2x;
	float			pos2y;
}					t_line;

t_data				*draw_line(t_data *data, t_line line, int s);
void				print_line_x(t_data *data, int *fdf, int len, int x);
void				print_line_y(t_data *data, int *fdf, int len, int y);
int					ft_mouse_action(int button, int x, int y, t_data *data);
int					ft_mouse_motion(int x, int y, t_data *data);
void				ft_print_fdf(t_data data);
int					ft_key_action(int keycode, t_data *data);
void				get_frame_info(t_data data);
int					get_color_px(int p, t_point point);
void				init_color(t_data *data);
t_fdf				read_map(int fd);
int					init_x11(t_fdf fdf, char *filename, int fd_move);
t_data				*read_txt_color(t_data *data, int fd);
void				save_txt_color(t_data *data);
void				draw_full_rec(t_data *data, int x, int y, int c);
t_data				*read_c_color(t_data *data);
pthread_mutex_t		*get_mutex(int rw);
void				ft_make_png(t_data *data);
t_motion			*read_move_conf(int fd_move);
int					read_move_space(t_data *data, t_motion *motion);

#endif
