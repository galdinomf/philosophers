/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:19:42 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/25 20:37:42 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_ind_i)
{
	//t_data	*data;

	printf("data->time_to_die = %d\n", ((t_philo_ind *) philo_ind_i)->data->time_to_die);
	//data = 	((t_philo_ind *) philo_ind_i)->data;
	
	return (NULL);
}

int	initialize_simulation(t_data *data)
{
	int	i;
	t_philo_ind	**philo_ind;

	philo_ind = initialize_philo_ind(data);
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		
		if (pthread_create(&data->philos[i], NULL, &routine, philo_ind[i]))
			return (1);
		printf("Thread #%d started\n", i);
	}

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (pthread_join(data->philos[i], NULL))
			return (2);
		printf("Thread #%d finished\n", i);
	}
	i = -1;
	while (++i < data->number_of_philosophers)
		free(philo_ind[i]);
	free(philo_ind);
	return (0);
}
