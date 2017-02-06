/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 04:26:54 by gtorresa          #+#    #+#             */
/*   Updated: 2016/01/21 16:27:06 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int				ft_mouse_action(int button, int x, int y, t_data *data)
{
	if (button == 1)
	{
		if ((data->move == 0) && ((data->move = 1)
			&& (data->mouse_x = x)))
			data->mouse_y = y;
		else
			data->move = 0;
	}
	if ((button == 5 && data->p.zoom < 2000) && (
		(data->p.posx[0] -= data->p.zoom * 0.01) &&
		(data->p.posy[0] -= data->p.zoom * 3)))
		data->p.zoom = (data->p.zoom * 1.20) + 1;
	if ((button == 4) && (
		(data->p.posx[0] += data->p.zoom * 0.01) &&
		(data->p.posy[0] += data->p.zoom * 3)))
		data->p.zoom = data->p.zoom * 0.80;
	data->p.posx[2] = data->p.posx[0];
	data->p.posy[2] = data->p.posy[0];
	if (button == 4 || button == 5 || data->move == 0)
		ft_print_fdf(*data);
	printf("%lf\n", data->p.zoom);
	return (0);
}

int				ft_mouse_motion(int x, int y, t_data *data)
{
	if (data->move == 1)
	{
		data->p.posx[0] = data->p.posx[0] - (data->mouse_x - x);
		data->p.posy[0] = data->p.posy[0] - (data->mouse_y - y);
		data->p.posx[2] = data->p.posx[0];
		data->p.posy[2] = data->p.posy[0];
		ft_print_fdf(*data);
		mlx_string_put(data->mlx, data->win, x + 10, y + 10, 0xCE0003, "X");
		data->mouse_x = x;
		data->mouse_y = y;
	}
	return (0);
}

static int		get_key_action_2(int keycode, t_data *data, int r)
{
	if (((keycode == 20 || keycode == 51) && data->p.c_index > 0)
		&& (r = 1))
		data->p.c_index--;
	if (((keycode == 21 || keycode == 52) && data->p.c_index < C_SP - 1)
		&& (r = 1))
		data->p.c_index++;
	if (((keycode == 8 || keycode == 99)) && (r = 1))
	{
		data->p.posx[0] = 500;
		data->p.posy[0] = 100;
		data->p.posx[2] = 500;
		data->p.posy[2] = 100;
		data->p.zoom = 30;
		data->p.scale = 0.05;
		data->p.rot = 0.5;
	}
	return (r);
}

static int		get_key_action(int key, t_data *data)
{
	int		r;

	r = 0;
	if ((key == 53 || key == 65307) && (r = 1))
	{
		save_txt_color(data);
		exit(EXIT_SUCCESS);
	}
	if (((key == 69 || key == 65453) && data->p.scale < 0.5) && (r = 1))
		data->p.scale = data->p.scale + 0.01;
	if (((key == 78 || key == 65451) && data->p.scale > -0.5) && (r = 1))
		data->p.scale = data->p.scale - 0.01;
	if (((key == 30 || key == 91) && data->p.rot < 10) && (r = 1))
		data->p.rot = data->p.rot + 0.05;
	if (((key == 33 || key == 93) && data->p.rot > -10) && (r = 1))
		data->p.rot = data->p.rot - 0.05;
	if (((key == 18 || key == 50)) && (r = 1))
		data->p.color_ref[data->p.c_index] += 0x00010F;
	if (((key == 19 || key == 49)) && (r = 1))
		data->p.color_ref[data->p.c_index] -= 0x00010F;
	return (get_key_action_2(key, data, r));
}

int				ft_key_action(int keycode, t_data *data)
{
	if (get_key_action(keycode, data) == 1)
		ft_print_fdf(*data);
	return (0);
}
