/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 22:04:50 by excalibur         #+#    #+#             */
/*   Updated: 2020/10/04 03:10:52 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

/*
** @brief Check if the philosopher ate enought.
** The element of comparasion is the each_must_eat.
** If each_must_eat is not defined (-1) he will never
** ate_enought.
**
** @param philosopher the philosopher.
** @return 1 if the philosopher ate enought else 0.
*/

// static int		ate_enought(
// 	t_philosopher *philosopher
// )
// {
// 	if (philosopher->simulation->each_must_eat != -1 &&
// 		philosopher->number_meal >= philosopher->simulation->each_must_eat)
// 	{
// 		pthread_mutex_unlock(&philosopher->simulation->can_write);
// 		return (1);
// 	}
// 	return (0);
// }

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
	while (42 && philosopher->simulation->have_a_death == 0)
	{
		if ((philosopher->simulation->each_must_eat != -1
			&& philosopher->number_meal
			>= philosopher->simulation->each_must_eat) || philosopher->simulation->have_a_death == 1)
			break ;
		if ((get_actual_time() - philosopher->last_time_eated)
			> philosopher->simulation->time_to_die)
		{
			philosopher->simulation->have_a_death = 1;
			philosopher->is_died = 1;
			print_msg(philosopher, "died");
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
