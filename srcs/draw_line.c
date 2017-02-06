/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 20:50:04 by gtorresa          #+#    #+#             */
/*   Updated: 2016/02/10 20:38:39 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static void		put_pixel_to_img(t_data *e, int x, int y)
{
	int i;

	i = ((int)x * 4) + ((int)y * e->img_line);
	e->pixel_img[i] = e->p.px_color;
	e->pixel_img[++i] = e->p.px_color >> 8;
	e->pixel_img[++i] = e->p.px_color >> 16;
}

static void		init_dif(t_line line, int difx[2], int dify[2], float inc_px[4])
{
	inc_px[0] = line.pos1x;
	inc_px[1] = line.pos1y;
	difx[1] = 0;
	dify[1] = 0;
	difx[0] = line.pos2y - line.pos1y;
	dify[0] = line.pos2x - line.pos1x;
	if (difx[0] < 0)
	{
		difx[0] = -difx[0];
		difx[1] = 1;
	}
	if (dify[0] < 0)
	{
		dify[0] = -dify[0];
		dify[1] = 1;
	}
}

static int		get_inc_px(t_line line, float inc_px[4])
{
	int				loop;
	int				difx[2];
	int				dify[2];

	init_dif(line, difx, dify, inc_px);
	if (difx[0] > dify[0])
		loop = difx[0];
	else
		loop = dify[0];
	inc_px[2] = 1;
	inc_px[3] = 1;
	if (difx[0] > dify[0])
		inc_px[3] = (float)dify[0] / (float)difx[0];
	if (difx[0] < dify[0])
		inc_px[2] = (float)difx[0] / (float)dify[0];
	if (difx[1] == 1)
		inc_px[2] = -inc_px[2];
	if (dify[1] == 1)
		inc_px[3] = -inc_px[3];
	return (loop);
}

t_data			*draw_line(t_data *data, t_line line, int s)
{
	int				loop;
	float			inc_px[4];

	loop = get_inc_px(line, inc_px);
	while (loop > 0)
	{
		inc_px[0] += inc_px[3];
		inc_px[1] += inc_px[2];
		if ((inc_px[0] + data->r_pxx[s]) >= 0 &&
			(inc_px[0] + data->r_pxx[s]) < data->win_size_w &&
			(inc_px[1] + data->r_pxy[s]) >= 0 &&
			(inc_px[1] + data->r_pxy[s]) < data->win_size_h)
			put_pixel_to_img(data, inc_px[0] + data->r_pxx[s], inc_px[1] + data->r_pxy[s]);
		loop--;
	}
	if (data->p.color_off != 0 && (data->p.px_color = data->p.color_off))
		data->p.color_off = 0;
	return (data);
}
