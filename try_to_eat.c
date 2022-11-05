/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_to_eat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:38:51 by mgaldino          #+#    #+#             */
/*   Updated: 2022/11/05 12:48:53 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_fork_mutexes(int ind, int left_ind, t_data *data)
{
	if (ind > left_ind)
	{
		pthread_mutex_lock(&data->forks_mutex[ind]);
		pthread_mutex_lock(&data->forks_mutex[left_ind]);
	}
	else
	{
		if (left_ind != ind)
			pthread_mutex_lock(&data->forks_mutex[left_ind]);
		pthread_mutex_lock(&data->forks_mutex[ind]);
	}
}

void	unlock_fork_mutexes(int ind, int left_ind, t_data *data)
{
	if (ind > left_ind)
	{
		pthread_mutex_unlock(&data->forks_mutex[ind]);
		pthread_mutex_unlock(&data->forks_mutex[left_ind]);
	}
	else
	{
		if (left_ind != ind)
			pthread_mutex_unlock(&data->forks_mutex[left_ind]);
		pthread_mutex_unlock(&data->forks_mutex[ind]);
	}
}

int	take_fork(t_philo_ind *philo_ind, int fork_ind)
{
//	int *forks;
	int	result;
	t_data	*data;

	result = 0;
	data = philo_ind->data;
//	forks = philo_ind->data->forks;
	pthread_mutex_lock(&data->forks_mutex[fork_ind]);
	if ((data->forks[fork_ind] == 0) || (data->forks[fork_ind] == philo_ind->ind + 1))
	{	
		//forks[fork_ind] = philo_ind->ind + 1;
		display_message("has taken a fork", philo_ind);
		result = 1;
	}
	pthread_mutex_unlock(&data->forks_mutex[fork_ind]);
	return (result);
}

void	lay_fork_down(t_philo_ind *philo_ind, int fork_ind, int next_ind)
{
	int *forks;
	t_data	*data;

	data = philo_ind->data;
	forks = philo_ind->data->forks;
	pthread_mutex_lock(&data->forks_mutex[fork_ind]);
	if (forks[fork_ind] == philo_ind->ind + 1)
		forks[fork_ind] = next_ind;
	pthread_mutex_unlock(&data->forks_mutex[fork_ind]);
}

void	eat(t_philo_ind *philo_ind)
{
	t_data	*data;
	int		ind;
//	int		timestamp;

	data = philo_ind->data;
	ind = philo_ind->ind;
//	timestamp = get_timestamp(data);
	//printf("%d %d is eating\n", timestamp, ind + 1);
	pthread_mutex_lock(&data->eat_time_mutex[ind]);	
	data->eat_time[ind] = get_timestamp(data);
	pthread_mutex_unlock(&data->eat_time_mutex[ind]);
	display_message("is eating", philo_ind);
	usleep(data->time_to_eat * 1000);
}

int	try_to_eat(t_philo_ind *philo_ind)
{
	t_data	*data;
	int		ind;
	int		left_ind;
	int		right_ind;
	int		has_not_eaten;

	data = philo_ind->data;
	ind = philo_ind->ind;
	has_not_eaten = 1;
	if (ind == 0)
		left_ind = data->number_of_philosophers - 1;
	else
		left_ind = ind - 1;
	if (ind == data->number_of_philosophers - 1)
		right_ind =  0;
	else
		right_ind = ind + 1;
	//printf("ind = %d, left_ind = %d\n", ind, left_ind);
	//lock_fork_mutexes(ind, left_ind, data);
	//printf("data->forks[%d] = %d\n", ind, data->forks[ind]);
	//printf("data->forks[%d] = %d\n", left_ind, data->forks[left_ind]);
	//pthread_mutex_lock(&data->forks_mutex[ind]);
	//if (ind != left_ind)
	//	pthread_mutex_lock(&data->forks_mutex[left_ind]);
	//printf("ind = %d, left_ind = %d\n", ind, left_ind);
	if ((take_fork(philo_ind, ind)) && (take_fork(philo_ind, left_ind)))
	{
	//	take_fork(philo_ind, ind);
	//	take_fork(philo_ind, left_ind);
	//	unlock_fork_mutexes(ind, left_ind, data);
		eat(philo_ind);
		has_not_eaten = 0;
	//	lock_fork_mutexes(ind, left_ind, data);
	}
		lay_fork_down(philo_ind, ind, right_ind + 1);
		lay_fork_down(philo_ind, left_ind, left_ind + 1);
	//unlock_fork_mutexes(ind, left_ind, data);
	/*
	pthread_mutex_unlock(&data->forks_mutex[ind]);
		if (ind != left_ind)
	pthread_mutex_unlock(&data->forks_mutex[left_ind]);
	*/
	return (has_not_eaten);
}