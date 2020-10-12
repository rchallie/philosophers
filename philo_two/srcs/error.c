/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 23:05:40 by rchallie          #+#    #+#             */
/*   Updated: 2020/10/11 20:01:47 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_two.h"

int		error_command_argument(void)
{
	char *help;
	char *cmd1;
	char *cmd2;

	help = "Please use this command :\n";
	cmd1 = "./philo_two number_of_philosopher time_to_die time_to_eat ";
	cmd2 = "time_to_sleep [number_of_time_each_philosophers_must_eat]\n";
	write(2, help, ft_strlen(help));
	write(2, cmd1, ft_strlen(cmd1));
	write(2, cmd2, ft_strlen(cmd2));
	return (__COMMAND_ARGUMENTS);
}

int		error_bad_argument(void)
{
	char *help;

	help = "ERROR : One argument is wrong, please, only use numbers.\n";
	write(2, help, ft_strlen(help));
	return (error_command_argument());
}

int		error_init_philosophers(void)
{
	char *help;
	char *help2;

	help = "ERROR : Sorry, an error appear during the initialisation of ";
	help2 = "philosophers.\n";
	write(2, help, ft_strlen(help));
	write(2, help2, ft_strlen(help2));
	return (__INIT_PHILOSOPHERS);
}

int		error_init_forks(void)
{
	char *help;
	char *help2;

	help = "ERROR : Sorry, an error appear during the initialisation of ";
	help2 = "forks.\n";
	write(2, help, ft_strlen(help));
	write(2, help2, ft_strlen(help2));
	return (__INIT_FORKS);
}
