/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:19:42 by mgaldino          #+#    #+#             */
/*   Updated: 2022/11/08 11:04:55 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_should_end(t_data *data)
{
	 pthread_mutex_lock(&data->counter_mutex);
	if (data->end_simulation)
	{
		pthread_mutex_unlock(&data->counter_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->counter_mutex);
		return (0);
}

void	set_end_simulation_var_value(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->counter_mutex);
		if (data->counter[i] < data->number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_unlock(&data->counter_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->counter_mutex);
	}
	if (i == data->number_of_philosophers)
	{
		
		pthread_mutex_lock(&data->counter_mutex);
		data->end_simulation = 1;
		pthread_mutex_unlock(&data->counter_mutex);
		
		pthread_mutex_lock(&data->mutex);
		data->can_show_messages = 0;
		pthread_mutex_unlock(&data->mutex);
	}
}

void	*death_check(void *philo_ind)
{
	int	i;
	t_data	*data;
	int	eat_time_i;
	int	current_time;

	data = (*(t_philo_ind **) philo_ind)->data;
	i = -1;
	while (1)
	{
		++i;
		if (i == data->number_of_philosophers)
			i = 0;
		current_time = get_timestamp(data);
		pthread_mutex_lock(&data->eat_time_mutex[i]);
		eat_time_i = data->eat_time[i];
		if ((current_time - eat_time_i) > data->time_to_die)
		{
			display_message("died", ((t_philo_ind **) philo_ind)[i]);
			pthread_mutex_lock(&data->counter_mutex);
		
		pthread_mutex_lock(&data->mutex);
			data->end_simulation = 1;
		data->can_show_messages = 0;
			pthread_mutex_unlock(&data->eat_time_mutex[i]);
			pthread_mutex_unlock(&data->counter_mutex);
		pthread_mutex_unlock(&data->mutex);
			break;
		}
		else
			pthread_mutex_unlock(&data->eat_time_mutex[i]);
		//pthread_mutex_unlock(&data->eat_time_mutex[i]);	
	}
	return (NULL);
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
		if (simulation_should_end(data))
			break ;
		display_message("is thinking", philo_ind_i);
		//printf("%d %d is thinking\n", get_timestamp(data), ind + 1);
		while (try_to_eat(philo_ind_i))
		{
			if (simulation_should_end(data))
				break ;
			//usleep(1000);
		}
		
		pthread_mutex_lock(&data->counter_mutex);
		if (data->end_simulation == 0)
		{
			data->counter[ind]++;
			
		pthread_mutex_unlock(&data->counter_mutex);
		}
		else
			pthread_mutex_unlock(&data->counter_mutex);
			
		if (data->number_of_times_each_philosopher_must_eat)
			set_end_simulation_var_value(data);
		display_message("is sleeping", philo_ind_i);
		//printf("%d %d is sleeping\n", get_timestamp(data), ind + 1);
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

		if (pthread_create(&data->killer, NULL, &death_check, philo_ind))
			return (1);	



	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (pthread_join(data->philos[i], NULL))
			return (2);
	}
		if (pthread_join(data->killer, NULL))
			return (2);
	i = -1;
	while (++i < data->number_of_philosophers)
		free(philo_ind[i]);
	free(philo_ind);
	return (0);
}
