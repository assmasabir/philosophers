/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:00:24 by asabir            #+#    #+#             */
/*   Updated: 2024/12/06 22:40:37 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_execute(void *tmp)
{
	t_thread_list	*node;
	long			started_eating;
	int				count_meals;

	count_meals = 0;
	started_eating = get_time(0);
	node = (t_thread_list *)tmp;
	if (node->params->nb_must_eat == 0)
		return (NULL);
	if (node->params->nb_philos == 1)
		return (case_one_thread(node));
	if (node->index % 2)
		usleep(500);
	while (1)
	{
		if (case_eating(node, &started_eating, &count_meals) == 1)
			break ;
		if (case_sleeping(node, started_eating) == 1)
			break ;
		case_thinking(node, started_eating);
	}
	return (NULL);
}

int	join_threads(t_thread_list **head)
{
	t_thread_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (pthread_join(tmp->th, NULL) != 0)
		{
			ft_putstr_fd("failed thread_creation\n", 2);
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	create_threads(t_thread_list **head)
{
	t_thread_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (pthread_mutex_init(&(tmp->right_fork->fork), NULL) != 0
			|| pthread_mutex_init(&(tmp->left_fork->fork), NULL) != 0)
		{
			ft_putstr_fd("failed to initialize a mutex\n", 2);
			return (-1);
		}
		if (pthread_create(&(tmp->th), NULL, ft_execute, tmp) != 0)
		{
			ft_putstr_fd("failed thread_creation\n", 2);
			return (-1);
		}
		tmp = tmp->next;
	}
	return (join_threads(head));
}

long	get_time(long difference)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - difference);
}

int	check_if_died(t_thread_list *node, long started_eating)
{
	if (node->params->check_if_someone_died == 1)
	{
		return (1);
	}
	if (get_time(started_eating) > node->params->time_to_die)
	{
		usleep(100);
		pthread_mutex_lock(&node->params->display_message);
		if (node->params->check_if_someone_died == 1)
		{
			pthread_mutex_unlock(&node->params->display_message);
			return (1);
		}
		node->params->check_if_someone_died = 1;
		printf("%ld philosopher %d died\n", get_time(node->params->tv.tv_sec
				* 1000 + node->params->tv.tv_usec / 1000), node->index);
		pthread_mutex_unlock(&node->params->display_message);
		return (1);
	}
	return (0);
}
