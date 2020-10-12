/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:07:17 by excalibur         #+#    #+#             */
/*   Updated: 2020/10/11 20:00:53 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_two.h"

long unsigned	get_actual_time(void)
{
	struct timeval actual;

	gettimeofday(&actual, NULL);
	return (actual.tv_sec * 1000 + actual.tv_usec / 1000);
}

/*
** @brief Get the difference between two timeval
** structur in microsecond.
**
** @param a first timeval.
** @param b secobd timeval.
** @return the difference in microsecond.
*/

long unsigned	get_time_diff(
	long unsigned a,
	long unsigned b
)
{
	return (a - b);
}

/*
** @brief Get timestamp in milliseconds.
**
** @param start_time start time of the simulation.
** @return timestamp in milliseconds.
*/

long unsigned	get_timestamp(
	long unsigned start_time
)
{
	return (get_time_diff(get_actual_time(), start_time));
}

/*
** @brief Wait for a duration in microseconds.
**
** @param start a timeval structure, it's the
** time of reference for the waiting.
** @param time the duration.
*/

void			wait_for(
	long unsigned time
)
{
	long unsigned start;

	start = get_actual_time();
	while (get_actual_time() - start < time)
		usleep(100);
}
