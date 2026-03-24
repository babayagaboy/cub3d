/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:20:03 by hgutterr          #+#    #+#             */
/*   Updated: 2026/03/24 18:32:14 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeight)
		return ;
	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_column(t_mlx *mlx,int x, int start, int end, int color)
{
	while (start < end)
	{
		put_pixel(mlx, x, start, color);
		start++;
	}
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return ;
	mlx->win = mlx_new_window(mlx->mlx, screenWidth, screenHeight, "cub3d");
	mlx->img = mlx_new_image(mlx->mlx, screenWidth, screenHeight);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp,
			&mlx->line_len, &mlx->endian);
}

void    init_player(t_player *p)
{
	p->pos_y = 12;  //x and y start position //get_player_coords()
	p->pos_x = 22;

	p->dir_y = 0;	//initial direction vector (N, S, W, E)
	p->dir_x = -1;

	//^^ mykyta ^^

	p->plane_y = p->dir_x * 0.66; //the 2d raycaster version of camera plane
	p->plane_x = -p->dir_y * 0.66;
	
	p->time = 0; //time of current frame
	p->old_time = 0; //time of previous frame
	p->frame_time = 0;

	p->move_speed = 0;
	p->rot_speed = 0;
}

void    calc_camera(t_ray *r, t_player *p, int i)
{
	r->camera_x = 2 * i / (double)screenWidth - 1;
	r->ray_dir_y = p->dir_y + p->plane_y * r->camera_x;
	r->ray_dir_x = p->dir_x + p->plane_x * r->camera_x;
}

void	calc_dda(t_ray *r, t_player *p)
{
	r->map_x = (int)p->pos_x; //our position in the map
	r->map_y = (int)p->pos_y;

	if (r->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1 / r->ray_dir_x);	// same thing has pythagoras theorem
	if (r->ray_dir_y == 0)
		r->delta_dist_y = 1e30;						//edge case if delta_dist = 0
	else
		r->delta_dist_y = fabs(1 / r->ray_dir_y);
	if (r->ray_dir_x < 0)	// ray on the left or rigth
	{
		r->step_x = -1;
		r->side_dist_x = (p->pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - p->pos_x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)	// ray on the up or down
	{
		r->step_y = -1;
		r->side_dist_y = (p->pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - p->pos_y) * r->delta_dist_y;
	}
}

void	run_dda(t_ray *r, char **map)
{
	r->hit = 0;
	while(r->hit == 0)	// search dda till it hits a wall
	{
		if(r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (map[r->map_y][r->map_x] != '0')
			r->hit = 1;
	}
	if (r->side == 0)
		r->perp_wall_dist = (r->side_dist_x - r->delta_dist_x);
	else
		r->perp_wall_dist = (r->side_dist_y - r->delta_dist_y);
}

void	draw_column(t_mlx *mlx, t_ray *r, int i)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	if (r->perp_wall_dist <= 0)
		r->perp_wall_dist = 0.1;
	line_height = (int)(screenHeight / r->perp_wall_dist);
	draw_start = (-1 * line_height) / 2 + screenHeight / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + screenHeight / 2;
	if (draw_end >= screenHeight)
		draw_end = screenHeight - 1;
	if (r->side == 1)
		put_column(mlx, i, draw_start, draw_end, (0x00FF0000 / 2));
	else
		put_column(mlx, i, draw_start, draw_end, 0x00FF0000);
}

double	get_timestamp(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1e6);
}

void	get_time(t_player *p)
{
	p->old_time = p->time;
	p->time = get_timestamp();
	p->frame_time = p->time - p->old_time;			// time this frame has taken, in seconds
	p->move_speed = p->frame_time * 500000.0;		// const value in squares per sec
	p->rot_speed = p->frame_time * 300000.0;		// const value in radians per sec
}
	
void    calc_rays(t_mlx *mlx, t_ray *ray, t_player *player, char **map)
{
	int i;

	i = 0;
	while (i < screenWidth * screenHeight * 4)
	{
		mlx->addr[i] = 0;
		i++;
	}
	i = 0;
	while (i < screenWidth) // calculate ray
	{
		get_time(player);
		calc_camera(ray, player, i);
		calc_dda(ray, player);
		run_dda(ray, map);
//		printf("BEFORE IMAGE TO WINDOW\n");
		draw_column(mlx, ray, i);
		i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int		handle_input(int key, t_game *g)
{
	if (key == KEY_UP)
	{
		if ((g->map[(int)(g->player->pos_x + (g->player->dir_x * g->player->move_speed))][(int)(g->player->pos_y)]) == '0')
			g->player->pos_x += g->player->dir_x * g->player->move_speed;
		if ((g->map[(int)(g->player->pos_x)][(int)(g->player->pos_y + (g->player->dir_y * g->player->move_speed))]) == '0')
			g->player->pos_y += g->player->dir_y * g->player->move_speed;
	}
	if (key == KEY_DOWN)
	{
		if ((g->map[(int)(g->player->pos_x - g->player->dir_x * g->player->move_speed)][(int)(g->player->pos_y)]) == '0')
			g->player->pos_x -= g->player->dir_x * g->player->move_speed;
		if ((g->map[(int)(g->player->pos_x)][(int)(g->player->pos_y - g->player->dir_y * g->player->move_speed)]) == '0')
			g->player->pos_y -= g->player->dir_y * g->player->move_speed;
	}
	if (key == KEY_RIGHT)
	{
		g->player->old_dir_x = g->player->dir_x;
		g->player->dir_x = g->player->dir_x * cos(g->player->rot_speed) - g->player->dir_y * sin(g->player->rot_speed);
		g->player->dir_y = g->player->old_dir_x * sin(g->player->rot_speed) + g->player->dir_y * cos(g->player->rot_speed);
		g->player->old_plane_x = g->player->plane_x;
		g->player->plane_x = g->player->plane_x * cos(g->player->rot_speed) - g->player->plane_y * sin(g->player->rot_speed);
		g->player->plane_y = g->player->plane_x * sin(g->player->rot_speed) + g->player->plane_y * cos(g->player->rot_speed);
	}
	if (key == KEY_LEFT)
	{
		g->player->old_dir_x = g->player->dir_x;
		g->player->dir_x = g->player->dir_x * cos(-g->player->rot_speed) - g->player->dir_y * sin(-g->player->rot_speed);
		g->player->dir_y = g->player->old_dir_x * sin(-g->player->rot_speed) + g->player->dir_y * cos(-g->player->rot_speed);
		g->player->old_plane_x = g->player->plane_x;
		g->player->plane_x = g->player->plane_x * cos(-g->player->rot_speed) - g->player->plane_y * sin(-g->player->rot_speed);
		g->player->plane_y = g->player->plane_x * sin(-g->player->rot_speed) + g->player->plane_y * cos(-g->player->rot_speed);

	}
	calc_rays(g->mlx, g->ray, g->player, g->map);
	return (0);
}

void	start(t_game *game)
{
	calc_rays(game->mlx, game->ray, game->player, game->map);
	mlx_key_hook(game->mlx->win, handle_input, game);
}