/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 08:17:45 by gtorresa          #+#    #+#             */
/*   Updated: 2016/02/10 20:39:04 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void			draw_full_rec(t_data *d, int x, int y, int c)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (i < 25)
	{
		while (j < 50)
		{
			mlx_pixel_put(d->mlx, d->win, x + j, y + i, c);
			j++;
		}
		j = 0;
		i++;
	}
}

void			save_txt_color(t_data *data)
{
	int		fd;
	char	*color;
	int		i;

	i = 0;
	color = ft_strjoin_free(ft_itoa(data->p.color_ref[i++]), ";", 1);
	while (i < C_SP)
	{
		color = ft_strjoin_free(color, ft_itoa(data->p.color_ref[i]), 3);
		color = ft_strjoin_free(color, ";", 1);
		i++;
	}
	fd = open("color.hex", O_RDWR | O_CREAT);
	if (fd > 0)
		fchmod(fd, 000640);
	if (fd > 0 && write(fd, color, ft_strlen(color)) != ft_strlen(color))
		write(2, "There was an error writing to color.hex\n", 40);
	close(fd);
}

t_data			*read_txt_color(t_data *data, int fd)
{
	char	*line;
	char	**tmp;
	int		i;

	i = 0;
	line = NULL;
	get_next_line(fd, &line);
	tmp = ft_strsplit(line, ';');
	while (tmp[i])
		i++;
	data->p.color_ref = (int*)malloc(sizeof(data->p.color_ref) * i);
	i = 0;
	while (tmp[i])
	{
		data->p.color_ref[i] = ft_atoi(tmp[i]);
		free(tmp[i]);
		i++;
	}
	C_SP = i;
	free(tmp);
	free(line);
	return (data);
}

void			init_color(t_data *data)
{
	int		i;
	int		fd;

	i = 0;
	fd = open("color.hex", O_RDONLY);
	if (fd > 0)
		read_txt_color(data, fd);
	else
		read_c_color(data);
	close(fd);
}

int				get_color_px(int p, t_point point)
{
	int		color_select;

	if (p < 0)
	{
		color_select = -((float)point.color_ref_len /
			(float)point.v_max_min[1] * p);
		color_select = (color_select / 2) + (point.color_ref_len / 2);
	}
	else
	{
		color_select = (float)point.color_ref_len /
		(float)point.v_max_min[0] * p;
		color_select = (color_select / 2);
	}
	return (point.color_ref[color_select]);
}
