/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:54:01 by asabir            #+#    #+#             */
/*   Updated: 2024/12/07 19:38:45 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_params		*param;
	t_thread_list	*thread_structure;

	param = malloc(sizeof(t_params));
	if (param == NULL)
	{
		ft_putstr_fd("can't allocate memory, by ^^\n", 2);
		return (1);
	}
	if (parse_all(argc, argv) == -1)
		return (free(param), 1);
	else
	{
		if (prepare_data(argc, argv, param, &thread_structure) == -1)
			return (1);
		gettimeofday(&(param->tv), NULL);
		if (create_threads(&thread_structure) == -1)
		{
			free_all(&thread_structure, param);
			return (1);
		}
	}
	free_all(&thread_structure, param);
}

void	free_all(t_thread_list **head, t_params *par)
{
	t_thread_list	*thread;
	t_fork			*tmp;

	(void)head;
	thread = *head;
	while (par->forks)
	{
		pthread_mutex_destroy(&(par->forks->fork));
		tmp = par->forks->next;
		free(par->forks);
		par->forks = tmp;
	}
	pthread_mutex_destroy(&par->display_message);
	free(par);
	while (*head)
	{
		thread = *head;
		*head = (*head)->next;
		free(thread);
	}
}
