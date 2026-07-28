/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfayez <helfayez@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:11:15 by helfayez          #+#    #+#             */
/*   Updated: 2026/07/27 23:46:12 by helfayez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void print_status(t_philo *philo, char *status)
{
    pthread_mutex_lock(&philo->data->print_lock);
    if (!get_dead(philo -> data))
        printf("%ld %d %s\n", get_time() - philo-> data -> start_time, philo->id, status);
    pthread_mutex_unlock(&philo->data->print_lock);
}
int check_death(t_philo *philo)
{
    long current;
    long last;

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
        printf("%ld %d died\n",
            current - philo->data->start_time,
            philo->id);
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

void *monitor(void *arg)
{
    t_data *data = arg;
    int i;

    while (!get_dead(data))
    {
        if (all_ate_enough(data))
        {
            pthread_mutex_lock(&data->dead_lock);
            data->dead = 1;
            pthread_mutex_unlock(&data->dead_lock);
            return NULL;
        }

        i = 0;
        while (i < data->num_philo)
        {
            if (check_death(&data->philo[i]))
                return NULL;
            i++;
        }

        usleep(1000);
    }
    return NULL;
}

int get_dead(t_data *data)
{
    int dead;
    pthread_mutex_lock(&data->dead_lock);
    dead = data->dead;
    pthread_mutex_unlock(&data->dead_lock);
    return dead;
}
int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}
void smart_sleep(long time, t_philo *philo)
{
    long start;
    long remaining;

    start = get_time();
    while (!get_dead(philo->data))
    {
        remaining = time - (get_time() - start);
        if (remaining <= 0)
            break;
        if (remaining > 5)
            usleep(1000);
        else
            usleep(remaining * 1000 / 2 + 100);
    }
}