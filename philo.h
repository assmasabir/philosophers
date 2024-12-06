/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:54:08 by asabir            #+#    #+#             */
/*   Updated: 2024/12/06 22:50:23 by asabir           ###   ########.fr       */
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

typedef struct forks
{
	int				index;
	pthread_mutex_t	fork;
	struct forks	*next;
}					t_fork;

typedef struct Params
{
	int				nb_philos;
	double			time_to_die;
	double			time_to_eat;
	double			time_to_sleep;
	double			nb_must_eat;
	struct timeval	tv;
	pthread_mutex_t	display_message;
	t_fork			*forks;
	pthread_mutex_t	stop_simulation;
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
void				display_eating_messages(t_thread_list *node);
void				*case_one_thread(t_thread_list *node);
void				ft_putstr_fd(char *str, int fd);
double				ft_atoi(char *str);
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
void				case_thinking(t_thread_list *node, long started_eating);
long				get_time(long difference);
int					check_if_died(t_thread_list *node, long started_eating);
int					ft_usleep(t_thread_list *node, long time_to_sleep,
						long started_eating);
#endif