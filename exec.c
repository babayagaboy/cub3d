/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <myivanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:29:02 by hgutterr          #+#    #+#             */
/*   Updated: 2026/05/07 14:12:00 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int buffer[SCREENHEIGHT][SCREENWIDTH];

//----------------------------------------------
// typedef struct s_weapon_hud
// {
// 	t_texture	*tex;
// 	int			start_x;
// 	int			start_y;
// 	float		scale;
// } 				t_weapon_hud;

// void	get_weapon_hud_start_pos(t_texture *tex, float scale, int *start_x, int *start_y)
// {
// 	*start_x = (SCREENWIDTH - (tex->width / scale)) + (SCREENWIDTH / 18);
// 	*start_y = SCREENHEIGHT - (tex->height / scale) + 50;
// }

// void	draw_weapon_hud_row(t_weapon_hud *hud, int y)
// {
// 	int				x;
// 	unsigned int	color;
// 	unsigned int	*pixels;
// 	int				bx;
// 	int				by;

// 	x = 0;
// 	pixels = (unsigned int *)hud->tex->data;
// 	while (x < hud->tex->width)
// 	{
// 		bx = hud->start_x + (x / hud->scale);
// 		by = hud->start_y + (y / hud->scale);

// 		color = pixels[y * (hud->tex->line_len / 4) + x];
// 		if (bx >= 0 && bx < SCREENWIDTH && by >= 0 && by < SCREENHEIGHT
// 			&& (color & 0xFF000000) == 0)
// 		{
// 			buffer[by][bx] = color;
// 		}
// 		x++;
// 	}
// }

// void	draw_weapon_hud_pixels(t_weapon_hud *hud)
// {
// 	int	y;

// 	y = 0;
// 	while (y < hud->tex->height)
// 	{
// 		draw_weapon_hud_row(hud, y);
// 		y++;
// 	}
// }

// void	draw_weapon_hud(t_game *g, int i)
// {
// 	t_weapon_hud	hud;

// 	if (!g->lightsaber || !g->lightsaber->tex_arr[i])
// 		return ;

// 	hud.tex = g->lightsaber->tex_arr[i];
// 	hud.scale = 1.5;

// 	get_weapon_hud_start_pos(hud.tex, hud.scale, &hud.start_x, &hud.start_y);
// 	draw_weapon_hud_pixels(&hud);
// }
//----------------------------------------------


//----------------------------------------------
// typedef struct s_attack_hud
// {
// 	t_texture	*tex;
// 	int			start_x;
// 	int			start_y;
// 	float		scale;
// }				t_attack_hud;

// void	get_attack_hud_start_pos(t_texture *tex, float scale, int *start_x, int *start_y)
// {
// 	*start_x = (SCREENWIDTH - (tex->width / scale)) + (SCREENWIDTH / 18);
// 	*start_y = SCREENHEIGHT - (tex->height / scale) + 50;
// }

// void	draw_attack_hud_row(t_attack_hud *hud, int y)
// {
// 	int				x;
// 	unsigned int	color;
// 	unsigned int	*pixels;
// 	int				bx;
// 	int				by;

// 	x = 0;
// 	pixels = (unsigned int *)hud->tex->data;
// 	while (x < hud->tex->width)
// 	{
// 		bx = hud->start_x + (x / hud->scale);
// 		by = hud->start_y + (y / hud->scale);

// 		color = pixels[y * (hud->tex->line_len / 4) + x];
// 		if (bx >= 0 && bx < SCREENWIDTH && by >= 0 && by < SCREENHEIGHT
// 			&& (color & 0xFF000000) == 0)
// 		{
// 			buffer[by][bx] = color;
// 		}
// 		x++;
// 	}
// }

// void	draw_attack_hud_pixels(t_attack_hud *hud)
// {
// 	int	y;

// 	y = 0;
// 	while (y < hud->tex->height)
// 	{
// 		draw_attack_hud_row(hud, y);
// 		y++;
// 	}
// }

// void	draw_attack_hud(t_game *g, int i)
// {
//     t_attack_hud hud;

//     if (!g->lightsaber || !g->lightsaber->tex_atk_arr[i])
//         return;

//     hud.tex = g->lightsaber->tex_atk_arr[i];
//     hud.scale = 1.5;

//     get_attack_hud_start_pos(hud.tex, hud.scale, &hud.start_x, &hud.start_y);
//     draw_attack_hud_pixels(&hud);
// }

//----------------------------------------------


// t_door	*find_door(t_game *g, int y, int x)
// {
// 	int	i;

// 	if (!g->door)
// 		return (NULL);
// 	i = 0;
// 	while (g->door[i])
// 	{
// 		if ((int)g->door[i]->pos_y == y && (int)g->door[i]->pos_x == x)
// 			return (g->door[i]);
// 		++i;
// 	}
// 	return (NULL);
// }


//----------------------------------------------

// void	get_player_door_diff(t_player *player, t_door *door, int *diff_x, int *diff_y)
// {
// 	int	player_x;
// 	int	player_y;
// 	int	door_x ;
// 	int	door_y;


// 	player_x = (int)player->pos_x;
// 	player_y = (int)player->pos_y;
// 	door_x = (int)door->pos_x;
// 	door_y = (int)door->pos_y;
// 	*diff_x = player_x - door_x;
// 	*diff_y = player_y - door_y;
// }

// int	check_adjacent(int diff_x, int diff_y)
// {
// 	if ((diff_y == 0 && diff_x == 0)
// 		|| (diff_y == 1 && diff_x == 0)
// 		|| (diff_y == -1 && diff_x == 0)
// 		|| (diff_y == 0 && diff_x == 1)
// 		|| (diff_y == 0 && diff_x == -1))
// 		return (1);
//     return (0);
// }

// int	is_player_adjacent_to_door(t_game *g, t_door *door)
// {
// 	int	diff_x;
// 	int	diff_y;

// 	get_player_door_diff(g->player, door, &diff_x, &diff_y);
// 	return (check_adjacent(diff_x, diff_y));
// }

//----------------------------------------------



// int	update_single_door(t_game *g, t_door *door, double speed)
// {
// 	double	old_pct;

// 	old_pct = door->open_pct;
// 	door->opening = is_player_adjacent_to_door(g, door);
// 	if (door->opening)
// 		door->open_pct += speed;
// 	else
// 		door->open_pct -= speed;

// 	if (door->open_pct < 0.0)
// 		door->open_pct = 0.0;
// 	if (door->open_pct > 1.0)
// 		door->open_pct = 1.0;

// 	if (fabs(door->open_pct - old_pct) > 0.0001)
//     	return (1); // door mudou
//     return (0); // door não mudou
// }

// int	update_doors(t_game *g)
// {
// 	int		i;
// 	int		changed;
// 	double	speed;

// 	if (!g->door)
// 		return (0);

// 	changed = 0;
// 	speed = g->player->frame_time * 1.5;
// 	i = 0;
// 	while (g->door[i])
// 	{
// 		if (update_single_door(g, g->door[i], speed))
// 			changed = 1;
// 		i++;
// 	}
// 	return (changed);
// }


// int	is_walkable_tile(t_game *g, int y, int x)
// {
// 	t_door	*door;

// 	if (!g->map[y] || !g->map[y][x])
// 		return (0);
// 	if (g->map[y][x] == '0')
// 		return (1);
// 	if (g->map[y][x] != 'D')
// 		return (0);
// 	door = find_door(g, y, x);
// 	if (!door)
// 		return (0);
// 	return (door->open_pct >= 0.9);
// }

// char	get_player_marker(t_player *player)
// {
// 	if (fabs(player->dir_x) >= fabs(player->dir_y))
// 	{
// 		if (player->dir_x >= 0)
// 			return ('E');
// 		return ('W');
// 	}
// 	if (player->dir_y >= 0)
// 		return ('S');
// 	return ('N');
// }

// int	ft_isdigit(int c)
// {
// 	if (c >= '0' && c <= '9')
// 		return (1);
// 	return (0);
// }

// double	get_timestamp(void)
// {
// 	struct timeval tv;

// 	gettimeofday(&tv, NULL);
// 	return ((double)tv.tv_sec + (double)tv.tv_usec / 1e6);
// }
// void	put_pixel(t_mlx *mlx, int x, int y, int color)
// {
// 	char	*dst;

// 	if (x < 0 || x >= SCREENWIDTH || y < 0 || y >= SCREENHEIGHT)
// 		return ;
// 	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
// 	*(unsigned int *)dst = color;
// }

// void	drawbuffer(t_mlx *mlx)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	while (y < SCREENHEIGHT)
// 	{
// 		x = 0;
// 		while (x < SCREENWIDTH)
// 		{
// 			put_pixel(mlx, x, y, buffer[y][x]);
// 			++x;
// 		}
// 		++y;
// 	}

// }

// void	put_square(int y, int x, int color, t_game *g)
// {
// 	int	i;
// 	int	j;

// 	i = y * g->sp;
// 	while (i < y * g->sp + g->sp)
// 	{
// 		j = x * g->sp;
// 		while (j < x * g->sp + g->sp)
// 		{
// 			put_pixel(g->mlx, j, i, color);
// 			++j;
// 		}
// 		++i;
// 	}
// }

// int	get_color(int r, int g, int b)
// {
// 	return (r * (256 * 256) + g * 256 + b);
// }

// void	init_mlx(t_mlx *mlx)
// {
// 	mlx->mlx = mlx_init();
// 	if (!mlx->mlx)
// 		return ;
// 	mlx->win = mlx_new_window(mlx->mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
// 	mlx->img = mlx_new_image(mlx->mlx, SCREENWIDTH, SCREENHEIGHT);
// 	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp,
// 	&mlx->line_len, &mlx->endian);
// }

// void	init_player(t_player *p)
// {
// 	p->kp_w = 0;
// 	p->kp_s = 0;
// 	p->kp_a = 0;
// 	p->kp_d = 0;

// 	p->old_pos_x = p->pos_x;
// 	p->old_pos_y = p->pos_y;

// 	p->plane_y = p->dir_x * 0.66;
// 	p->plane_x = -p->dir_y * 0.66;

// 	p->time = get_timestamp();
// 	p->old_time = p->time;
// 	p->frame_time = 0;

// 	p->move_speed = 0;
// 	p->rot_speed = 0;
// }

// void	calc_camera(t_ray *r, t_player *p, int i)
// {
// 	r->camera_x = 2 * i / (double)SCREENWIDTH - 1;
// 	r->ray_dir_y = p->dir_y + p->plane_y * r->camera_x;
// 	r->ray_dir_x = p->dir_x + p->plane_x * r->camera_x;
// }





// int	get_door_side(char **map, int y, int x)
// {
// 	if (y > 0 && map[y - 1] && map[y - 1][x] && is_wall(map[y - 1][x]))
// 	{
// 		if (map[y + 1] && map[y + 1][x] && is_wall(map[y + 1][x]))
// 			return (0);
// 	}
// 	return (1);
// }





// int	hit_door_plane_x(t_ray *r, t_player *p, t_door *door)
// {
// 	double	door_plane;
// 	double	hit_pos;
// 	double	local_pos;

// 	if (r->ray_dir_x == 0)
// 		return (0);

// 	door_plane = r->map_x + 0.5;
// 	r->perp_wall_dist = (door_plane - p->pos_x) / r->ray_dir_x;
// 	hit_pos = p->pos_y + r->perp_wall_dist * r->ray_dir_y;
// 	local_pos = hit_pos - r->map_y;

// 	if (r->perp_wall_dist > 0 && local_pos >= 0.0
// 		&& local_pos <= (1.0 - door->open_pct))
// 	{
// 		r->wall_hit_pos_x = local_pos + door->open_pct;
// 		return (1);
// 	}
// 	return (0);
// }

// int	hit_door_plane_y(t_ray *r, t_player *p, t_door *door)
// {
// 	double	door_plane;
// 	double	hit_pos;
// 	double	local_pos;

// 	if (r->ray_dir_y == 0)
// 		return (0);

// 	door_plane = r->map_y + 0.5;
// 	r->perp_wall_dist = (door_plane - p->pos_y) / r->ray_dir_y;
// 	hit_pos = p->pos_x + r->perp_wall_dist * r->ray_dir_x;
// 	local_pos = hit_pos - r->map_x;

// 	if (r->perp_wall_dist > 0 && local_pos >= 0.0
// 		&& local_pos <= (1.0 - door->open_pct))
// 	{
// 		r->wall_hit_pos_x = local_pos + door->open_pct;
// 		return (1);
// 	}
// 	return (0);
// }


// int	hit_door_plane(t_ray *r, t_player *p, t_game *g)
// {
// 	t_door	*door;

// 	door = find_door(g, r->map_y, r->map_x);
// 	if (!door || door->open_pct >= 1.0)
// 		return 0;

// 	r->door_side = get_door_side(g->map, r->map_y, r->map_x);

// 	if (r->door_side == 0)
// 		return hit_door_plane_x(r, p, door);
// 	else
// 		return hit_door_plane_y(r, p, door);
// }


// int	get_door_count(char **map)
// {
// 	int	y;
// 	int	x;
// 	int	doors;

// 	if (!map || !map[0])
// 		return (0);
// 	y = 0;
// 	doors = 0;
// 	while (map[y])
// 	{
// 		x = 0;
// 		while (map[y][x])
// 		{
// 			if (map[y][x] == 'D')
// 				++doors;
// 			++x;
// 		}
// 		++y;
// 	}
// 	return (doors);
// }

// void	fill_door_cords(t_door **door, char **map)
// {
// 	int	y;
// 	int	x;
// 	int	i;

// 	y = 0;
// 	i = 0;
// 	while (map[y])
// 	{
// 		x = 0;
// 		while (map[y][x])
// 		{
// 			if (map[y][x] == 'D')
// 			{
// 				door[i]->pos_y = y;
// 				door[i]->pos_x = x;
// 				door[i]->open_pct = 0.0;
// 				door[i]->opening = 0;
// 				++i;
// 			}
// 			++x;
// 		}
// 		++y;
// 	}
// }

// t_door	**get_door_coords(t_game *g, char **map)
// {
// 	t_door	**door;
// 	int		i;
// 	int		door_count;

// 	i = 0;
// 	door_count = get_door_count(map);
// 	door = malloc(sizeof(t_door *) * (door_count + 1));
// 	if (!door)
// 		return (NULL);
// 	while (i < door_count)
// 	{
// 		door[i] = malloc(sizeof(t_door));
// 		if (!door[i])
// 		{
// 			while (--i)
// 				free(door[i]);
// 			return (NULL);
// 		}
// 		++i;
// 	}
// 	door[door_count] = NULL;
// 	g->door_count = door_count;
// 	fill_door_cords(door, map);
// 	return (door);
// }

//------------------------------------------


// void	run_dda(t_ray *r, t_player *p, t_game *g)
// {
// 	r->hit = 0;
// 	while (r->hit == 0)
// 		step_dda(r, p, g);

// 	calc_perp_wall_dist(r);
// }

//---------------------------------------------


//----------------------------------------------- 


// void	init_floor_ceil_params(t_ray *r, t_player *p, int i)
// {
// 	int	pos;

// 	r->ray_dir_x_l = p->dir_x - p->plane_x;
// 	r->ray_dir_y_l = p->dir_y - p->plane_y;
// 	r->ray_dir_x_r = p->dir_x + p->plane_x;
// 	r->ray_dir_y_r = p->dir_y + p->plane_y;

// 	pos = i - (SCREENHEIGHT >> 1);
// 	p->pos_z = (SCREENHEIGHT >> 1);
// 	p->row_dis = p->pos_z / pos;

// 	r->floor_step_x = p->row_dis * (r->ray_dir_x_r - r->ray_dir_x_l) / SCREENWIDTH;
// 	r->floor_step_y = p->row_dis * (r->ray_dir_y_r - r->ray_dir_y_l) / SCREENWIDTH;

// 	r->floor_x = p->pos_x + p->row_dis * r->ray_dir_x_l;
// 	r->floor_y = p->pos_y + p->row_dis * r->ray_dir_y_l;
// }

// void	draw_ceil_pixel(t_ori_tex *t, t_ray *r, int screen_i, int j)
// {
// 	int	tex_x;
// 	int	tex_y;
// 	int	color;
// 	int	*pixels;

// 	pixels = (int *)t->tex_ceiling->data;
// 	tex_x = (int)(t->tex_ceiling->width * (r->floor_x - floor(r->floor_x)));
// 	tex_y = (int)(t->tex_ceiling->height * (r->floor_y - floor(r->floor_y)));
// 	color = pixels[tex_y * (t->tex_ceiling->line_len / 4) + tex_x];
// 	buffer[SCREENHEIGHT - screen_i - 1][j] = color;
// }

// void draw_floor_pixel(t_ori_tex *t, t_ray *r, int screen_i, int j)
// {
// 	int	tex_x;
// 	int	tex_y;
// 	int	color;
// 	int	*pixels;

// 	pixels = (int *)t->tex_floor->data;
// 	tex_x = (int)(t->tex_floor->width * (r->floor_x - floor(r->floor_x)));
// 	tex_y = (int)(t->tex_floor->height * (r->floor_y - floor(r->floor_y)));
// 	color = pixels[tex_y * (t->tex_floor->line_len / 4) + tex_x];
// 	buffer[screen_i][j] = color;
// }

// void	get_fc(t_ray *r, t_player *p, t_ori_tex *t, int i)
// {
// 	int	j;

// 	if (i <= (SCREENHEIGHT >> 1))
//     	return ;

// 	init_floor_ceil_params(r, p, i);

// 	j = 0;
// 	while (j < SCREENWIDTH)
// 	{
// 		if (t->path_ceiling)
// 			draw_ceil_pixel(t, r, i, j);
// 		if (t->path_floor)
// 			draw_floor_pixel(t, r, i, j);

// 		r->floor_x += r->floor_step_x;
// 		r->floor_y += r->floor_step_y;
// 		++j;
// 	}
// }

//-----------------------------

// typedef struct s_draw_params
// {
// 	t_ray		*r;
// 	t_texture	*t;
// 	int			tex_x;
// 	int			draw_start;
// 	int			draw_end;
// 	int			i;
// } t_draw_params;

// typedef struct s_wall_calc
// {
// 	int	line_height;
// 	int	draw_start;
// 	int	draw_end;
// } t_wall_calc;

// int	calc_draw_positions(t_ray *r, int *draw_start, int *draw_end)
// {
// 	int	line_height;

// 	if (r->perp_wall_dist <= 0)
// 		r->perp_wall_dist = 0.1;
// 	line_height = (int)(SCREENHEIGHT / r->perp_wall_dist);

// 	*draw_start = ((-1 * line_height) >> 1) + (SCREENHEIGHT >> 1);
// 	if (*draw_start < 0)
// 		*draw_start = 0;

// 	*draw_end = (line_height >> 1) + (SCREENHEIGHT >> 1);
// 	if (*draw_end >= SCREENHEIGHT)
// 		*draw_end = SCREENHEIGHT - 1;

// 	return (line_height);
// }

// void	calc_wall_hit(t_ray *r, t_player *p)
// {
// 	if (r->hit != 2 && r->side == 0)
// 		r->wall_hit_pos_x = p->pos_y + r->perp_wall_dist * r->ray_dir_y;
// 	else if (r->hit != 2)
// 		r->wall_hit_pos_x = p->pos_x + r->perp_wall_dist * r->ray_dir_x;
// }

// t_texture	*select_texture(t_ray *r, t_ori_tex *tex)
// {
// 	if (r->hit == 2)
// 		return (tex->tex_door);
// 	else if (r->side == 0 && r->ray_dir_x > 0)
// 		return (tex->tex_west);
// 	else if (r->side == 0)
// 		return (tex->tex_east);
// 	else if (r->ray_dir_y > 0)
// 		return (tex->tex_north);
// 	else
// 		return (tex->tex_south);
// }

// int	calc_tex_mapping(t_ray *r, t_texture *t, int line_height, int draw_start)
// {
// 	int tex_x;

// 	r->wall_hit_pos_x -= floor(r->wall_hit_pos_x);
// 	r->tex_step = 1.0 * t->height / line_height;
// 	r->tex_pos = (draw_start - (SCREENHEIGHT >> 1) + (line_height >> 1)) * r->tex_step;

// 	tex_x = (int)(r->wall_hit_pos_x * (1.0 * t->width));
// 	if (r->side == 0 && r->ray_dir_x > 0)
// 		tex_x = t->width - tex_x - 1;
// 	if (r->side == 1 && r->ray_dir_y < 0)
// 		tex_x = t->width - tex_x - 1;

// 	return tex_x;
// }

// void	draw_vertical_line(t_draw_params *dp)
// {
// 	int	start;
// 	int	tex_y;
// 	int	*pixels;
// 	int	color;

// 	start = dp->draw_start;
// 	while (start <= dp->draw_end)
// 	{
// 		if (start >= 0 && start < SCREENHEIGHT && dp->i >= 0 && dp->i < SCREENWIDTH)
// 		{
// 			tex_y = (int)dp->r->tex_pos;
// 			if (tex_y < 0)
// 				tex_y = 0;
// 			if (tex_y >= dp->t->height)
// 				tex_y = dp->t->height - 1;

// 			pixels = (int *)dp->t->data;
// 			color = pixels[tex_y * (dp->t->line_len / 4) + dp->tex_x];
// 			buffer[start][dp->i] = color;
// 		}
// 		dp->r->tex_pos += dp->r->tex_step;
// 		++start;
// 	}
// }

// void	get_walls(t_ray *r, t_player *p, t_ori_tex *tex, int i)
// {
// 	t_texture		*t;
// 	t_draw_params	dp;
// 	int				tex_x;
// 	t_wall_calc		wc;

// 	wc.line_height = calc_draw_positions(r, &wc.draw_start, &wc.draw_end);
// 	calc_wall_hit(r, p);

// 	t = select_texture(r, tex);
// 	tex_x = calc_tex_mapping(r, t, wc.line_height, wc.draw_start);

// 	dp = (t_draw_params){r, t, tex_x, wc.draw_start, wc.draw_end, i};
// 	draw_vertical_line(&dp);
// }
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

// void	get_c_colored(t_ori_tex *tex)
// {
// 	int	x;
// 	int	y;
// 	int	half_h;

// 	x = 0;
// 	half_h = SCREENHEIGHT >> 1;
// 	while (x < SCREENWIDTH)
// 	{
// 		y = 0;
// 		while (y < half_h)
// 		{
// 			if (buffer[y][x] == 0)
// 				buffer[y][x] = get_color(tex->rgb_ceiling[0],
// 						tex->rgb_ceiling[1], tex->rgb_ceiling[2]);
// 			++y;
// 		}
// 		++x;
// 	}
// }

// void	get_f_colored(t_ori_tex *tex)
// {
// 	int	x;
// 	int	y;
// 	int	half_h;

// 	x = 0;
// 	half_h = SCREENHEIGHT >> 1;
// 	while (x < SCREENWIDTH)
// 	{
// 		y = half_h;
// 		while (y < SCREENHEIGHT)
// 		{
// 			if (buffer[y][x] == 0)
// 				buffer[y][x] = get_color(tex->rgb_floor[0],
// 						tex->rgb_floor[1], tex->rgb_floor[2]);
// 			++y;
// 		}
// 		++x;
// 	}
// }

// void	get_time(t_player *p)
// {
// 	p->old_time = p->time;
// 	p->time = get_timestamp();
// 	p->frame_time = p->time - p->old_time;
// 	p->move_speed = p->frame_time * 3.0;
// 	p->rot_speed = p->frame_time * 2.0;
// }

// void	upd_player_minimap(t_game *g)
// {
// 	g->minimap[(int)g->player->old_pos_y][(int)g->player->old_pos_x] = g->player->prev_tile;
// 	g->player->prev_tile = g->minimap[(int)g->player->pos_y][(int)g->player->pos_x];
// 	g->minimap[(int)g->player->pos_y][(int)g->player->pos_x]
// 	= get_player_marker(g->player);
// 	g->player->old_pos_y = g->player->pos_y;
// 	g->player->old_pos_x = g->player->pos_x;
// }


// //-----------------------------------------
// //-----------------------------------------

// void	clear_img_buffer(t_mlx *mlx)
// {
// 	int	i;
// 	int	size;

// 	i = 0;
// 	size = mlx->line_len * SCREENHEIGHT;

// 	while (i < size)
// 	{
// 		mlx->addr[i] = 0;
// 		++i;
// 	}
// }

// void	draw_floor_ceiling(t_ray *ray, t_player *player, t_ori_tex *tex)
// {
// 	int	i;

// 	i = 0;
// 	while (i < SCREENHEIGHT)
// 	{
// 		get_fc(ray, player, tex, i);
// 		++i;
// 	}
// }

// void	cast_rays(t_ray *ray, t_player *player, t_ori_tex *tex, t_game *g)
// {
// 	int	i;

// 	i = 0;
// 	while (i < SCREENWIDTH)
// 	{
// 		calc_camera(ray, player, i);
// 		calc_dda(ray, player);
// 		run_dda(ray, player, g);
// 		get_walls(ray, player, tex, i);
// 		++i;
// 	}
// }

// void	handle_hud(t_game *g)
// {
// 	if (!g->o_text->path_ceiling)
// 		get_c_colored(g->o_text);
// 	if (!g->o_text->path_floor)
// 		get_f_colored(g->o_text);

// 	if (g->lightsaber->weapon_state == 2)
// 		draw_attack_hud(g, g->lightsaber->weapon_frame);
// 	else
// 		draw_weapon_hud(g, g->lightsaber->weapon_frame);
// }

// void	clear_buffer(void)
// {
// 	int	i;
// 	int	x;

// 	i = 0;
// 	while (i < SCREENHEIGHT)
// 	{
// 		x = 0;
// 		while (x < SCREENWIDTH)
// 		{
// 			buffer[i][x] = 0;
// 			++x;
// 		}
// 		++i;
// 	}
// }

// void	calc_rays(t_mlx *mlx, t_ray *ray, t_player *player, t_game *g)
// {
// 	clear_img_buffer(mlx);

// 	draw_floor_ceiling(ray, player, g->o_text);
// 	cast_rays(ray, player, g->o_text, g);

// 	handle_hud(g);
// 	drawbuffer(g->mlx);

// 	clear_buffer();
// 	minimap(g);

// 	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
// }
//--------------------------------------------
//-------------------------------------------

// static void	handle_left_click(t_game *g)
// {
// 	if (g->lightsaber->weapon_state != 0)
// 		return ;

// 	g->player->kp_lc = 1;

// 	if (g->lightsaber->deployed == 0 || g->lightsaber->weapon_state == 1)
// 		return ;

// 	g->lightsaber->weapon_state = 2;
// 	g->lightsaber->weapon_frame = 1;
// 	g->lightsaber->deployed = 1;
// }

// static void	handle_right_click(t_game *g)
// {
// 	if (g->lightsaber->weapon_state != 0)
// 		return ;

// 	g->player->kp_rc = 1;

// 	if (g->lightsaber->deployed == 0)
// 	{
// 		g->lightsaber->weapon_state = 1;
// 		g->lightsaber->weapon_anim_timer = 0;
// 		g->lightsaber->deployed = 1;
// 	}
// 	else
// 	{
// 		g->lightsaber->weapon_state = 3;
// 		g->lightsaber->weapon_frame = 5;
// 		g->lightsaber->weapon_anim_timer = 0;
// 	}
// }

// int	mouse_press(int button, int x, int y, t_game *g)
// {
// 	(void)x;
// 	(void)y;

// 	if (button == 1)
// 		handle_left_click(g);
// 	else if (button == 3)
// 		handle_right_click(g);

// 	return (0);
// }

// int mouse_release(int button, int x, int y, t_game *g)
// {
// 	(void)x; 
// 	(void)y;

// 	if (button == 1)
// 		g->player->kp_lc = 0;
// 	if (button == 3)
// 		g->player->kp_rc = 0;
// 	return (0);
// }

// int	key_press(int key, t_game *g)
// {
// 	if (key == KEY_W)
// 		g->player->kp_w = 1;
// 	if (key == KEY_S)
// 		g->player->kp_s = 1;
// 	if (key == KEY_A)
// 		g->player->kp_a = 1;
// 	if (key == KEY_D)
// 		g->player->kp_d = 1;
// 	if (key == KEY_LEFT)
// 		g->player->kp_la = 1;
// 	if (key == KEY_RIGHT)
// 		g->player->kp_ra = 1;
// 	if (key == KEY_ESC)
// 	{
// 		free_project(g);
// 		exit(0);
// 	}
// 	return (0);
// }

// int	key_release(int key, t_game *g)
// {
// 	if (key == KEY_W)
// 		g->player->kp_w = 0;
// 	if (key == KEY_S)
// 		g->player->kp_s = 0;
// 	if (key == KEY_A)
// 		g->player->kp_a = 0;
// 	if (key == KEY_D)
// 		g->player->kp_d = 0;
// 	if (key == KEY_LEFT)
// 		g->player->kp_la = 0;
// 	if (key == KEY_RIGHT)
// 		g->player->kp_ra = 0;
// 	return (0);
// }

// int	mouse_move(int x, int y, t_game *g)
// {
// 	(void)y;
// 	if (g->warping)
// 	{
// 		g->warping = 0;
// 		return (0);
// 	}
// 	g->mouse_dx += x - g->center_x;
// 	g->warping = 1;
// 	mlx_mouse_move(g->mlx->mlx, g->mlx->win, g->center_x, g->center_y);
// 	return (0);
// }

// void	apply_mouse_rotation(t_game *g)
// {
// 	double	rot;
// 	double	old_dir_x;
// 	double	old_plane_x;

// 	if (g->mouse_dx == 0)
// 		return ;
// 	rot = g->mouse_dx * 0.002;
// 	old_dir_x = g->player->dir_x;
// 	g->player->dir_x = g->player->dir_x * cos(rot)
// 		- g->player->dir_y * sin(rot);
// 	g->player->dir_y = old_dir_x * sin(rot)
// 		+ g->player->dir_y * cos(rot);
// 	old_plane_x = g->player->plane_x;
// 	g->player->plane_x = g->player->plane_x * cos(rot)
// 		- g->player->plane_y * sin(rot);
// 	g->player->plane_y = old_plane_x * sin(rot)
// 		+ g->player->plane_y * cos(rot);
// 	g->mouse_dx = 0;
// }


//--------------------------------------
//-------------------------------------

// static int	move_forward(t_game *g)
// {
// 	t_player	*p;

// 	p = g->player;
// 	if (!p->kp_w)
// 		return (0);

// 	if (is_walkable_tile(g, (int)p->pos_y, (int)(p->pos_x + p->dir_x * p->move_speed)))
// 		p->pos_x += p->dir_x * p->move_speed;
// 	if (is_walkable_tile(g, (int)(p->pos_y + p->dir_y * p->move_speed), (int)p->pos_x))
// 		p->pos_y += p->dir_y * p->move_speed;

// 	return (1);
// }

// static int	move_backward(t_game *g)
// {
// 	t_player	*p;

// 	p = g->player;
// 	if (!p->kp_s)
// 		return (0);

// 	if (is_walkable_tile(g, (int)p->pos_y, (int)(p->pos_x - p->dir_x * p->move_speed)))
// 		p->pos_x -= p->dir_x * p->move_speed;
// 	if (is_walkable_tile(g, (int)(p->pos_y - p->dir_y * p->move_speed), (int)p->pos_x))
// 		p->pos_y -= p->dir_y * p->move_speed;

// 	return (1);
// }

// static int	move_right(t_game *g)
// {
// 	t_player	*p;

// 	p = g->player;

// 	if (!p->kp_d)
// 		return (0);

// 	if (is_walkable_tile(g, (int)(p->pos_y + p->dir_x * p->move_speed), (int)p->pos_x))
// 		p->pos_y += p->dir_x * p->move_speed;
// 	if (is_walkable_tile(g, (int)p->pos_y, (int)(p->pos_x - p->dir_y * p->move_speed)))
// 		p->pos_x -= p->dir_y * p->move_speed;

// 	return (1);
// }

// static int	move_left(t_game *g)
// {
// 	t_player	*p;

// 	p = g->player;

// 	if (!p->kp_a)
// 		return (0);

// 	if (is_walkable_tile(g, (int)(p->pos_y - p->dir_x * p->move_speed), (int)p->pos_x))
// 		p->pos_y -= p->dir_x * p->move_speed;
// 	if (is_walkable_tile(g, (int)p->pos_y, (int)(p->pos_x + p->dir_y * p->move_speed)))
// 		p->pos_x += p->dir_y * p->move_speed;

// 	return (1);
// }

// static int	handle_movement(t_game *g)
// {
// 	int	moved;

// 	moved = 0;

// 	if (move_forward(g))
// 		moved = 1;
// 	if (move_backward(g))
// 		moved = 1;
// 	if (move_right(g))
// 		moved = 1;
// 	if (move_left(g))
// 		moved = 1;

// 	return (moved);
// }

// static int	handle_rotation_keys(t_game *g)
// {
// 	int			moved;
// 	double		old_dir;
// 	double		old_plane;
// 	double		angle;
// 	t_player	*p;

// 	moved = 0;
// 	p = g->player;
// 	if (p->kp_ra || p->kp_la)
// 	{
// 		angle = (p->kp_ra) ? p->rot_speed : -p->rot_speed;

// 		old_dir = p->dir_x;
// 		p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
// 		p->dir_y = old_dir * sin(angle) + p->dir_y * cos(angle);

// 		old_plane = p->plane_x;
// 		p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
// 		p->plane_y = old_plane * sin(angle) + p->plane_y * cos(angle);

// 		moved = 1;
// 	}
// 	return (moved);
// }

// static int	handle_mouse_rotation(t_game *g)
// {
// 	if (g->mouse_dx != 0)
// 	{
// 		apply_mouse_rotation(g);
// 		return (1);
// 	}
// 	return (0);
// }

// static int	handle_weapons(t_game *g)
// {
// 	if (g->lightsaber->weapon_state != 0)
// 	{
// 		run_weapon_animation(g);
// 		return (1);
// 	}
// 	return (0);
// }

// int	handle_input(t_game *g)
// {
// 	int	moved;
// 	int	redraw;
// 	int	door_changed;

// 	moved = 0;
// 	redraw = 0;

// 	get_time(g->player);
// 	if (handle_movement(g))
// 		moved = 1;
// 	if (handle_rotation_keys(g))
// 		moved = 1;
// 	if (handle_mouse_rotation(g))
// 		moved = 1;
// 	if (handle_weapons(g))
// 		redraw = 1;
// 	door_changed = update_doors(g);
// 	if (moved)
// 		upd_player_minimap(g);
// 	if (moved || door_changed || redraw)
// 		calc_rays(g->mlx, g->ray, g->player, g);
// 	return (0);
// }

// void	start(t_game *game)
// {
// 	mlx_mouse_hide(game->mlx->mlx, game->mlx->win);
// 	game->minimap = copy_map(game->map, 0, game->map_h);
// 	game->map[(int)game->player->pos_y][(int)game->player->pos_x] = '0';
// 	game->player->prev_tile = '0';
// 	game->center_x = SCREENWIDTH / 2;
// 	game->center_y = SCREENHEIGHT / 2;
// 	game->mouse_dx = 0;
// 	game->warping = 0;
// 	game->player->kp_lc = 0;
// 	game->player->kp_rc = 0;
// 	game->door = NULL;
// 	game->door = get_door_coords(game, game->map);
// 	mlx_loop_hook(game->mlx->mlx, handle_input, game);
// 	get_guns_sprite(game);
// 	get_weapon_attack_sprite(game);
// 	calc_rays(game->mlx, game->ray, game->player, game);
// 	mlx_hook(game->mlx->win, 2, 1L << 0, key_press, game);
// 	mlx_hook(game->mlx->win, 3, 1L << 1, key_release, game);
// 	mlx_hook(game->mlx->win, 6, 1L << 6, mouse_move, game);
// 	mlx_hook(game->mlx->win, 4, 1L << 2, mouse_press, game);
// 	mlx_hook(game->mlx->win, 5, 1L << 3, mouse_release, game);
// 	mlx_mouse_move(game->mlx->mlx, game->mlx->win, game->center_x, game->center_y);
// }
