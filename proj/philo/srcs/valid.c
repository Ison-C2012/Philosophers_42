/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:02:51 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/25 20:14:34 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define INT_MAX_STR "2147483647"

static bool	is_positive_number(char *str)
{
	if (*str == '+')
		str++;
	if (*str == '0')
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

bool	is_positive_numbers(char **av)
{
	while (*av)
	{
		if (!is_positive_number(*av))
			return (false);
		av++;
	}
	return (true);
}

static size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

bool	is_overflow(char **av)
{
	char	*str;

	while (*av)
	{
		str = *av;
		if (*str == '+')
			str++;
		if (ft_strlen(str) > ft_strlen(INT_MAX_STR))
			return (true);
		if (ft_strlen(str) == ft_strlen(INT_MAX_STR))
			if (ft_strcmp(str, INT_MAX_STR) > 0)
				return (true);
		av++;
	}
	return (false);
}
