/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecube.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:21:10 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/29 03:38:50 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSECUBE_H
# define PARSECUBE_H

# include "libft.h"

typedef struct s_cube_data {
	char    *north_texture; // NO
	char    *south_texture; // SO
	char    *west_texture; // WE
	char    *east_texture; // EA
	int     floor_color[3]; // F
	int     ceiling_color[3]; // C
	char    **map; // MAP
}   t_cube_data;

# endif
