/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:39:31 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/12 03:20:34 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

int	get_pixel_color(int x, int y, t_image_info *img)
{
	char	*dst;

	dst = img->addres + (y * img->line_s + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}
