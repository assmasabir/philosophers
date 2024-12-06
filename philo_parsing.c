/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:54:54 by asabir            #+#    #+#             */
/*   Updated: 2024/12/06 21:14:18 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_all(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("unsatisfied number of arguments\n", 2);
		return (-1);
	}
	else if (parse_numbers(argv) == -1)
	{
		ft_putstr_fd("Type only positive numbers please\n", 2);
		return (-1);
	}
	else if (ft_atoi(argv[1]) == 0)
	{
		ft_putstr_fd("0 is not a valid number of philosophers\n", 2);
		return (-1);
	}
	return (0);
}

int	parse_numbers(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (j == 0 && argv[i][j] == '+')
				j++;
			if (argv[i][j] && (argv[i][j] < '0' || argv[i][j] > '9'))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

double	ft_atoi(char *str)
{
	double	res;
	int		i;

	res = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		res = res * 10;
		res += (str[i] - '0');
		i++;
	}
	return (res);
}
