/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:22:42 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/25 21:30:41 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	int initial_time_ms;
}	t_data;

typedef struct s_philo_ind
{
	t_data	*data;
	int		ind;
}	t_philo_ind;

int	check_input_and_initialize(int argc, char *argv[], int *parameters);
int	ft_atoi(const char *nptr);
int	ft_isdigit(int c);
int	ft_strlen(char *str);

t_data	*initialize_data(int *parameters);
void	free_data(t_data *data);
int	initialize_simulation(t_data *data);
t_philo_ind	**initialize_philo_ind(t_data *data);
int	get_time_stamp(t_data *data);

#endif
