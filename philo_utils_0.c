/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:54:05 by asabir            #+#    #+#             */
/*   Updated: 2024/12/06 22:50:04 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

void	add_thread(t_thread_list **head, t_thread_list *new, int index,
		t_params *params)
{
	t_thread_list	*tmp;

	tmp = *head;
	if (!head)
		return ;
	new->next = NULL;
	new->index = index;
	new->params = params;
	if (*head == NULL)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	add_fork(t_fork **head, t_fork *new, int index)
{
	t_fork	*tmp;

	new->next = NULL;
	new->index = index;
	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	display_eating_messages(t_thread_list *node)
{
	pthread_mutex_lock(&node->params->display_message);
	printf("%ld %d has taken the right fork\n", get_time(node->params->tv.tv_sec
			* 1000 + node->params->tv.tv_usec / 1000), node->index);
	printf("%ld %d has taken the left fork\n", get_time(node->params->tv.tv_sec
			* 1000 + node->params->tv.tv_usec / 1000), node->index);
	printf("%ld %d is eating\n", get_time(node->params->tv.tv_sec * 1000
			+ node->params->tv.tv_usec / 1000), node->index);
	pthread_mutex_unlock(&node->params->display_message);
}
