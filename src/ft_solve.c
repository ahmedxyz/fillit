/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumedi <ssumedi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 19:59:51 by ssumedi           #+#    #+#             */
/*   Updated: 2017/11/30 18:39:30 by ssumedi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fillit.h"

int		ft_is_available(char *str, int i, int *coords)
{
	if (str[i] == '.' && str[i + coords[0]] == '.' &&
			str[i + coords[1]] == '.' && str[i + coords[2]] == '.')
		return (1);
	return (0);
}

char	*ft_print(char *str, int i, int *coords, char c)
{
	str[i] = c;
	str[i + coords[0]] = c;
	str[i + coords[1]] = c;
	str[i + coords[2]] = c;
	return (str);
}

int		**ft_scale_up(int **tetro, int *n, int x)
{
	while (++x < n[1])
	{
		if (tetro[x][0] == (n[0] - 2) && tetro[x][1] == (n[0] - 1) &&
				tetro[x][2] == n[0])
		{
			tetro[x][0] += 1;
			tetro[x][1] += 1;
			tetro[x][2] += 1;
		}
		else if ((tetro[x][0] == (n[0] - 1) || tetro[x][1] == (n[0] - 1) ||
				tetro[x][2] == (n[0] - 1)) || (tetro[x][0] == n[0] &&
				tetro[x][1] == ((n[0] * 2) - 1) && tetro[x][2] == (n[0] * 2)))
		{
			tetro[x][0] += (tetro[x][0] / (n[0] - 1));
			tetro[x][1] += (tetro[x][1] / (n[0] - 1));
			tetro[x][2] += (tetro[x][2] / (n[0] - 1));
		}
		else
		{
			tetro[x][0] += (tetro[x][0] / n[0]);
			tetro[x][1] += (tetro[x][1] / n[0]);
			tetro[x][2] += (tetro[x][2] / n[0]);
		}
	}
	return (tetro);
}

int		**ft_scale_down(int **tetro, int size, int x, int count)
{
	while (++x < count)
	{
		if (tetro[x][0] == (size - 2) && tetro[x][1] == (size - 1) &&
				tetro[x][2] == size)
		{
			tetro[x][0] -= 1;
			tetro[x][1] -= 1;
			tetro[x][2] -= 1;
		}
		else if ((tetro[x][0] == (size - 1) || tetro[x][1] == (size - 1) ||
				tetro[x][2] == (size - 1)) || (tetro[x][0] == size &&
				tetro[x][1] == ((size * 2) - 1) && tetro[x][2] == (size * 2)))
		{
			tetro[x][0] -= (tetro[x][0] / (size - 1));
			tetro[x][1] -= (tetro[x][1] / (size - 1));
			tetro[x][2] -= (tetro[x][2] / (size - 1));
		}
		else
		{
			tetro[x][0] -= (tetro[x][0] / size);
			tetro[x][1] -= (tetro[x][1] / size);
			tetro[x][2] -= (tetro[x][2] / size);
		}
	}
	return (tetro);
}

int		ft_solve(int **tetro, int x, int *n, char *str)
{
	int		i;

	if (x == n[1] || !str[x])
	{
		ft_putstr(str);
		exit(1);
	}
	if ((n[0] == 3 && x == 0))
		tetro = ft_scale_down(tetro, 4, -1, n[1]);
	i = -1;
	while (str[++i])
	{
		if (ft_is_available(str, i, tetro[x]))
		{
			str = ft_print(str, i, tetro[x], 'A' + x);
			ft_solve(tetro, x + 1, n, str);
			str = ft_print(str, i, tetro[x], '.');
		}
	}
	if (x == 0)
	{
		n[0] += 1;
		return (ft_solve(ft_scale_up(tetro, n, -1), 0, n, ft_grid(n[0])));
	}
	return (0);
}
