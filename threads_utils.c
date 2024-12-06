/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:26:36 by asabir            #+#    #+#             */
/*   Updated: 2024/12/06 22:49:57 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*case_one_thread(t_thread_list *node)
{
	pthread_mutex_lock(&node->params->display_message);
	printf("%ld %d has taken the right fork\n", get_time(node->params->tv.tv_sec
			* 1000 + node->params->tv.tv_usec / 1000), node->index);
	pthread_mutex_unlock(&node->params->display_message);
	usleep(node->params->time_to_die * 1000);
	pthread_mutex_lock(&node->params->display_message);
	printf("%ld philosopher %d died\n", get_time(node->params->tv.tv_sec * 1000
			+ node->params->tv.tv_usec / 1000), node->index);
	pthread_mutex_unlock(&node->params->display_message);
	return (NULL);
}

int	ft_usleep(t_thread_list *node, long time_to_sleep, long started_eating)
{
	long	time_at_start;
	int		check;

	time_at_start = get_time(0);
	check = 0;
	while ((get_time(0) - time_at_start) < time_to_sleep)
	{
		if (check_if_died(node, started_eating) == 1)
		{
			check = 1;
			break ;
		}
		usleep(2);
	}
	if (check == 1)
		return (1);
	return (0);
}

int	case_eating(t_thread_list *node, long *started_eating, int *count_meals)
{
	pthread_mutex_lock(&(node->right_fork->fork));
	pthread_mutex_lock(&(node->left_fork->fork));
	if (check_if_died(node, *started_eating) == 1
		|| (node->params->nb_must_eat != -1
			&& *count_meals == node->params->nb_must_eat))
	{
		pthread_mutex_unlock(&(node->left_fork->fork));
		pthread_mutex_unlock(&(node->right_fork->fork));
		return (1);
	}
	display_eating_messages(node);
	*started_eating = get_time(0);
	if (ft_usleep(node, node->params->time_to_eat, *started_eating) == 1)
	{
		pthread_mutex_unlock(&(node->left_fork->fork));
		pthread_mutex_unlock(&(node->right_fork->fork));
		return (1);
	}
	pthread_mutex_unlock(&(node->right_fork->fork));
	pthread_mutex_unlock(&(node->left_fork->fork));
	count_meals++;
	return (0);
}

int	case_sleeping(t_thread_list *node, long started_eating)
{
	pthread_mutex_lock(&node->params->display_message);
	printf("%ld %d is sleeping\n", get_time(node->params->tv.tv_sec * 1000
			+ node->params->tv.tv_usec / 1000), node->index);
	pthread_mutex_unlock(&node->params->display_message);
	return (ft_usleep(node, node->params->time_to_sleep, started_eating));
}

void	case_thinking(t_thread_list *node, long started_eating)
{
	if (check_if_died(node, started_eating) != 1)
	{
		pthread_mutex_lock(&node->params->display_message);
		printf("%ld %d is thinking\n", get_time(node->params->tv.tv_sec * 1000
				+ node->params->tv.tv_usec / 1000), node->index);
		pthread_mutex_unlock(&node->params->display_message);
	}
}
