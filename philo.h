/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfayez <helfayez@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:11:17 by helfayez          #+#    #+#             */
/*   Updated: 2026/07/27 03:15:35 by helfayez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHOLOSOPHER_H
#define PHOLOSOPHER_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h> 

typedef struct s_philo t_philo;

typedef struct s_fork
{
  pthread_mutex_t held;
  pthread_mutex_t guard;
  int next_ticket;
  int now_serving;
}   t_fork;

typedef struct s_data
{
  int dead;
  long start_time;
  int num_philo;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int must_eat;
  pthread_mutex_t print_lock;
  t_fork *forks;
  pthread_mutex_t dead_lock;
  t_philo *philo;
}   t_data;

typedef struct s_philo
{
   int id;
   pthread_t thread;
   long last_meal;
   int meal_eaten;
   t_fork *left_fork;
   t_fork *right_fork;
   pthread_mutex_t meal_lock;
   t_data *data;

}   t_philo;

void	take_forks(t_philo *philo);
void	fork_lock(t_fork *fork);
void	fork_unlock(t_fork *fork);
int craete_fork(t_data *data);
void *routine(void *arg);
long get_time(void);
void print_status(t_philo *philo, char *status);
int check_death(t_philo *philo);
void *monitor(void *arg);
int get_dead(t_data *data);
int	ft_atoi(const char *nptr);

#endif 