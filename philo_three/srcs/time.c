/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: excalibur <excalibur@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:07:17 by excalibur         #+#    #+#             */
/*   Updated: 2020/04/09 20:45:41 by excalibur        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_three.h"

/*
** @brief Get the difference between two timeval
** structur in microsecond.
**
** @param a first timeval.
** @param b secobd timeval.
** @return the difference in microsecond.
*/

long unsigned	get_time_diff(
	struct timeval a,
	struct timeval b
)
{
	return (((a.tv_sec * 1000000) + a.tv_usec)
			- ((b.tv_sec * 1000000) + b.tv_usec));
}

/*
** @brief Get timestamp in milliseconds.
**
** @param start_time start time of the simulation.
** @return timestamp in milliseconds.
*/

long unsigned	get_timestamp(
	struct timeval start_time
)
{
	struct timeval actual;

	gettimeofday(&actual, NULL);
	return (get_time_diff(actual, start_time) / 1000);
}

/*
** @brief Wait for a duration in microseconds.
**
** @param start a timeval structure, it's the
** time of reference for the waiting.
** @param time the duration.
*/

void			wait_for(
	struct timeval start,
	long unsigned time
)
{
	struct timeval actual;

	gettimeofday(&actual, NULL);
	while (get_time_diff(actual, start) < time)
	{
		usleep(1000);
		gettimeofday(&actual, NULL);
	}
}
