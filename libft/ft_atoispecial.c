/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoispecial.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:22:53 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/01/10 17:29:32 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_special(const char *str)
{
	int				i[2];
	unsigned long	nb;

	i[0] = 0;
	i[1] = 0;
	nb = 0;
	while (str[i[0]] == ' ' || str[i[0]] == '\n' || str[i[0]] == '\t' \
			|| str[i[0]] == '\f' || str[i[0]] == '\v' || str[i[0]] == '\r')
		i[0]++;
	if (str[i[0]] == '+' || str[i[0]] == '-')
		if (str[i[0]++] == '-')
			i[1] = 1;
	while (str[i[0]] >= '0' && str[i[0]] <= '9')
		nb = (nb * 10) + (str[i[0]++] - '0');
	if ((nb > 2147483647 && i[1] == 0) || (nb > 2147483648 && i[1] == 1))
	{
		write(1, "Error\n", 6);
		exit (0);
	}
	else if (i[1] != 0)
		return ((int)nb * -1);
	return ((int) nb);
}