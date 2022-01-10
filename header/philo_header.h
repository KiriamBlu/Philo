/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:30:15 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/01/10 17:29:35 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HEADER_H
# define PHILO_HEADER_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

typedef struct t_mutex
{
	pthread_t *thread;
	pthread_mutex_t mutex;
	int philo_num;
	int i;
}gen;

typedef struct t_philo
{
	int index;
	gen lst;
}philo;


#endif