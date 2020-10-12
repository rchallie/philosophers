/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 23:19:43 by rchallie          #+#    #+#             */
/*   Updated: 2020/10/12 16:19:35 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_three.h"

char		*get_sem_name(int i)
{
	char	*test;
	char	*nbr;
	char	*buff;
	int		j;
	int		k;

	if (!(buff = malloc(sizeof(char) * 13)))
		return (NULL);
	memset(buff, 0, sizeof(char) * 13);
	test = "/eating_";
	nbr = ft_lutoa(i);
	j = 0;
	while (j < ft_strlen(test))
	{
		buff[j] = *(test + j);
		j++;
	}
	k = 0;
	while (j < ft_strlen(test) + ft_strlen(nbr))
		buff[j++] = *(nbr + k++);
	buff[j] = '\0';
	free(nbr);
	return (buff);
}

int			init_sems(t_philosopher *philosophers, int i)
{
	if ((philosophers[i].eating_name = get_sem_name(i)) == NULL)
		return (1);
	sem_unlink(philosophers[i].eating_name);
	if ((philosophers[i].eating =
		sem_open(philosophers[i].eating_name, O_CREAT, S_IRWXU, 1))
			== SEM_FAILED)
	{
		sem_unlink(philosophers[i].eating_name);
		if ((philosophers[i].eating =
			sem_open(philosophers[i].eating_name, O_CREAT, S_IRWXU, 1))
				== SEM_FAILED)
			return (1);
	}
	return (0);
}

void		fork_philos(
	t_philosopher *phi,
	pid_t *philos_pid,
	int i
)
{
	pid_t	child_process;

	if ((child_process = fork()) < 0)
	{
		write(1, "ERROR : Fork.\n", 14);
		exit(999);
	}
	else if (child_process == 0)
	{
		pthread_create(&phi[i].monitor, NULL,
		(void*)monitor_func, (void*)&phi[i]);
		routine(&phi[i]);
	}
	else
		philos_pid[i] = child_process;
}
