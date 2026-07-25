/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfayez <helfayez@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 12:32:53 by helfayez          #+#    #+#             */
/*   Updated: 2026/07/25 14:43:51 by helfayez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
        print_status(philo, "took right fork");
		pthread_mutex_lock(philo->left_fork);
        print_status(philo, "took left fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
        print_status(philo, "took left fork");
		pthread_mutex_lock(philo->right_fork);
        print_status(philo, "took right fork");
	}
}
int craete_fork(t_data *data)
{
    int i;
    
    i = 0;
    data -> forks = malloc(sizeof(pthread_mutex_t) * data -> num_philo);
    if(!data -> forks)
        return (1);
    while(i < data -> num_philo)
    {
        pthread_mutex_init(&data -> forks[i], NULL);
        i++;
    }
    return 0;
}
int one_philo(t_philo *philo)
{
    if (philo ->data -> num_philo == 1)
    {
        pthread_mutex_lock(philo -> left_fork);
        printf("1 took a fork \n");
        usleep(philo -> data -> time_to_die * 1000);
        pthread_mutex_unlock(philo -> left_fork);
        return 1;
    }
    return 0;
}

void eat(t_philo *philo)
{
    print_status(philo, "is eating");
    philo -> last_meal = get_time();
    philo -> meal_eaten++;
    usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void *routine(void *arg)
{
    t_philo *philo;
    philo =arg;
    if(one_philo(philo))
        return (NULL);
    while(1)
    {
    print_status(philo, "is thinking");
    take_forks(philo);
    eat(philo);
    print_status(philo, "is sleeping");
    usleep(philo->data->time_to_sleep * 1000);
    }
    return (NULL);
}
