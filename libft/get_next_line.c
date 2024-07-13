/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:49:03 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/19 13:35:32 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_buff(int fd, char *sub)
{
	char	*buff;
	int		i;

	buff = (char *)malloc(sizeof(char ) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	i = 1;
	while (i > 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
			break ;
		buff[i] = '\0';
		sub = ft_strjoin(sub, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (sub);
}

char	*get_lines(char *buff)
{
	char	*line;
	int		i;

	i = 0;
	if (!buff[0])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	line = ft_substr(buff, 0, i + 1);
	return (line);
}

char	*get_sub(char *buff)
{
	char	*sub;
	int		i;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	i++;
	sub = ft_substr(buff, i, ft_strlen(buff) - i);
	free(buff);
	return (sub);
}

char	*get_next_line(int fd)
{
	static char	*sub;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	sub = get_buff(fd, sub);
	if (!sub)
		return (NULL);
	line = get_lines(sub);
	sub = get_sub(sub);
	return (line);
}
