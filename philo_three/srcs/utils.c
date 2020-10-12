/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:28:00 by excalibur         #+#    #+#             */
/*   Updated: 2020/10/11 23:31:42 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_three.h"

/*
** @brief Get the length of the string.
**
** @return the length. If the string is NULL
** return 0.
*/

int				ft_strlen(
	const char *str
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

size_t			ft_strlcpy(
	char *dst,
	const char *src,
	size_t dstsize
)
{
	size_t i;
	size_t src_len;

	i = 0;
	if (!dst || !src)
		return (0);
	src_len = ft_strlen(src);
	if (!dstsize)
		return (src_len);
	while (src[i] != '\0' && i < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize < src_len)
		dst[dstsize - 1] = '\0';
	else if (dstsize != 0)
		dst[i] = '\0';
	return (src_len);
}

/*
** @brief Print a message with timestamp, philosopher
** number and reset the value for which the message
** was printed.
**
** @param timestamp the timestamp.
** @param philosopher_number the philosopher number.
** @param message the message to print.
** @param value_to_reset the value to reset.
*/

void			print_msg(
	t_philosopher *phi,
	char *message
)
{
	char	buffer[100];
	char	*buff_timestamp;
	char	*buff_phi_number;
	int		j;

	j = 0;
	memset(buffer, '\0', 100);
	if (*phi->have_a_death == 1 && phi->is_died != 1)
		return ;
	else if (phi->is_died)
		phi->is_died = 0;
	buff_timestamp = ft_lutoa(get_timestamp(phi->start_time));
	buff_phi_number = ft_lutoa((long unsigned)phi->number);
	j = ft_strlcpy(buffer, buff_timestamp, ft_strlen(buff_timestamp));
	memset(buffer + j++, ' ', 1);
	j += ft_strlcpy(buffer + j, buff_phi_number, ft_strlen(buff_phi_number));
	memset(buffer + j++, ' ', 1);
	j += ft_strlcpy(buffer + j, message, ft_strlen(message));
	j = 0;
	sem_wait(phi->can_write);
	while (buffer[j])
		write(1, &buffer[j++], 1);
	sem_post(phi->can_write);
	(buff_timestamp) ? free(buff_timestamp) : 0;
	(buff_phi_number) ? free(buff_phi_number) : 0;
}
