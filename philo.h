/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfayez <helfayez@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:11:17 by helfayez          #+#    #+#             */
/*   Updated: 2026/07/28 13:18:00 by helfayez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_fork
{
	pthread_mutex_t		mutex;
	int					id;
}						t_fork;

typedef struct s_data
{
	int					dead;
	long				start_time;
	int					num_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	int					finished_count;
	pthread_mutex_t		print_lock;
	t_fork				*forks;
	pthread_mutex_t		forks_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		finished_lock;
	t_philo				*philo;
}						t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	long				last_meal;
	int					meal_eaten;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_mutex_t		meal_lock;
	t_data				*data;

}						t_philo;

int						take_forks(t_philo *philo);
void					fork_lock(t_fork *fork);
void					fork_unlock(t_fork *fork);
int						craete_fork(t_data *data);
void					*routine(void *arg);
long					get_time(void);
void					print_status(t_philo *philo, char *status);
int						check_death(t_philo *philo);
void					*monitor(void *arg);
int						get_dead(t_data *data);
void					smart_sleep(long time, t_philo *philo);
int						ft_atoi(const char *nptr);
void					eat(t_philo *philo);

#endif