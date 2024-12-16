/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:54:08 by asabir            #+#    #+#             */
/*   Updated: 2024/12/16 15:02:35 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct forks
{
	int				index;
	pthread_mutex_t	fork;
	struct forks	*next;
}					t_fork;

typedef struct Params
{
	long			nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_must_eat;
	struct timeval	tv;
	pthread_mutex_t	display_message;
	t_fork			*forks;
	int				check_if_someone_died;
}					t_params;

typedef struct Pthread
{
	pthread_t		th;
	int				index;
	t_fork			*right_fork;
	t_fork			*left_fork;
	t_params		*params;
	struct Pthread	*next;
}					t_thread_list;

int					parse_numbers(char **argv);
long				get_time(long difference);
void				display_eating_messages(t_thread_list *node);
void				*case_one_thread(t_thread_list *node);
void				ft_putstr_fd(char *str, int fd);
long				ft_atoi(char *str);
int					parse_all(int argc, char **argv);
int					prepare_structure(t_thread_list **head, t_params *params);
int					prepare_data(int argc, char **argv, t_params *param,
						t_thread_list **thread_struct);
void				add_thread(t_thread_list **head, t_thread_list *new,
						int index, t_params *params);
void				add_fork(t_fork **head, t_fork *new, int index);
int					create_threads(t_thread_list **list);
int					ft_usleep(t_thread_list *node, long time_to_sleep,
						long started_eating);
int					case_eating(t_thread_list *node, long *started_eating,
						int *count_meals);
int					case_sleeping(t_thread_list *node, long started_eating);
int					case_thinking(t_thread_list *node);
long				get_time(long difference);
int					check_if_died(t_thread_list *node, long started_eating);
int					ft_usleep(t_thread_list *node, long time_to_sleep,
						long started_eating);
void				free_all(t_thread_list **head, t_params *par);
#endif
