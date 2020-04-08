/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: excalibur <excalibur@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:28:00 by excalibur         #+#    #+#             */
/*   Updated: 2020/04/08 20:05:41 by excalibur        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
** @brief Get the length of the string.
**
** @return the length. If the string is NULL
** return 0.
*/

int				ft_strlen(
	char *str
)
{
	int i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (*str++)
		i++;
	return (i);
}

/*
** @brief String to long unsigned.
**
** @param str the string.
** @return the long unsigned.
*/

long unsigned	ft_atolu(
	char *str
)
{
	long unsigned rtn;

	rtn = 0;
	if (str)
		while (*str >= '0' && *str <= '9')
			rtn = (rtn * 10) + (*str++ - '0');
	return (rtn);
}

/*
** @brief Long unsigned to string.
**
** @param nbr the long unsigned.
** @return the string.
*/

char			*ft_lutoa(
	long unsigned nbr
)
{
	int				len;
	char			*rtn;
	long unsigned	nbr_save;

	len = 0;
	if ((nbr_save = nbr) == 0)
		len++;
	else
		while (nbr > 0)
		{
			nbr /= 10;
			len++;
		}
	if (!(rtn = malloc(sizeof(char) * (len + 1))))
		return ((void *)0);
	rtn[len--] = 0;
	if (nbr_save == 0)
		rtn[0] = '0';
	else
		while (nbr_save > 0)
		{
			rtn[len--] = (nbr_save % 10) + '0';
			nbr_save /= 10;
		}
	return (rtn);
}
