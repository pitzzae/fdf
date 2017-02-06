/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 16:35:18 by gtorresa          #+#    #+#             */
/*   Updated: 2016/01/21 16:39:44 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static int			get_len_map(char **map)
{
	char			**tmp;
	int				len;

	len = 0;
	tmp = ft_strsplit(map[0], ' ');
	while (tmp[len])
	{
		free(tmp[len]);
		len++;
	}
	free(tmp);
	return (len);
}

static t_fdf		extract_data_y(t_fdf fdf)
{
	int				x;
	int				y;

	x = 0;
	fdf.fdfy = (int**)malloc(sizeof(fdf.fdfy) * fdf.y);
	while (x < fdf.y)
	{
		y = 0;
		fdf.fdfy[x] = (int*)malloc(sizeof(fdf.fdfy) * fdf.x);
		while (y < fdf.x)
		{
			fdf.fdfy[x][y] = fdf.fdfx[y][x];
			if (fdf.v_max_min[0] < fdf.fdfx[y][x])
				fdf.v_max_min[0] = fdf.fdfx[y][x];
			if (fdf.v_max_min[1] > fdf.fdfx[y][x])
				fdf.v_max_min[1] = fdf.fdfx[y][x];
			y++;
		}
		x++;
	}
	return (fdf);
}

static t_fdf		extract_data_map(t_fdf fdf, char **line, int y)
{
	fdf.v_max_min[0] = 0;
	fdf.v_max_min[1] = 0;
	while (line[y])
	{
		fdf.fdfx[fdf.x][y + 1] = ft_atoi(line[y]);
		free(line[y]);
		y++;
	}
	free(line);
	return (fdf);
}

static t_fdf		extract_data_x(char **map, t_fdf fdf)
{
	char			**line;
	int				y;

	fdf.x = 1;
	fdf.y = get_len_map(map) + 1;
	fdf.fdfx = (int**)malloc(sizeof(fdf.fdfx) * fdf.y);
	fdf.fdfx[0] = (int*)malloc(sizeof(fdf.fdfx) * fdf.y);
	y = 0;
	while (y < fdf.y)
		fdf.fdfx[0][y++] = 0;
	while (map[fdf.x - 1][0] != '\0')
	{
		line = ft_strsplit(map[fdf.x - 1], ' ');
		free(map[fdf.x - 1]);
		y = 0;
		fdf.fdfx[fdf.x] = (int*)malloc(sizeof(fdf.fdfx) * fdf.y);
		fdf.fdfx[fdf.x][0] = 0;
		fdf = extract_data_map(fdf, line, y);
		fdf.x++;
	}
	free(map[fdf.x - 1]);
	fdf = extract_data_y(fdf);
	return (fdf);
}

t_fdf				read_map(int fd)
{
	char			*line;
	char			**map;
	int				pos;
	t_fdf			fdf;

	line = NULL;
	map = (char**)malloc(sizeof(map));
	pos = 0;
	while (get_next_line(fd, &line) == 1)
	{
		map[pos++] = ft_strdup(line);
		free(line);
		map = ft_tab_realloc(map, pos + 1);
		line = NULL;
	}
	map[pos++] = ft_strdup(line);
	map = ft_tab_realloc(map, pos + 1);
	free(line);
	map[pos] = "\0";
	fdf = extract_data_x(map, fdf);
	free(map);
	return (fdf);
}
