/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_x11.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 16:42:05 by gtorresa          #+#    #+#             */
/*   Updated: 2016/02/10 20:38:46 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

extern int image_height;	/* Number of rows in image */
extern int image_width;		/* Number of columns in image */

static void		*make_line_x(void *arg)
{
	int			x;
	t_data		*data;

	x = 0;
	data = (t_data*)arg;
	data->r_pxx[0] = 0;
	data->r_pxy[0] = 0;
	while (x < data->fdf.x)
	{
		data->p.px_color = data->p.color_ref[0];
		pthread_mutex_lock(get_mutex(0));
		print_line_x(data, data->fdf.fdfx[x], data->fdf.y, x);
		pthread_mutex_unlock(get_mutex(0));
		data->r_pxx[0] = data->r_pxx[0] - data->p.zoom;
		data->r_pxy[0] = data->r_pxy[0] + data->p.zoom * data->p.rot;
		x++;
	}
	pthread_exit(NULL);
}

static void		*make_line_y(void *arg)
{
	int			y;
	t_data		*data;

	y = 0;
	data = (t_data*)arg;
	data->r_pxx[1] = 0;
	data->r_pxy[1] = 0;
	while (y < data->fdf.y)
	{
		data->p.px_color = data->p.color_ref[0];
		pthread_mutex_lock(get_mutex(0));
		print_line_y(data, data->fdf.fdfy[y], data->fdf.x, y);
		pthread_mutex_unlock(get_mutex(0));
		data->r_pxx[1] = data->r_pxx[1] + data->p.zoom;
		data->r_pxy[1] = data->r_pxy[1] + data->p.zoom * data->p.rot;
		y++;
	}
	pthread_exit(NULL);
}

void			ft_print_fdf(t_data data)
{
	pthread_t	thread_x;
	pthread_t	thread_y;
	t_data		*data_s;

	data_s = &data;
	data.img = mlx_new_image(data.mlx, W_W, W_H);
	data.pixel_img = mlx_get_data_addr(data.img, &(data.bpp), &(data.img_line), &(data.ed));
	if (data.play == 0)
	{
		data.play = 1;
		data.move = 0;
		get_frame_info(data);
		pthread_create(&thread_x, NULL, make_line_x, data_s);
		pthread_create(&thread_y, NULL, make_line_y, data_s);
		pthread_join(thread_x, NULL);
		pthread_join(thread_y, NULL);
		data.play = 0;
	}
	ft_make_png(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_destroy_image(data.mlx, data.img);
	get_frame_info(data);
}

static t_data	init_data(t_data data, t_fdf fdf, char *filename)
{
	data.fdf = fdf;
	data.p.posx[0] = 500;
	data.p.posy[0] = 500;
	data.p.posx[2] = data.p.posx[0];
	data.p.posy[2] = data.p.posy[0];
	data.win_size_w = 1920;
	data.win_size_h = 1080;
	image_height = data.win_size_h;
	image_width = data.win_size_w;
	data.p.zoom = 8;
	data.p.scale = 0.11;
	data.p.rot = 0.5;
	init_color(&data);
	data.p.v_max_min[0] = fdf.v_max_min[0];
	data.p.v_max_min[1] = -fdf.v_max_min[1];
	data.p.c_index = 0;
	data.p.color_off = 0;
	data.play = 0;
	data.filename = filename;
	data.mouse_x = 0;
	data.mouse_y = 0;
	data.move = 0;
	get_mutex(1);
	return (data);
}

int				init_x11(t_fdf fdf, char *filename, int fd_move)
{
	t_data			data;


	data = init_data(data, fdf, filename);
	printf("conf mouve\n");
	if ((data.mlx = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data.win = mlx_new_window(data.mlx, W_W, W_H, "FdF")) == NULL)
		return (EXIT_FAILURE);
	ft_print_fdf(data);
	//mlx_mouse_hook(data.win, &ft_mouse_action, &data);
	//mlx_hook(data.win, 6, (1L << 6), &ft_mouse_motion, &data);
	//mlx_hook(data.win, 2, (1L << 0), &ft_key_action, &data);
	read_move_space(&data, read_move_conf(fd_move));
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
