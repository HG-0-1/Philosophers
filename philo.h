/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfayez <helfayez@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:11:17 by helfayez          #+#    #+#             */
/*   Updated: 2026/07/25 14:45:52 by helfayez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHOLOSOPHER_H
#define PHOLOSOPHER_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h> 

typedef struct s_data
{
  long start_time;
  int num_philo;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  pthread_mutex_t print_lock;
  pthread_mutex_t *forks;
}   t_data;

typedef struct s_philo
{
   int id;
   pthread_t thread;
   int last_meal;
   int meal_eaten;
   pthread_mutex_t *left_fork;
   pthread_mutex_t *right_fork;
   t_data *data;
    
}   t_philo;

void	take_forks(t_philo *philo);
int craete_fork(t_data *data);
void *routine(void *arg);
long get_time(void);
void print_status(t_philo *philo, char *status);

#endif 