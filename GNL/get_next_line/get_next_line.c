/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:44:55 by jcervill          #+#    #+#             */
/*   Updated: 2020/02/19 22:57:02 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str)
{
	while (*str != '\n' && *str)
		str++;
	if (*str == '\n')
		return (str);
	return (NULL);
}

char	*ft_strdup(char *str)
{
	int i = 0;
	char *stret;
	if (!(stret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	while (str[i])
	{
		stret[i] = str[i];
		i++;
	}
	stret[i] = 0;
	return (stret);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int i = 0;
	char *stret;

	if (!(stret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (*s1)
		stret[i++] = *s1++;
	while (*s2)
		stret[i++] = *s2++;
	stret[i] = 0;
	return (stret);
}

int get_next_line(char **line)
{
	int ret = 0;
	char buff[512];
	static char *gnl;
	char *tmp;

	while (!(ft_strchr(gnl)))
	{
		ret = read(0,buff,511);
		if (ret < 0)
			return (-1);
		if (!ret)
			break;
		buff[ret] = 0;
		tmp = ft_strjoin(gnl,buff);
		free (gnl);
		gnl = tmp;
	}
	if ((tmp = ft_strchr(gnl)))
	{
		*tmp = 0;
		*line = ft_strdup(++tmp);
		free (gnl);
		gnl = tmp;
		return (1);
	}
	else
	{
		*line = ft_strdup(gnl);
		free (gnl);
		gnl = 0;
		return(0);
	}
}
