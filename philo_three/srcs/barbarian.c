/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barbarian.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: excalibur <excalibur@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 23:04:49 by excalibur         #+#    #+#             */
/*   Updated: 2020/04/10 13:04:06 by excalibur        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_three.h"

int		wait_for_end(
	t_simulation *simulation
)
{
	pthread_t		*headers;
	t_header		*h;
	long unsigned	i;
	int				status;

	if (!(headers = malloc(sizeof(pthread_t)
		* simulation->number_of_philosopher)))
		return (__HEADERS_THREADS_MALLOC);
	i = 0;
	if (!(h = malloc(sizeof(t_header) * simulation->number_of_philosopher)))
		return (__HEADERS_MALLOC);
	memset(h, 0, sizeof(t_header) * simulation->number_of_philosopher);
	while (i < simulation->number_of_philosopher)
	{
		h[i].pids = simulation->philosophers_pids;
		h[i].number = (long unsigned)i;
		h[i].nbr_philosopher = simulation->number_of_philosopher;
		pthread_create(&headers[i], NULL, (void *)header_routine, (void*)&h[i]);
		pthread_detach(headers[i++]);
		usleep(100);
	}
	i = 0;
	while (i < simulation->number_of_philosopher + 1)
		waitpid(simulation->philosophers_pids[i++], &status, 0);
	return (__SUCCESS);
}

void	*header_routine(void *raw)
{
	t_header		*h;
	int				status;
	long unsigned	i;

	h = (t_header*)raw;
	waitpid(h->pids[h->number], &status, 0);
	i = 0;
	while (i < h->nbr_philosopher)
	{
		kill(h->pids[i], SIGKILL);
		i++;
	}
	return (NULL);
}
