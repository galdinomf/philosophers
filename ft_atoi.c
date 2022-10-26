/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:43:11 by mgaldino          #+#    #+#             */
/*   Updated: 2022/04/21 15:46:27 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(int c);

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	signal;

	i = 0;
	while ((nptr[i] == 32) || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	signal = 1;
	if (nptr[i] == '-')
	{
		signal = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	if (!ft_isdigit(nptr[i]))
		return (0);
	result = nptr[i] - '0';
	while (ft_isdigit(nptr[i + 1]))
	{
		result = result * 10 + (nptr[i + 1] - '0');
		i++;
	}
	result *= signal;
	return (result);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	else
		return (0);
}
