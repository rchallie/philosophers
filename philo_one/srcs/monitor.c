/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 22:04:50 by excalibur         #+#    #+#             */
/*   Updated: 2020/10/06 22:16:16 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

static void		death(
	t_philosopher *philosopher
)
{
	*philosopher->have_a_death = 1;
	philosopher->is_died = 1;
	print_msg(philosopher, "died\n");
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
		pthread_mutex_lock(&philosopher->eating);
		if ((get_actual_time() - philosopher->last_time_eated)
			> philosopher->time_to_die)
		{
			if (*philosopher->have_a_death != 1)
				death(philosopher);
			pthread_mutex_unlock(&philosopher->eating);
			break ;
		}
		pthread_mutex_unlock(&philosopher->eating);
		usleep(1000);
	}
	return (NULL);
}
