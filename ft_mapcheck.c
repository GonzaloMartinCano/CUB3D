/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapCheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 20:05:20 by gmartin-          #+#    #+#             */
/*   Updated: 2020/07/09 13:50:07 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		map_check(int row, int col, t_file *f)
{
	int ok;

	if (row < 0 || col < 0 || row >= f->nFil
		|| col >= f->nColMax || f->map[row][col] == 4)
		return (-1);
	else if (f->map[row][col] == 3 || f->map[row][col] == 1)
		return (0);
	if (f->map[row][col] == 2)
		f->map[row][col] = 2;
	else
		f->map[row][col] = 3;
	ok = map_check(row, col - 1, f);
	ok = ok == 0 ? map_check(row, col + 1, f) : ok;
	ok = ok == 0 ? map_check(row - 1, col, f) : ok;
	ok = ok == 0 ? map_check(row + 1, col, f) : ok;
	return (ok);
}
