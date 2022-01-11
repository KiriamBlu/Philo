/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:30:15 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/01/11 15:45:00 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HEADER_H
# define PHILO_HEADER_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
#include <sys/time.h>

typedef struct t_mutex
{
	int philo_num;
	pthread_mutex_t	*forks;
	struct timeval reftime;
	unsigned long time;
}gen;

typedef struct t_philo
{
	pthread_t thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	unsigned long lasttime;
	int index;
	gen lst;
}philo;


#endif