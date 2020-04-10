/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: excalibur <excalibur@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 22:04:50 by excalibur         #+#    #+#             */
/*   Updated: 2020/04/10 12:48:44 by excalibur        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_three.h"

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

static void		print_msg(
	long unsigned timestamp,
	int philosopher_number,
	char *message,
	int *value_to_reset
)
{
	char	*buff_timestamp;
	char	*buff_philo_number;

	buff_timestamp = ft_lutoa(timestamp);
	buff_philo_number = ft_lutoa((long unsigned)philosopher_number);
	write(1, buff_timestamp, ft_strlen(buff_timestamp));
	write(1, " ", 1);
	write(1, buff_philo_number, ft_strlen(buff_philo_number));
	write(1, " ", 1);
	write(1, message, ft_strlen(message));
	write(1, "\n", 1);
	if (value_to_reset)
		*value_to_reset = 0;
	free(buff_timestamp);
	free(buff_philo_number);
}

/*
** @brief Check states status of philosopher
** and print the message associate. This is
** a critical part of the message the it's
** protected by semaphores.
**
** @param philosopher the philosopher.
*/

static void		phi_messages(
	t_philosopher *philosopher
)
{
	sem_wait(philosopher->simulation->can_write);
	if (philosopher->is_thinking == 1)
		print_msg(get_timestamp(philosopher->simulation->start_time),
			philosopher->number, "is thinking", &philosopher->is_thinking);
	if (philosopher->take_fork_l == 1)
		print_msg(get_timestamp(philosopher->simulation->start_time),
			philosopher->number, "has taken a fork", &philosopher->take_fork_l);
	if (philosopher->take_fork_r == 1)
		print_msg(get_timestamp(philosopher->simulation->start_time),
			philosopher->number, "has taken a fork", &philosopher->take_fork_r);
	if (philosopher->is_eating == 1)
		print_msg(get_timestamp(philosopher->simulation->start_time),
			philosopher->number, "is eating", &philosopher->is_eating);
	if (philosopher->is_sleeping == 1)
		print_msg(get_timestamp(philosopher->simulation->start_time),
			philosopher->number, "is sleeping", &philosopher->is_sleeping);
	sem_post(philosopher->simulation->can_write);
}

/*
** @brief Check if the philosopher ate enought.
** The element of comparasion is the each_must_eat.
** If each_must_eat is not defined (-1) he will never
** ate_enought.
**
** @param philosopher the philosopher.
** @return 1 if the philosopher ate enought else 0.
*/

static int		ate_enought(
	t_philosopher *philosopher
)
{
	if (philosopher->simulation->each_must_eat != -1 &&
		philosopher->number_meal >= philosopher->simulation->each_must_eat)
	{
		sem_post(philosopher->simulation->can_write);
		return (1);
	}
	return (0);
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
	struct timeval	actual;

	philosopher = (t_philosopher*)phi;
	while (42)
	{
		gettimeofday(&actual, NULL);
		if (get_time_diff(actual, philosopher->last_time_eated)
			> philosopher->simulation->time_to_die * 1000
			&& philosopher->is_on_eat != 1)
		{
			sem_wait(philosopher->simulation->can_write);
			print_msg(get_timestamp(philosopher->simulation->start_time),
			philosopher->number, "died", NULL);
			break ;
		}
		phi_messages(philosopher);
		if (ate_enought(philosopher) == 1)
			break ;
		usleep(1000);
	}
	exit(0);
	return (NULL);
}
