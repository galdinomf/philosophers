/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:19:42 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/28 15:10:00 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_end_simulation_var_value(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (data->counter[i] < data->number_of_times_each_philosopher_must_eat)
			break ;
	}
	data->end_simulation = (i == data->number_of_philosophers);
}

void	*routine(void *philo_ind_i)
{
	t_data	*data;
//	int	c;
	int	ind;

	//printf("data->time_to_die = %d\n", ((t_philo_ind *) philo_ind_i)->data->time_to_die);
	data = 	((t_philo_ind *) philo_ind_i)->data;
	ind = ((t_philo_ind *) philo_ind_i)->ind;

//	c = 0;
	while (1)
	{
		pthread_mutex_lock(&data->counter_mutex);
		if (data->end_simulation)
		{
			pthread_mutex_unlock(&data->counter_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->counter_mutex);
		printf("%d %d is thinking\n", get_timestamp(data), ind + 1);
		while (try_to_eat(philo_ind_i))
			;
		pthread_mutex_lock(&data->counter_mutex);
		data->counter[ind]++;
		set_end_simulation_var_value(data);
		pthread_mutex_unlock(&data->counter_mutex);
		printf("%d %d is sleeping\n", get_timestamp(data), ind + 1);
		usleep(data->time_to_sleep * 1000);
		/*
		pthread_mutex_lock(&data->mutex);
		data->c++;
		if (data->c > data->number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_unlock(&data->mutex);
			break;
		}
		pthread_mutex_unlock(&data->mutex);
		*/
	}
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
	}

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (pthread_join(data->philos[i], NULL))
			return (2);
	}
	i = -1;
	while (++i < data->number_of_philosophers)
		free(philo_ind[i]);
	free(philo_ind);
	return (0);
}
