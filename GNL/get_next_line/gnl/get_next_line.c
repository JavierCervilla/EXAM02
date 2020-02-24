/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 23:07:54 by jcervill          #+#    #+#             */
/*   Updated: 2020/02/19 23:27:05 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str)
{
	int i = 0;
	while (*str != '\n' && *str)
		str++;
	if (*str == '\n')
		return (str);
	else
		return (NULL);
}

char	*ft_strdup(char *str)
{
	int i = 0;
	char *tmp;
	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(str)))))
		return (NULL);
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int i = 0;
	char *ret;

	if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (*s1)
		ret[i++] = *s1++;
	while (*s2)
		ret[i++] = *s2++;
	ret[i] = 0;
	return (ret);
}

int		get_next_line(char **line)
{
	int			ret;
	static char *gnl;
	char		*tmp;
	char		buff[512];
	while (!(ft_strchr(gnl)))
	{
		ret = read(0, buff, 511);
		if (ret < 0)
			return (-1);
		if (!ret)
			break;
		buff[ret] = 0;
		tmp = ft_strjoin(gnl, buff);
		free (gnl);
		gnl = tmp;
	}
	if (tmp = ft_strchr(gnl))
	{
		*tmp = 0;
		*line = ft_strdup(gnl);
		tmp = ft_strdup(++tmp);
		free (gnl);
		gnl = tmp;
		return (0);
	}
}
