/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:22:42 by mgaldino          #+#    #+#             */
/*   Updated: 2022/11/08 11:49:54 by mgaldino         ###   ########.fr       */
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
	pthread_t	*philos;
	pthread_t	killer;
	pthread_mutex_t	mutex;
	pthread_mutex_t	counter_mutex;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	*eat_time_mutex;
	pthread_mutex_t	*eat_counter_mutex;
	int			*forks;
	int			*fork_used;
	int			*counter;
	int			*eat_time;
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
	int			initial_time_ms;
	int			end_simulation;
	int			can_show_messages;
}	t_data;

typedef struct s_philo_ind
{
	t_data	*data;
	int		ind;
}	t_philo_ind;

int	ft_atoi(const char *nptr);
int	ft_isdigit(int c);
int	ft_strlen(char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nmemb, size_t size);

int	check_input_and_initialize(int argc, char *argv[], int *parameters);
t_data	*initialize_data(int *parameters);
void	free_data(t_data *data);
int	initialize_simulation(t_data *data);
t_philo_ind	**initialize_philo_ind(t_data *data);
int	get_timestamp(t_data *data);
int	try_to_eat(t_philo_ind *philo_ind);
void	display_message(char *msg, t_philo_ind *philo_ind);
#endif
