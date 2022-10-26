/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_and_initialize.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:38:57 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/25 14:59:11 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_numeric(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	return (i == ft_strlen(arg));
}

int	check_input_and_initialize(int argc, char *argv[], int *parameters)
{
	int				i;

	if ((argc != 5) && (argc != 6))
	{
		printf("You should input 4 or 5 arguments!\n");
		return (1);
	}
	i = 0;
	while (++i < argc)
	{
		if (is_numeric(argv[i]))
			parameters[i - 1] = ft_atoi(argv[i]);
		else
			{
				printf("All arguments must be numeric!\n");
				return (2);
			}
	}
	if (i == 5)
		parameters[4] = 0;
	return (0);
}