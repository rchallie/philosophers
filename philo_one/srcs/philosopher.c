/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: excalibur <excalibur@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:18:48 by excalibur         #+#    #+#             */
/*   Updated: 2020/04/07 23:39:52 by excalibur        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incs/philo_one.h"

/**
 ** @brief Philosopher eat. Get forks.
 ** eat for time_to_eat and leave them.
 **
 ** @param philosopher a pointer to the
 ** philosopher.
 **/
static void eat(
    t_philosopher *philosopher
)
{    
    philosopher->is_on_eat = 1;
    pthread_mutex_lock(
        &philosopher->simulation->forks[philosopher->number - 1]);
    philosopher->take_fork_l = 1;
    pthread_mutex_lock(&philosopher->simulation->forks[(philosopher->number)
        % philosopher->simulation->number_of_philosopher]);
    philosopher->take_fork_r = 1;
    philosopher->is_eating = 1;
    philosopher->number_meal++;
    gettimeofday(&philosopher->last_time_eated, NULL);
    wait_for(philosopher->last_time_eated,
        philosopher->simulation->time_to_eat * 1000);
    pthread_mutex_unlock(
        &philosopher->simulation->forks[philosopher->number - 1]);
    pthread_mutex_unlock(
        &philosopher->simulation->forks[(philosopher->number)
        % philosopher->simulation->number_of_philosopher]);
    philosopher->is_on_eat = 0;
}

/**
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
 **/
void    *routine(
    void *phi
)
{
    t_philosopher *philosopher;
    struct timeval start;

    philosopher = (t_philosopher*)phi;
    gettimeofday(&philosopher->last_time_eated, NULL);
    pthread_create(&philosopher->monitor, NULL,
        (void*)monitor_func, (void*)philosopher);
    pthread_detach(philosopher->monitor);
    while (42 && philosopher->simulation->have_a_death == 0)
    {
        philosopher->is_thinking = 1;
        eat(philosopher);
        if (philosopher->simulation->each_must_eat != -1
            && philosopher->number_meal
            >= philosopher->simulation->each_must_eat)
            break;
        philosopher->is_sleeping = 1;
        gettimeofday(&start, NULL);
        wait_for(start, philosopher->simulation->time_to_sleep);
    }
    return (NULL);
}