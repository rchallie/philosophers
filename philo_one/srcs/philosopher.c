/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:18:48 by excalibur         #+#    #+#             */
/*   Updated: 2020/10/06 22:20:37 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

/*
** @brief Philosopher eat. Get forks.
** eat for time_to_eat and leave them.
**
** @param philosopher a pointer to the
** philosopher.
*/

static void		eat(
	t_philosopher *philosopher
)
{
	if (!(philosopher->number % 2))
		pthread_mutex_lock(philosopher->right_fork);
	else
		pthread_mutex_lock(philosopher->left_fork);
	print_msg(philosopher, "has taken a fork\n");
	if (philosopher->number % 2)
		pthread_mutex_lock(philosopher->right_fork);
	else
		pthread_mutex_lock(philosopher->left_fork);
	print_msg(philosopher, "has taken a fork\n");
	if (*philosopher->have_a_death != 1)
	{
		pthread_mutex_lock(&philosopher->eating);
		print_msg(philosopher, "eating\n");
		philosopher->last_time_eated = get_actual_time();
		wait_for(philosopher->time_to_eat);
		pthread_mutex_unlock(&philosopher->eating);
	}
	pthread_mutex_unlock(
		philosopher->left_fork);
	pthread_mutex_unlock(
		philosopher->right_fork);
	philosopher->number_meal++;
}

/*
** @brief the routine of a philosopher.
** He will thinking, eating, sleeping.
** If another philosopher is dead or he
** have ate enought, he will be
** stopped.
**
** @param phi a pointer to the philosopher.
** (it's a void pointer because it's the routine
** called by thread creation function).
** @return NULL.
*/

void			*routine(
	void *phi
)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher*)phi;
	while (42 && *philosopher->have_a_death == 0)
	{
		eat(philosopher);
		if (*philosopher->have_a_death == 1
			|| (philosopher->each_must_eat != -1 && philosopher->number_meal
			>= philosopher->each_must_eat))
		{
			philosopher->is_died = 1;
			break ;
		}
		print_msg(philosopher, "sleeping\n");
		if (*philosopher->have_a_death == 1)
			break ;
		wait_for(philosopher->time_to_sleep);
		print_msg(philosopher, "thinking\n");
	}
	return (NULL);
}
