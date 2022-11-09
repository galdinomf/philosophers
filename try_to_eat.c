/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_to_eat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:38:51 by mgaldino          #+#    #+#             */
/*   Updated: 2022/11/08 22:58:12 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo_ind *philo_ind, int fork_ind)
{
	int		result;
	t_data	*data;

	result = 0;
	data = philo_ind->data;
	pthread_mutex_lock(&data->forks_mutex[fork_ind]);
	if ((data->fork_used[fork_ind] == 0) && \
		((data->forks[fork_ind] == 0) || \
		(data->forks[fork_ind] == philo_ind->ind + 1)))
	{
		data->fork_used[fork_ind] = 1;
		pthread_mutex_unlock(&data->forks_mutex[fork_ind]);
		display_message("has taken a fork", philo_ind);
		result = 1;
	}
	else
		pthread_mutex_unlock(&data->forks_mutex[fork_ind]);
	return (result);
}

void	lay_fork_down(t_philo_ind *philo_ind, int fork_ind)
{
	t_data	*data;

	data = philo_ind->data;
	pthread_mutex_lock(&data->forks_mutex[fork_ind]);
	{
		data->fork_used[fork_ind] = 0;
	}
	pthread_mutex_unlock(&data->forks_mutex[fork_ind]);
}

void	eat(t_philo_ind *philo_ind)
{
	t_data	*data;
	int		ind;

	data = philo_ind->data;
	ind = philo_ind->ind;
	pthread_mutex_lock(&data->eat_time_mutex[ind]);
	data->eat_time[ind] = get_timestamp(data);
	display_message("is eating", philo_ind);
	pthread_mutex_unlock(&data->eat_time_mutex[ind]);
	usleep(data->time_to_eat * 1000);
}

void	set_variables(t_philo_ind *philo_ind, int *has_not_eaten, \
						int *left_ind, int *right_ind)
{
	*has_not_eaten = 1;
	if (philo_ind->ind == 0)
		*left_ind = philo_ind->data->number_of_philosophers - 1;
	else
		*left_ind = philo_ind->ind - 1;
	if (philo_ind->ind == philo_ind->data->number_of_philosophers - 1)
		*right_ind = 0;
	else
		*right_ind = philo_ind->ind + 1;
}

int	try_to_eat(t_philo_ind *philo_ind)
{
	int		left_ind;
	int		right_ind;
	int		has_not_eaten;
	int		right_fork_taken;
	int		left_fork_taken;

	set_variables(philo_ind, &has_not_eaten, &left_ind, &right_ind);
	right_fork_taken = take_fork(philo_ind, philo_ind->ind);
	left_fork_taken = take_fork(philo_ind, left_ind);
	if ((right_fork_taken) && (left_fork_taken))
	{
		eat(philo_ind);
		has_not_eaten = 0;
		pthread_mutex_lock(&philo_ind->data->forks_mutex[left_ind]);
		philo_ind->data->forks[left_ind] = left_ind + 1;
		pthread_mutex_unlock(&philo_ind->data->forks_mutex[left_ind]);
		pthread_mutex_lock(&philo_ind->data->forks_mutex[philo_ind->ind]);
		philo_ind->data->forks[philo_ind->ind] = right_ind + 1;
		pthread_mutex_unlock(&philo_ind->data->forks_mutex[philo_ind->ind]);
	}
	if (right_fork_taken)
		lay_fork_down(philo_ind, philo_ind->ind);
	if (left_fork_taken)
		lay_fork_down(philo_ind, left_ind);
	return (has_not_eaten);
}
