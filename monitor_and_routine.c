/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_and_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfayez <helfayez@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 12:06:45 by helfayez          #+#    #+#             */
/*   Updated: 2026/07/28 12:11:09 by helfayez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_philo *philo)
{
	if (philo->data->num_philo == 1)
	{
		fork_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000);
		fork_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

int	check_death(t_philo *philo)
{
	long	current;
	long	last;

	current = get_time();
	pthread_mutex_lock(&philo->meal_lock);
	last = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_lock);
	if (current - last > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->dead_lock);
			return (1);
		}
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%ld %d died\n", current - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
		return (1);
	}
	return (0);
}

static int	all_ate_enough(t_data *data)
{
	int	i;
	int	eaten;

	if (data->must_eat <= 0)
		return (0);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&data->philo[i].meal_lock);
		eaten = data->philo[i].meal_eaten;
		pthread_mutex_unlock(&data->philo[i].meal_lock);
		if (eaten < data->must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = arg;
	while (!get_dead(data))
	{
		if (all_ate_enough(data))
		{
			pthread_mutex_lock(&data->dead_lock);
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (NULL);
		}
		i = 0;
		while (i < data->num_philo)
		{
			if (check_death(&data->philo[i]))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_lock);
	if (one_philo(philo))
		return (NULL);
	usleep((philo->id % 20) * 300);
	while (!get_dead(philo->data))
	{
		print_status(philo, "is thinking");
		take_forks(philo);
		eat(philo);
		print_status(philo, "is sleeping");
		smart_sleep(philo->data->time_to_sleep, philo);
	}
	return (NULL);
}
