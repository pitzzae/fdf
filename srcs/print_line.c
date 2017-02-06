/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 20:56:25 by gtorresa          #+#    #+#             */
/*   Updated: 2016/02/10 20:38:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static t_point			get_next_pos_x(t_point d, int *fdf, int i)
{
	if (fdf[i] - fdf[i - 1] < 0)
	{
		d.posy[1] += (fdf[i - 1] - fdf[i]) * d.zoom * d.scale;
		d.color_off = get_color_px(fdf[i], d);
	}
	if (fdf[i] - fdf[i - 1] > 0)
	{
		d.posy[1] -= (fdf[i] - fdf[i - 1]) * d.zoom * d.scale;
		d.px_color = get_color_px(fdf[i], d);
	}
	return (d);
}

static t_point			get_next_pos_y(t_point d, int *fdf, int i)
{
	if (fdf[i] - fdf[i - 1] < 0)
	{
		d.posy[1] -= (fdf[i - 1] - fdf[i]) * d.zoom * d.scale;
		d.color_off = get_color_px(fdf[i], d);
	}
	if (fdf[i] - fdf[i - 1] > 0)
	{
		d.posy[1] += (fdf[i] - fdf[i - 1]) * d.zoom * d.scale;
		d.px_color = get_color_px(fdf[i], d);
	}
	return (d);
}

static t_point			get_next_pos(t_point data, int *fdf, int i, int n)
{
	data.posx[1] = data.zoom;
	data.posy[1] = data.posx[1] * data.rot;
	data.color_off = 0;
	if (n == 0)
	{
		data = get_next_pos_x(data, fdf, i);
	}
	if (n == 1)
	{
		data.posy[1] = -data.posy[1];
		data = get_next_pos_y(data, fdf, i);
	}
	return (data);
}

void					print_line_x(t_data *data, int *fdf, int len, int x)
{
	int			i;
	float		tmp[2];
	t_line		line;

	i = 1;
	tmp[0] = data->p.posx[0];
	tmp[1] = data->p.posy[0];
	while (i < len)
	{
		data->p = get_next_pos(data->p, fdf, i, 0);
		if (x > 0 && i > 1)
		{
			line.pos1x = data->p.posx[0];
			line.pos1y = data->p.posy[0];
			line.pos2x = data->p.posx[0] + data->p.posx[1];
			line.pos2y = data->p.posy[0] + data->p.posy[1];
			data = draw_line(data, line, 0);
		}
		data->p.posx[0] = data->p.posx[0] + data->p.posx[1];
		data->p.posy[0] = data->p.posy[0] + data->p.posy[1];
		i++;
	}
	data->p.posx[0] = tmp[0];
	data->p.posy[0] = tmp[1];
}

void					print_line_y(t_data *data, int *fdf, int len, int y)
{
	int			i;
	float		tmp[2];
	t_line		line;

	i = 1;
	tmp[0] = data->p.posx[2];
	tmp[1] = data->p.posy[2];
	while (i < len)
	{
		data->p = get_next_pos(data->p, fdf, i, 1);
		if (y > 0 && i > 1)
		{
			line.pos1x = data->p.posx[2];
			line.pos1y = data->p.posy[2];
			line.pos2x = data->p.posx[2] - data->p.posx[1];
			line.pos2y = data->p.posy[2] - data->p.posy[1];
			data = draw_line(data, line, 1);
		}
		data->p.posx[2] = data->p.posx[2] - data->p.posx[1];
		data->p.posy[2] = data->p.posy[2] - data->p.posy[1];
		i++;
	}
	data->p.posx[2] = tmp[0];
	data->p.posy[2] = tmp[1];
}
