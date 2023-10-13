/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ou <abdel-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:56:36 by abdel-ou          #+#    #+#             */
/*   Updated: 2023/10/13 16:41:34 by abdel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void drow_rays(t_mlx *mlxx, double angle, int color)
{
    int x = mlxx->player_x;
    int y = mlxx->player_y;
    int z = 1;
    int xx, yy;

    while (z < 100)
    {
        xx = x - (z * cos(angle));
        yy = y - (z * sin(angle));
        
        // Check for collision with obstacles in your environment
        if (mlxx->map[(int)(yy / 40)][(int)(xx / 40)] == '1') {
            break; // Exit the loop when hitting an obstacle
        }

        my_mlx_pixel_put(&mlxx->img, xx, yy, color);
        z++;
    }
}
t_point horizontal_ray(t_mlx *mlxx, double angle)
{
    int y_intercept;
    int x_intercept;
    int x_step;
    t_point h_point;

	x_step = 40 / tan(M_PI - angle);
    if (angle >= 0 && angle < M_PI)
    {
        y_intercept = (int)(mlxx->player_y / 40) * 40;
        x_intercept = mlxx->player_x + (y_intercept - mlxx->player_y) / tan(angle);
    }
    else
    {
        y_intercept = (int)((mlxx->player_y / 40) + 1) * 40;
        x_intercept = mlxx->player_x + (y_intercept - mlxx->player_y) / tan(angle);
    }

    while (x_intercept >= 0 && x_intercept < mlxx->weight &&
           y_intercept >= 0 && y_intercept < mlxx->height * 40)
    {
        if (mlxx->map[(int)(y_intercept / 40)][(int)(x_intercept / 40)] == '1' || mlxx->map[(int)(y_intercept / 40) - 1][(int)(x_intercept / 40)] == '1')
            break;

        if (angle >= 0 && angle < M_PI)
        {
            x_intercept += x_step;
            y_intercept -= 40;
        }
        else
        {
            x_intercept -= x_step;
            y_intercept += 40;
        }
    }
    if (x_intercept <= 0 || x_intercept >= mlxx->weight || y_intercept <= 0 || y_intercept >= mlxx->height)
    {
        h_point.x = 10000;
        h_point.y = 10000;
        return(h_point);
    }
    h_point.x = x_intercept;
    h_point.y = y_intercept;
    // draw_line(mlxx->player_x, mlxx->player_y, h_point.x, h_point.y, mlxx->img, 0x00ff00);
    return (h_point);
}