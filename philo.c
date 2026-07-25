/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfayez <helfayez@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:11:13 by helfayez          #+#    #+#             */
/*   Updated: 2026/07/25 14:46:27 by helfayez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int creat_philosopher(t_philo *philo, t_data *data)
{
    int i;

    i = 0;
    while (i < data -> num_philo)
    {
        philo[i].id = i + 1;
        philo[i].data = data;
        philo[i].left_fork = &data -> forks[i];
        philo[i].right_fork = &data -> forks[(i + 1) % data -> num_philo];
        if(pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
            return 1;
        i++;
    }
    return 0;
}

int join_philo (t_philo *philo, t_data *data)
{
    int i;

    i = 0;
    while (i < data -> num_philo)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
    return (0);
}

int	main(void)
{
	t_data	data;
	t_philo	*philos;

    data.start_time = get_time();
    data.num_philo = 10;
    if (craete_fork(&data))
        return 1;
    philos = malloc(sizeof(t_philo) * data.num_philo);
	if(!philos)
        return 1;
	if (creat_philosopher(philos, &data))
		return (1);

	join_philo(philos, &data);
    free(philos);
	return (0);
}
