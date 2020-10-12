/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 23:19:43 by rchallie          #+#    #+#             */
/*   Updated: 2020/10/11 23:22:39 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_two.h"

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
