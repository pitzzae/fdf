/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_move_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 16:42:05 by gtorresa          #+#    #+#             */
/*   Updated: 2016/02/10 20:38:46 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void			extract_read_data_line(char *line, int	exp_intline[5])
{
	char			**exp_line;

	exp_line = ft_strsplit(line, ' ');
	if (exp_line[0] && exp_line[1] && exp_line[2] && exp_line[3]  && exp_line[4] && !exp_line[5])
	{
		exp_intline[0] = atoi(exp_line[0]);
		exp_intline[1] = atoi(exp_line[1]);
		exp_intline[2] = atoi(exp_line[2]);
		exp_intline[3] = atoi(exp_line[3]);
		exp_intline[4] = atoi(exp_line[4]);
		free(exp_line[0]);
		free(exp_line[1]);
		free(exp_line[2]);
		free(exp_line[3]);
		free(exp_line[4]);
	}
	else
	{
		ft_putstr("motion parse error");
		exp_intline[0] = 0;
		exp_intline[1] = 0;
		exp_intline[2] = 0;
		exp_intline[3] = 0;
		exp_intline[4] = 1;
	}
	free(exp_line);
}

t_motion		*ft_motionnew(char *line)
{
	t_motion	*motion;
	int			exp_intline[5];

	motion = (t_motion*)malloc(sizeof(*motion));
	if (motion != NULL)
	{
		if (line == NULL)
		{
			motion->posx = 0;
			motion->posy = 0;
			motion->zoom = 0;
			motion->rot = 0;
			motion->speed = 0;
		}
		else
		{
			extract_read_data_line(line, exp_intline);
			motion->posx = exp_intline[0];
			motion->posy = exp_intline[1];
			motion->zoom = exp_intline[2];
			motion->rot = exp_intline[3];
			motion->speed = exp_intline[4];
		}
		motion->next = NULL;
		return (motion);
	}
	return (NULL);
}

void	ft_motionadd(t_motion **amotion, t_motion *new)
{
	t_motion	*tmp;

	tmp = (*amotion);
	if (new)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_motion		*read_move_conf(int fd_move)
{
	int				loop;
	char			*line;
	t_motion		*motion;

	loop = 0;
	motion = NULL;
	line = NULL;
	while (get_next_line(fd_move, &line) == 1)
	{
		if (line && line[0] != '#')
		{
			if (loop == 0)
			{
				motion = ft_motionnew(line);
				loop++;
			}
			else
				ft_motionadd(&motion, ft_motionnew(line));
		}
		free(line);
	}
	close(fd_move);
	return (motion);
}

int				get_next_position(t_data *data)
{
	if (data->p.posx[0] == data->motion->posx && data->p.posy[0] == data->motion->posy &&
		data->p.zoom == data->motion->zoom && data->p.rot == data->motion->rot)
		return (1);
	else
		return (0);
}

float			get_paspx(float pos1, float pos2, float speed)
{
	float			res[2];
	res[0] = pos1 / pos2;
	res[1] = pos2 / pos1;
	if (res[0] > res[1])
		return (res[1] * speed);
	else
		return (res[0] * speed);
	return (1);
}

void			move_to_next_position(t_data *data, t_motion *motion)
{
	float			pas_x;
	float			pas_y;
	int				out[2];

	out[0] = 1;
	out[1] = 1;
	pas_x = get_paspx(motion->posy, motion->posx, motion->speed);
	pas_y = get_paspx(motion->posy, motion->posx, motion->speed);
	printf("%lf %lf\n", pas_x, pas_x);
	if (data->p.posx[0] > motion->posx)
		pas_x = -pas_x;
	if (data->p.posy[0] > motion->posy)
		pas_y = -pas_y;
	while (out[0] == 1 || out[1] == 1)
	{
		if ((pas_x > 0  && data->p.posx[0] < motion->posx) || 
			(pas_x < 0  && data->p.posx[0] > motion->posx))
			data->p.posx[0] += pas_x;
		else
			out[0] = 0;
		if ((pas_y > 0  && data->p.posy[0] < motion->posy) || 
			(pas_y < 0  && data->p.posy[0] > motion->posy))
			data->p.posy[0] += pas_y;
		else
			out[1] = 0;
		data->p.posx[2] = data->p.posx[0];
		data->p.posy[2] = data->p.posy[0];
		data->p.zoom = motion->zoom;
		ft_print_fdf(*data);
	}
}

void 			free_listmotion(t_motion *motion)
{
	t_motion		*motion_tmp;

	motion_tmp = motion;
	while (motion_tmp)
	{
		motion_tmp = motion->next;
		printf("%d %d\n", motion->posx, motion->posy);
		free(motion);
		motion = motion_tmp;
	}
}

int				read_move_space(t_data *data, t_motion *motion)
{
	int				i;
	t_motion		*motion_tmp;

	motion_tmp = motion;
	while (motion)
	{
		move_to_next_position(data, motion);
		motion = motion->next;
		printf("next point\n");
	}
	free_listmotion(motion_tmp);
}