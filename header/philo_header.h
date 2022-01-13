/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:30:15 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/01/13 13:40:00 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HEADER_H
# define PHILO_HEADER_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct t_mutex
{
	int philo_num;
	pthread_mutex_t	*forks;
	pthread_t *threads;
	pthread_mutex_t wait;
	int running;
	struct timeval reftime;
	unsigned long deathtime;
	unsigned long firsttime;
	unsigned long timetosleep;
	unsigned long timetoeat;
}gen;

typedef struct t_philo
{
	pthread_t thread;
	int deathstatus;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	unsigned long lasttime;
	unsigned long phdeath;
	int index;
	gen *lst;
}philo;

unsigned long	timestamp(philo *ph);
void	getupdatetime(philo *ph);
unsigned long	checktime(philo *ph);
void	myusleep(unsigned long microsec, philo *ph);


#endif