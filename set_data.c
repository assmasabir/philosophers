/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:46:12 by asabir            #+#    #+#             */
/*   Updated: 2024/12/16 15:02:10 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*get_fork(t_fork *head, int index)
{
	t_fork	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->index == index)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	create_forks(t_fork **head, t_params *params)
{
	t_fork	*fork;
	int		i;

	i = 0;
	*head = NULL;
	while (i < params->nb_philos)
	{
		fork = malloc(sizeof(t_fork));
		if (fork == NULL)
		{
			ft_putstr_fd("can't allocate memory!!\n", 2);
			return (-1);
		}
		add_fork(head, fork, i + 1);
		i++;
	}
	params->forks = *head;
	return (0);
}

int	prepare_structure(t_thread_list **head, t_params *params)
{
	int				i;
	t_thread_list	*node;

	i = 0;
	*head = NULL;
	while (i < params->nb_philos)
	{
		node = malloc(sizeof(t_thread_list));
		if (node == NULL)
		{
			ft_putstr_fd("can't allocate memory\n", 2);
			return (-1);
		}
		add_thread(head, node, i + 1, params);
		i++;
	}
	return (0);
}

int	distribute_forks(t_thread_list **head, t_params *params)
{
	t_fork			*head_forks;
	t_thread_list	*tmp;
	int				i;

	i = 1;
	if (create_forks(&head_forks, params) == -1)
		return (-1);
	tmp = *head;
	while (tmp)
	{
		if (i == 1)
			tmp->right_fork = get_fork(head_forks, params->nb_philos);
		else
			tmp->right_fork = get_fork(head_forks, i - 1);
		tmp->left_fork = get_fork(head_forks, i);
		i++;
		tmp = tmp->next;
	}
	return (0);
}

int	prepare_data(int argc, char **argv, t_params *param, t_thread_list **head)
{
	param->check_if_someone_died = 0;
	param->nb_philos = ft_atoi(argv[1]);
	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		param->nb_must_eat = ft_atoi(argv[5]);
	else
		param->nb_must_eat = -1;
	if (param->nb_philos > INT_MAX || param->time_to_die > INT_MAX
		|| param->time_to_eat > INT_MAX || param->time_to_sleep > INT_MAX
		|| param->nb_must_eat > INT_MAX)
	{
		ft_putstr_fd("Incorrect input\n", 2);
		free(param);
		return (-1);
	}
	if (prepare_structure(head, param) == -1)
		return (-1);
	if (distribute_forks(head, param) == -1)
		return (-1);
	return (0);
}
