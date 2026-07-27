/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfayez <helfayez@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 12:32:53 by helfayez          #+#    #+#             */
/*   Updated: 2026/07/27 03:33:56 by helfayez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_lock(t_fork *fork)
{
    int	ticket;
    int	serving;

    pthread_mutex_lock(&fork->guard);
    ticket = fork->next_ticket++;
    pthread_mutex_unlock(&fork->guard);
    while (1)
    {
        pthread_mutex_lock(&fork->guard);
        serving = fork->now_serving;
        pthread_mutex_unlock(&fork->guard);
        if (serving == ticket)
            break ;
        usleep(200);
    }
    pthread_mutex_lock(&fork->held);
}

void	fork_unlock(t_fork *fork)
{
    pthread_mutex_unlock(&fork->held);
    pthread_mutex_lock(&fork->guard);
    fork->now_serving++;
    pthread_mutex_unlock(&fork->guard);
}

void take_forks(t_philo *philo)
{
    if (philo->id == philo->data->num_philo)
    {
        fork_lock(philo->right_fork);
        print_status(philo, "has taken a fork");
        fork_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
    }
    else
    {
        fork_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
        fork_lock(philo->right_fork);
        print_status(philo, "has taken a fork");
    }
}

int craete_fork(t_data *data)
{
    int i;

    i = 0;
    data -> forks = malloc(sizeof(t_fork) * data -> num_philo);
    if(!data -> forks)
        return (1);
    while(i < data -> num_philo)
    {
        pthread_mutex_init(&data -> forks[i].held, NULL);
        pthread_mutex_init(&data -> forks[i].guard, NULL);
        data -> forks[i].next_ticket = 0;
        data -> forks[i].now_serving = 0;
        i++;
    }
    return 0;
}
int one_philo(t_philo *philo)
{
    if (philo ->data -> num_philo == 1)
    {
        fork_lock(philo -> left_fork);
        print_status(philo, "has taken a fork");
        usleep(philo -> data -> time_to_die * 1000);
        fork_unlock(philo -> left_fork);
        return 1;
    }
    return 0;
}

void eat(t_philo *philo)
{
    long new_time;

    pthread_mutex_lock(&philo->meal_lock);
    philo -> last_meal = get_time();
    philo -> meal_eaten++;
    pthread_mutex_unlock(&philo->meal_lock);
    print_status(philo, "is eating");
    new_time = get_time();

    while(get_time() - new_time < (philo->data->time_to_eat)  && !philo ->data ->dead)
        usleep(100);
    
    fork_unlock(philo->left_fork);
	fork_unlock(philo->right_fork);
}

void *routine(void *arg)
{
    t_philo *philo;
    long new_time;

    philo =arg;
    if(one_philo(philo))
        return (NULL);
    while(!get_dead(philo -> data))
    {
        print_status(philo, "is thinking");
        take_forks(philo);
        eat(philo);
        print_status(philo, "is sleeping");
        new_time = get_time();

        while(get_time() - new_time < (philo->data->time_to_sleep)  && !philo ->data ->dead)
            usleep(100);
    }
    return (NULL);
}
