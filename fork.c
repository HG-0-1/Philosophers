/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfayez <helfayez@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 12:32:53 by helfayez          #+#    #+#             */
/*   Updated: 2026/07/28 13:07:14 by helfayez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_lock(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
}

void	fork_unlock(t_fork *fork)
{
	pthread_mutex_unlock(&fork->mutex);
}

int	take_forks(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;

	if (philo->id == philo->data->num_philo)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	else
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	if (get_dead(philo->data))
		return (1);
	pthread_mutex_lock(&philo->data->forks_lock);
	if (get_dead(philo->data))
	{
		pthread_mutex_unlock(&philo->data->forks_lock);
		return (1);
	}
	pthread_mutex_lock(&first->mutex);
	pthread_mutex_lock(&second->mutex);
	pthread_mutex_unlock(&philo->data->forks_lock);
	print_status(philo, "has taken a fork");
	print_status(philo, "has taken a fork");
	return (0);
}

int	craete_fork(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(t_fork) * data->num_philo);
	if (!data->forks)
		return (1);
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		i++;
	}
	return (0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_status(philo, "is eating");
	smart_sleep(philo->data->time_to_eat, philo);
	fork_unlock(philo->left_fork);
	fork_unlock(philo->right_fork);
}
