/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 22:04:50 by excalibur         #+#    #+#             */
/*   Updated: 2020/10/12 15:31:04 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_three.h"

static void		death(
	t_philosopher *philosopher
)
{
	philosopher->is_died = 1;
	print_msg(philosopher, "died\n");
	sem_wait(philosopher->can_write);
	exit(0);
}

/*
** @brief Check philosopher vital constants.
** If the philosopher didn't eat before time_to_die
** he will kill him. Or if the philosopher ate enought
** in comparasion of each_must_eat (if it's initialized)
** the monitor will stop the philosopher.
**
** @param the philosopher.
*/

void			*monitor_func(
	void *phi
)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher*)phi;
	while (42 && *philosopher->have_a_death == 0)
	{
		if (philosopher->is_died == 1)
			break ;
		sem_wait(philosopher->eating);
		if ((get_actual_time() - philosopher->last_time_eated)
			> philosopher->time_to_die)
		{
			death(philosopher);
			sem_post(philosopher->eating);
			break ;
		}
		sem_post(philosopher->eating);
		usleep(1000);
	}
	return (NULL);
}
