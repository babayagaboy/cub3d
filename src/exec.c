/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:20:03 by hgutterr          #+#    #+#             */
/*   Updated: 2026/04/23 01:22:43 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int buffer[screenHeight][screenWidth];

static char	get_player_marker(t_player *player)
{
	if (fabs(player->dir_x) >= fabs(player->dir_y))
	{
		if (player->dir_x >= 0)
			return ('E');
		return ('W');
	}
	if (player->dir_y >= 0)
		return ('S');
	return ('N');
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

double	get_timestamp(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1e6);
}

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeight)
		return ;
	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	drawbuffer(t_mlx *mlx)
{
	int y;
	int x;

	y = 0;
	while(y < screenHeight)
	{
		x = 0;
		while (x < screenWidth)
		{
			put_pixel(mlx, x, y, buffer[y][x]);
			++x;
		}
		++y;
	}
}

void	put_square(int y, int x, int color, t_game *g)
{
	int i;
	int j;

	i = y * g->sp;
	while (i < y * g->sp + g->sp)
	{
		j = x * g->sp;
		while (j < x * g->sp + g->sp)
		{
			put_pixel(g->mlx,  j, i, color);
			++j;
		}
		++i;
	}
}

int		get_color(int r, int g, int b)
{
	return (r * (256 * 256) + g * 256 + b);
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
	p->kp_w = 0;
	p->kp_s = 0;
	p->kp_a = 0;
	p->kp_d = 0;

	p->old_pos_x = p->pos_x;
	p->old_pos_y = p->pos_y;


	p->plane_y = p->dir_x * 0.66; //the 2d raycaster version of camera plane
	p->plane_x = -p->dir_y * 0.66;
	
	p->time = get_timestamp(); 
	p->old_time = p->time; 
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
		r->side_dist_x = ((p->pos_x - r->map_x) * r->delta_dist_x);
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = ((r->map_x + 1.0 - p->pos_x) * r->delta_dist_x);
	}
	if (r->ray_dir_y < 0)	// ray on the up or down
	{
		r->step_y = -1;
		r->side_dist_y = ((p->pos_y - r->map_y) * r->delta_dist_y);
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = ((r->map_y + 1.0 - p->pos_y) * r->delta_dist_y);
	}
}

int	get_door_side(char **map, int y, int x)
{
	if (y > 0 && map[y - 1] && map[y - 1][x] && is_wall(map[y - 1][x]))
	{
		if (map[y + 1] && map[y + 1][x] && is_wall(map[y + 1][x]))
			return (0);
	}
	return (1);
}

int	hit_door_plane(t_ray *r, t_player *p, char **map)
{
	double	door_plane;
	double	hit_pos;

	r->door_side = get_door_side(map, r->map_y, r->map_x);
	if (r->door_side == 0)
	{
		if (r->ray_dir_x == 0)
			return (0);
		door_plane = r->map_x + 0.5;
		r->perp_wall_dist = (door_plane - p->pos_x) / r->ray_dir_x;
		hit_pos = p->pos_y + r->perp_wall_dist * r->ray_dir_y;
		if (r->perp_wall_dist > 0 && hit_pos >= r->map_y
			&& hit_pos <= r->map_y + 1.0)
			return (1);
	}
	else
	{
		if (r->ray_dir_y == 0)
			return (0);
		door_plane = r->map_y + 0.5;
		r->perp_wall_dist = (door_plane - p->pos_y) / r->ray_dir_y;
		hit_pos = p->pos_x + r->perp_wall_dist * r->ray_dir_x;
		if (r->perp_wall_dist > 0 && hit_pos >= r->map_x
			&& hit_pos <= r->map_x + 1.0)
			return (1);
	}
	return (0);
}

void	run_dda(t_ray *r, t_player *p, char **map)
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
		if (map[r->map_y][r->map_x] == 'D')
		{
			if (hit_door_plane(r, p, map))
			{
				r->hit = 2;
				r->side = r->door_side;
			}
		}
		else if (map[r->map_y][r->map_x] != '0')
			r->hit = 1;
	}
	if (r->hit == 2)
		return ;
	if (r->side == 0)
		r->perp_wall_dist = (r->side_dist_x - r->delta_dist_x);
	else
		r->perp_wall_dist = (r->side_dist_y - r->delta_dist_y);
}

void	get_fc(t_ray *r, t_player *p, t_ori_tex *t, int i)
{
	int pos;
	int j;
	int	tex_x;
	int	tex_y;
	int	color;

	j = 0;
	r->ray_dir_x_l = p->dir_x - p->plane_x;
	r->ray_dir_y_l = p->dir_y - p->plane_y;
	r->ray_dir_x_r = p->dir_x + p->plane_x;
	r->ray_dir_y_r = p->dir_y + p->plane_y;
	if (i <= (screenHeight >> 1))
		return ;
	pos = i - (screenHeight >> 1);
	p->pos_z = (screenHeight >> 1);
	p->row_dis = p->pos_z / pos;
	r->floor_step_x = p->row_dis * (r->ray_dir_x_r - r->ray_dir_x_l) / screenWidth;
	r->floor_step_y = p->row_dis * (r->ray_dir_y_r - r->ray_dir_y_l) / screenWidth;
	r->floor_x = p->pos_x + p->row_dis * r->ray_dir_x_l;
	r->floor_y = p->pos_y + p->row_dis * r->ray_dir_y_l;
	while (j < screenWidth)
	{
		double	frac_x = r->floor_x - floor(r->floor_x);
		double	frac_y = r->floor_y - floor(r->floor_y);

		if(t->path_ceiling)
		{
			int *pixels = (int *)t->tex_ceiling->data;
			tex_x = (int)(t->tex_ceiling->width * frac_x);
			tex_y = (int)(t->tex_ceiling->height * frac_y);
			color = pixels[tex_y * (t->tex_ceiling->line_len / 4) + tex_x];
			buffer[screenHeight - i - 1][j] = color;
		}
		if(t->path_floor)
		{
			int *pixels = (int *)t->tex_floor->data;
			tex_x = (int)(t->tex_floor->width * frac_x);
			tex_y = (int)(t->tex_floor->height * frac_y);
			color = pixels[tex_y * (t->tex_floor->line_len / 4) + tex_x];
			buffer[i][j] = color;
		}
		r->floor_x += r->floor_step_x;
		r->floor_y += r->floor_step_y;
		++j;
	}
}


void	get_walls(t_ray *r, t_player *p, t_ori_tex *tex, int i)
{
	t_texture *t = NULL;
	int	line_height;
	int	draw_start;
	int	draw_end;

	if (r->perp_wall_dist <= 0)
		r->perp_wall_dist = 0.1;
	line_height = (int)(screenHeight / r->perp_wall_dist);
	draw_start = ((-1 * line_height) >> 1) + (screenHeight >> 1);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (line_height >> 1) + (screenHeight >> 1);
	if (draw_end >= screenHeight)
		draw_end = screenHeight - 1;
	if (r->side == 0)
		r->wall_hit_pos_x = p->pos_y + r->perp_wall_dist * r->ray_dir_y;
	else
		r->wall_hit_pos_x = p->pos_x + r->perp_wall_dist * r->ray_dir_x;
	if (r->hit == 2)
		t = tex->tex_door;
	else if (r->side == 0 && r->ray_dir_x > 0)
		t = tex->tex_west;
	else if (r->side == 0)
		t = tex->tex_east;
	else if (r->ray_dir_y > 0)
		t = tex->tex_north;
	else if (r->side == 1)
		t = tex->tex_south;
	r->wall_hit_pos_x -= floor(r->wall_hit_pos_x);
	r->tex_step = 1.0 * t->height / line_height;
	r->tex_pos = (draw_start - (screenHeight >> 1) + (line_height >> 1)) * r->tex_step;

	int tex_x;
	tex_x = (int)(r->wall_hit_pos_x * (1.0 * t->width));
	if(r->side == 0 && r->ray_dir_x > 0) tex_x = t->width - tex_x - 1;
	if(r->side == 1 && r->ray_dir_y < 0) tex_x = t->width - tex_x - 1;

	int tex_y;
	int start = draw_start;
	int end = draw_end;
	int color;
	while (start <= end)
	{
		if (start >= 0 && start < screenHeight && i >= 0 && i < screenWidth)
		{
			tex_y = (int)r->tex_pos;

			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= t->height)
				tex_y = t->height - 1;

			int *pixels = (int *)t->data;
			color = pixels[tex_y * (t->line_len / 4) + tex_x];
			buffer[start][i] = color;
		}
		r->tex_pos += r->tex_step;
		++start;
	}
}

void	get_c_colored(t_ori_tex *tex)
{
	int	x;
	int	y;
	int half_h;

	x = 0;
	y = 0;
	half_h = screenHeight >> 1;
	while (x < screenWidth)
	{
		y = 0;

		while (y < half_h)
		{
			if (buffer[y][x] == 0)
				buffer[y][x] =  get_color(tex->rgb_ceiling[0], tex->rgb_ceiling[1], tex->rgb_ceiling[2]);
			++y;
		}
		++x;
	}
}

void	get_f_colored(t_ori_tex *tex)
{
	int	x;
	int	y;
	int half_h;

	x = 0;
	half_h = screenHeight >> 1;
	while (x < screenWidth)
	{
		y = half_h;
		while (y < screenHeight)
		{
			if (buffer[y][x] == 0)
				buffer[y][x] =  get_color(tex->rgb_floor[0], tex->rgb_floor[1], tex->rgb_floor[2]);
			++y;
		}
		++x;
	}
}

void	get_time(t_player *p)
{
	p->old_time = p->time;
	p->time = get_timestamp();
	p->frame_time = p->time - p->old_time;			// time this frame has taken, in seconds
	p->move_speed = p->frame_time * 3.0;			// const value in squares per sec
	p->rot_speed = p->frame_time * 2.0;			// const value in radians per sec
	//printf("frame: %f | moveSpeed: %f\n", p->frame_time, p->move_speed);
}

void	upd_player_minimap(t_game *g)
{
	g->minimap[(int)g->player->old_pos_y][(int)g->player->old_pos_x] = '0';
	g->minimap[(int)g->player->pos_y][(int)g->player->pos_x]
		= get_player_marker(g->player);
	g->player->old_pos_y = g->player->pos_y;
	g->player->old_pos_x = g->player->pos_x;
}

void	minimap(t_game *g)
{
	int	i;
	int	j;

	if (g->map_h > g->map_w)
		g->sp = (int)(300 / g->map_h);
	else
		g->sp = (int)(300 / g->map_w);
	i = 0;
	for (i = 0; g->minimap[i]; ++i)
	{
		for (j = 0; g->minimap[i][j]; ++j)
		{
			if (is_wall(g->minimap[i][j]))
				put_square(i, j, 0x48494B, g);
			if (g->minimap[i][j] == '0')
				put_square(i, j, 0x808588, g);
			if (g->minimap[i][j] == 'D')
				put_square(i, j, 0x0000FF, g);
			if (is_player(g->minimap[i][j]))
				put_square(i, j, 0xFF0000, g);
		}
	}
}

// 0x48494B wall
// 0x808588 floor
	
void    calc_rays(t_mlx *mlx, t_ray *ray, t_player *player, t_game *g)
{
	int i;

	i = 0;
	int size = mlx->line_len * screenHeight;
	for (int j = 0; j < size; j++)
		mlx->addr[j] = 0;
	while (i < screenHeight)
	{
		get_fc(ray, player, g->o_text, i);
		++i;
	}
	i = 0;
	while (i < screenWidth) // calculate ray
	{
		calc_camera(ray, player, i);
		calc_dda(ray, player);
		run_dda(ray, player, g->map);
		get_walls(ray, player, g->o_text, i);
		++i;
	}
	if (!g->o_text->path_ceiling)
		get_c_colored(g->o_text);
	if (!g->o_text->path_floor)
		get_f_colored(g->o_text);
	drawbuffer(g->mlx);
	for(int y = 0; y < screenHeight; ++y) {
		for(int x = 0; x < screenWidth; ++x) {
			buffer[y][x] = 0;
		}
	}
	minimap(g);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int		key_press(int key, t_game *g)
{
	if (key == KEY_UP)
		g->player->kp_w = 1;
	if (key == KEY_DOWN)
		g->player->kp_s = 1;
	if (key == KEY_LEFT)
		g->player->kp_a = 1;
	if (key == KEY_RIGHT)
		g->player->kp_d = 1;
	if (key == KEY_ESC)
		exit(0);
	return (0);
}
int		key_release(int key, t_game *g)
{
	if (key == KEY_UP)
		g->player->kp_w = 0;
	if (key == KEY_DOWN)
		g->player->kp_s = 0;
	if (key == KEY_LEFT)
		g->player->kp_a = 0;
	if (key == KEY_RIGHT)
		g->player->kp_d = 0;
	return (0);
}

int		handle_input(t_game *g)
{
	int moved;

	moved = 0;
	if (g->player->kp_w)
	{
		if ((g->map[(int)(g->player->pos_y)][(int)(g->player->pos_x + (g->player->dir_x * g->player->move_speed))])
			&& (g->map[(int)(g->player->pos_y)][(int)(g->player->pos_x + (g->player->dir_x * g->player->move_speed))]) == '0')
			g->player->pos_x += g->player->dir_x * g->player->move_speed;
		if ((g->map[(int)(g->player->pos_y + (g->player->dir_y * g->player->move_speed))][(int)(g->player->pos_x)])
			&& (g->map[(int)(g->player->pos_y + (g->player->dir_y * g->player->move_speed))][(int)(g->player->pos_x)]) == '0')
			g->player->pos_y += g->player->dir_y * g->player->move_speed;
		moved = 1;
	}
	if (g->player->kp_s)
	{
		if ((g->map[(int)(g->player->pos_y)][(int)(g->player->pos_x - g->player->dir_x * g->player->move_speed)]) == '0')
			g->player->pos_x -= g->player->dir_x * g->player->move_speed;
		if ((g->map[(int)(g->player->pos_y - g->player->dir_y * g->player->move_speed)][(int)(g->player->pos_x)]) == '0')
			g->player->pos_y -= g->player->dir_y * g->player->move_speed;
		moved = 1;	
	}
	if (g->player->kp_d)
	{
		g->player->old_dir_x = g->player->dir_x;
		g->player->dir_x = g->player->dir_x * cos(g->player->rot_speed) - g->player->dir_y * sin(g->player->rot_speed);
		g->player->dir_y = g->player->old_dir_x * sin(g->player->rot_speed) + g->player->dir_y * cos(g->player->rot_speed);
		g->player->old_plane_x = g->player->plane_x;
		g->player->plane_x = g->player->plane_x * cos(g->player->rot_speed) - g->player->plane_y * sin(g->player->rot_speed);
		g->player->plane_y = g->player->old_plane_x * sin(g->player->rot_speed) + g->player->plane_y * cos(g->player->rot_speed);
		moved = 1;
	}
	if (g->player->kp_a)
	{
		g->player->old_dir_x = g->player->dir_x;
		g->player->dir_x = g->player->dir_x * cos(-g->player->rot_speed) - g->player->dir_y * sin(-g->player->rot_speed);
		g->player->dir_y = g->player->old_dir_x * sin(-g->player->rot_speed) + g->player->dir_y * cos(-g->player->rot_speed);
		g->player->old_plane_x = g->player->plane_x;
		g->player->plane_x = g->player->plane_x * cos(-g->player->rot_speed) - g->player->plane_y * sin(-g->player->rot_speed);
		g->player->plane_y = g->player->old_plane_x * sin(-g->player->rot_speed) + g->player->plane_y * cos(-g->player->rot_speed);
		moved = 1;
	}
	get_time(g->player);
	if (moved)
	{
		upd_player_minimap(g);
		calc_rays(g->mlx, g->ray, g->player, g);
	}
	return (0);
}



void	start(t_game *game)
{
	game->minimap = copy_map(game->map, 0, game->map_h);
	game->map[(int)game->player->pos_y][(int)game->player->pos_x] = '0';
	
	// Passa 'game' em vez de 'game->player'
	mlx_hook(game->mlx->win, 2, 1L<<0, key_press, game);
	mlx_hook(game->mlx->win, 3, 1L<<1, key_release, game);
	
	mlx_loop_hook(game->mlx->mlx, handle_input, game);
	calc_rays(game->mlx, game->ray, game->player, game);
}
