/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:17:42 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/05/11 09:51:29 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"


void alloc_textures(t_cube_data *data)
{
 /*    int i;
    
    i = -1;
    
    while (++i < 5)
    {
    }
     */
    data->textures=(t_image_info *)ft_calloc(sizeof(t_image_info),sizeof(t_image_info)*5);
    if(!data->textures)
        exit(0);
}