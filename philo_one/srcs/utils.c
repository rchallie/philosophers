/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:28:00 by excalibur         #+#    #+#             */
/*   Updated: 2020/10/04 03:14:10 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../incs/philo_one.h"

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

void	ft_putstr(char *s)
{
	while (s && *s)
		write(1, s++, 1);
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

 void		print_msg(
	t_philosopher *phi,
	char *message
)
{
	char	buffer[100];
	char	*buff_timestamp;
	char	*buff_philo_number;
	
	if (phi->simulation->have_a_death == 1 && phi->is_died != 1)
		return ;
	else if (phi->is_died)
		phi->is_died = 0;
	buff_timestamp = ft_lutoa(get_actual_time() - phi->simulation->start_time);
	buff_philo_number = ft_lutoa((long unsigned)phi->number);
	memset(buffer, '\0', 100);
	
	int i = 0;
	int j = 0;
	while (buff_timestamp && *(buff_timestamp + i))
		buffer[j++] = buff_timestamp[i++];
	buffer[j++] = ' ';
	i = 0;
	while (buff_philo_number && *(buff_philo_number + i))
		buffer[j++] = buff_philo_number[i++];
	buffer[j++] = ' ';
	i = 0;
	while (message && *(message + i))
		buffer[j++] = message[i++];
	buffer[j++] = '\n';
	pthread_mutex_lock(&phi->simulation->can_write);
	ft_putstr(buffer);
	pthread_mutex_unlock(&phi->simulation->can_write);
	free(buff_timestamp);
	free(buff_philo_number);
}