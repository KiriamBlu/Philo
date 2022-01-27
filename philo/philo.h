/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:31:20 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/01/26 18:24:26 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

# define COLOR_RED     "\x1b[31m"
# define COLOR_GREEN   "\x1b[32m"
# define COLOR_YELLOW  "\x1b[33m"
# define COLOR_BLUE    "\x1b[34m"
# define COLOR_MAGENTA "\x1b[35m"
# define COLOR_CYAN    "\x1b[36m"
# define COLOR_RESET   "\x1b[0m"

typedef struct s_gen
{
	int				philo_num;
	int				i;
	pthread_mutex_t	*mutex_forks;
	int				*forks;
	pthread_t		*threads;
	pthread_mutex_t	wait;
	int				running;
	unsigned long	eattime;
	struct timeval	reftime;
	unsigned long	deathtime;
	unsigned long	firsttime;
	unsigned long	timetosleep;
	unsigned long	timetoeat;
}	t_gen;

typedef struct s_philo
{
	int				food;
	pthread_t		thread;
	int				count;
	int				deathstatus;
	pthread_mutex_t	*mutex_left;
	pthread_mutex_t	*mutex_right;
	int				fork_left;
	int				fork_right;
	int				eats;
	unsigned long	lasttime;
	unsigned long	phdeath;
	int				index;
	t_gen			*lst;
}	t_philo;

unsigned long	timestamp(t_philo *philo);
void			getupdatetime(t_philo *philo);
unsigned long	checktime(t_philo *philo);
void			myusleep(unsigned long microsec, t_philo *philo);
unsigned long	ft_atoi_special_l(const char *str);
int				ft_atoi_special(const char *str);
t_gen			structinit(char **argv, int argc);
void			sleeping(t_philo *philo);
void			pickfork(t_philo *philo);
void			pressftotalk(t_philo *philo, int i);
void			ft_finthread(t_gen *gen);
int				ft_errors(int argc, char **argv);
void			phinit(t_philo *philo, t_gen *gen);

#endif