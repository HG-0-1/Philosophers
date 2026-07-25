/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfayez <helfayez@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:11:15 by helfayez          #+#    #+#             */
/*   Updated: 2026/07/25 14:47:22 by helfayez         ###   ########.fr       */
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
    printf("%ld %d %s\n", get_time() - philo-> data -> start_time, philo->id, status);
    pthread_mutex_unlock(&philo->data->print_lock);
}
