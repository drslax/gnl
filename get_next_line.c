/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <anas.elouargui@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 04:39:02 by aelouarg          #+#    #+#             */
/*   Updated: 2018/10/21 07:38:59 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	unsigned int	ft_linelen(char *tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i] != '\n' && tab[i] != '\0')
		i++;
	return (i);
}

static	char			*ft_line(char *tab)
{
	if (ft_strchr(tab, '\n'))
	{
		ft_strcpy(tab, ft_strchr(tab, '\n') + 1);
		return (tab);
	}
	if (ft_linelen(tab) > 0)
	{
		ft_strcpy(tab, ft_strchr(tab, '\0'));
		return (tab);
	}
	return (NULL);
}

int						get_next_line(int const fd, char **line)
{
	char			*tmp;
	char			buff[BUFF_SIZE + 1];
	static char		*tab[256];
	int				ret;

	if (fd < 0 || BUFF_SIZE < 1 || !line || read(fd, buff, 0) < 0)
		return (-1);
	if (!(tab[fd]) && (tab[fd] = ft_strnew(0)) == NULL)
		return (-1);
	while (!(ft_strchr(tab[fd], '\n')) && (ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = tab[fd];
		tab[fd] = ft_strnjoin(tmp, buff, ret);
		free(tmp);
	}
	*line = ft_strsub(tab[fd], 0, ft_linelen(tab[fd]));
	if (ft_line(tab[fd]) == NULL)
		return (0);
	return (1);
}
