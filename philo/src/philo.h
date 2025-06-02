/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:46:10 by apatvaka          #+#    #+#             */
/*   Updated: 2025/06/02 13:18:31 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	t_table				*table;
	long				last_meal_time;
	int					meal_count;
	pthread_mutex_t		meal_mutex;
}						t_philo;

typedef struct s_table
{
	int					num_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					optional_eat;

	int					sim_stop;
	pthread_mutex_t		sim_stop_mutex;

	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	long				start_time;
	int					i;
}						t_table;

// validate
int						is_validate(int argc, char **argv, t_table *table);
int						ft_atoi(const char *str);
int						ft_strcmp(char *s1, char *s2);
int						ft_strlen(char *str);
int						ft_isdigit(int c);
int						print_error(char *str, int exit_code);

// free
void					free_table(t_table *table);
void					free_mutex_forks(t_table *table, int len);
void					free_mutex_meal(t_table *table, int len);

// hellper
int						init_philos_hellper(t_table *table);
#endif
