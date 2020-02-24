/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:57:50 by jcervill          #+#    #+#             */
/*   Updated: 2020/02/19 21:34:03 by jcervill         ###   ########.fr       */
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

char *ft_strchr(char *s)
{
	while (*s != '\n' && *s)
		s++;
	if (*s == '\n')
		return (s);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int i = 0;
	char *str;

	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(char *s)
{
	int i = 0;
	char *str;
	if (!(str = (char *)malloc((sizeof(char) * ft_strlen(s) + 1))))
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
int		get_next_line(char **line)
{
	static char *gnl;
	char		*tmp;
	char		buff[512];
	int			ret;

	if (!line)
		return (-1);
	if (gnl == NULL)
		gnl = ft_strdup("");
	while (!(ft_strchr(gnl)))
	{
		ret = read (0, buff, 511);
		if (ret < 0)
			return (-1);
		if (!ret)
			break;
		buff[ret] = '\0';
		tmp = ft_strjoin(gnl, buff);
		free(gnl);
		gnl = tmp;
	}
	if ((tmp = ft_strchr(gnl)))
	{
		*tmp = '\0';
		*line = ft_strdup(gnl);
		tmp = ft_strdup (++tmp);
		free (gnl);
		gnl = tmp;
		return (1);
	}
	else
	{
		*line = ft_strdup(gnl);
		free(gnl);
		gnl = NULL;
		return (0);
	}

}
