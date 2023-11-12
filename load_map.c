/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haguezou <haguezou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:37:33 by abdel-ou          #+#    #+#             */
/*   Updated: 2023/11/03 11:40:45 by haguezou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**memory_allocete(char *file_name)
{
	int		fd;
	int		x;
	int		y;
	char	*line;
	char	**new;

	fd = open(file_name, O_RDONLY, 0);
	line = get_next_line(fd);
	x = ft_strlen(line);
	y = 0;
	while (line)
	{
		y++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	new = (char **)malloc(sizeof(char *) * (y + 1));
	while (y > 0)
		new[--y] = (char *)malloc(sizeof(char) * (x + 1));
	close(fd);
	return (new);
}

char	**load_map(char *file_name)
{
	int		fd;
	char	**new;
	char	*line;
	int		i;
	int		j;

	new = memory_allocete(file_name);
	fd = open(file_name, O_RDONLY, 0);
	line = get_next_line(fd);
	i = 0;
	j = 0;
	while (line)
	{
		while (line[i])
		{
			new[j][i] = line[i];
			i++;
		}
		free(line);
		line = get_next_line(fd);
			if (!line)
				new[j][i - 1] = '\0';
		j++;
		i = 0;
	}
	free(line);
	close(fd);
	return (new);
}

