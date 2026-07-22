/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfayez <helfayez@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:11:13 by helfayez          #+#    #+#             */
/*   Updated: 2026/07/22 16:27:06 by helfayez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHOLOSOPHER_H
#define PHOLOSOPHER_H

#include <stdio.h>
#include <pthread.h>

typedef struct s_philo
{
   int thinking;
   int hungry;
   int eating;
   int number_of_philo;
    
}   t_philo;

#endif 

//pthread lib
/* pthread_create      
pthread_create(&th1 a pass a pointer to pthread, NULL  the aittrubte of the thread,c the function ,NULL to pass arg to the function);

*/
void *c(void *add)
{
    long sum = 0;
    long *add_num = (long *) (add);
    printf("the num : %ld \n", *add_num);
    return NULL;
}
int main()
{
    pthread_t th1;
    pthread_t th2;
    long val = 4;
    long val1 = 6;
    pthread_create(&th1, NULL,c,(void *) &val);
    pthread_create(&th2, NULL,c,(void *) &val1);
    
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);    
    return 0;
}