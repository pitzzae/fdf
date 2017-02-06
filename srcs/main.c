/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/16 16:38:58 by gtorresa          #+#    #+#             */
/*   Updated: 2016/01/21 16:48:42 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

JSAMPLE * image_buffer;	/* Points to large array of R,G,B-order data */
int image_height;	/* Number of rows in image */
int image_width;		/* Number of columns in image */
int nbr_img_frame;		/* Number of columns in image */

int			main(int argc, char **argv)
{
	char			*line;
	char			**map;
	int				pos;
	int				fd[2];
	t_fdf			fdf;

	if (argc == 3)
	{
		fd[0] = open(argv[1], O_RDONLY);
		fd[1] = open(argv[2], O_RDONLY);
		if (fd[0]  < 0 && fd[1]  < 0)
			ft_putendl("file error");
		else
		{
			fdf = read_map(fd[0] );
			close(fd[0]);
			nbr_img_frame = 0;
			return (init_x11(fdf, argv[1], fd[1]));
		}
	}
	else
		ft_putendl("file error");
	return (0);
}
