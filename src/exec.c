/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:29:02 by hgutterr          #+#    #+#             */
/*   Updated: 2026/04/29 14:35:42 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int buffer[screenHeight][screenWidth];

int		background(int color)
{
	if (color != 0x5B6EE1
		&& color != 0x6C77D1
		&& color != 0x5C6CDC
		&& color != 0x5667CF
		&& color != 0x515FB8
		&& color != 0x4C5AB4
		&& color != 0x4B5695
		&& color != 0x3B4584
		&& color != 0x394171
		&& color != 0x3B4584
		&& color != 0x706B8D
		&& color != 0x4D5270
		&& color != 0x6B4683 
		&& color != 0x6D4985
		&& color != 0x674A8D
		&& color != 0x364080
		&& color != 0x6A4A8B
		&& color != 0x754C87
		&& color != 0x6A4A8B
		&& color != 0x754C87
		&& color != 0x78508A
		&& color != 0x664D94
		&& color != 0x6A4E92
		&& color != 0x654F98
		&& color != 0x6C5095
		&& color != 0x65519D
		&& color != 0x6A529B
		&& color != 0x745395
		&& color != 0x535CA4
		&& color != 0x6555A4
		&& color != 0x6B58A7
		&& color != 0x6357AA
		&& color != 0x6359AD
		&& color != 0x715BA6
		&& color != 0x625BB4
		&& color != 0x6A5DB3
		&& color != 0x615EBB
		&& color != 0x6B61B7
		&& color != 0x6360BE
		&& color != 0x5F62C4
		&& color != 0x5364CA
		&& color != 0x5E65CC
		&& color != 0x5D67D0
		&& color != 0x5D69D4
		&& color != 0x5C6AD6
		&& color != 0x5C6CDB
		&& color != 0x5B6DDD
		&& color != 0x5F71DD
		&& color != 0x6162C2
		&& color != 0x6266CA
		&& color != 0x7077C6
		&& color != 0x6069D2
		&& color != 0x5B6EE0
		&& color != 0x5B6EE1
		&& color != 0x6678E3
		&& color != 0x78416C
		&& color != 0x6E4175
		&& color != 0x6E447B
		&& color != 0x734273
		&& color != 0x784677
		&& color != 0x72457B)
		return (0);
	return (1);
}

void	get_guns_sprite(t_game *g)
{
	int i = 0;
	g->pistol1 = malloc(sizeof(t_gun));
	if (!g->pistol1)
		return ;
	g->pistol1->tex_arr = malloc(sizeof(t_texture *) * 6);
	if (!g->pistol1->tex_arr)
		return ;
	while (i < 5)
	{
		g->pistol1->tex_arr[i] = malloc(sizeof(t_texture));
		if (!g->pistol1->tex_arr[i])
			return ;
		++i;
	}
	load_texture(g->mlx, &g->pistol1->tex_arr[0], "./assets/pistol1_0.xpm");
	load_texture(g->mlx, &g->pistol1->tex_arr[1], "./assets/pistol1_1.xpm");
	load_texture(g->mlx, &g->pistol1->tex_arr[2], "./assets/pistol1_2.xpm");
	load_texture(g->mlx, &g->pistol1->tex_arr[3], "./assets/pistol1_3.xpm");
	load_texture(g->mlx, &g->pistol1->tex_arr[4], "./assets/pistol1_3.xpm");
	i = 0;
	while(i < 5)
	{
		if(!g->pistol1->tex_arr[i])
			printf("coc\n");
		printf("text[%d] loaded\n", i);
		++i;
	}
}

void draw_gun_hud(t_game *g, int i)
{
    t_texture    *tex;
    int          start_x;
    int          start_y;
    int          x;
    int          y;
    unsigned int color;
    unsigned int *pixels;

    if (!g->pistol1 || !g->pistol1->tex_arr[i])
        return;
    tex = g->pistol1->tex_arr[i];
	//printf("Value of i in draw_gun_hud: %d\n", i);
    start_x = (screenWidth - tex->width) - (screenWidth / 7);
    start_y = screenHeight - tex->height + 50;
    pixels = (unsigned int *)tex->data;
    y = 0;
    while (y < tex->height)
    {
        x = 0;
        while (x < tex->width)
        {
            int bx = start_x + x;
            int by = start_y + y;

            color = pixels[y * (tex->line_len / 4) + x];
            if (bx >= 0 && bx < screenWidth && by >= 0 && by < screenHeight
                && color != 0)
            {
				if (!background(color))
	                buffer[by][bx] = color;
            }
            ++x;
        }
        ++y;
    }
}

void run_gun_animation(t_game *g)
{
	if (g->player->gun_frame == 0)
		return ;
	g->player->gun_anim_timer += g->player->frame_time;
	if (g->player->gun_anim_timer >= 0.6)
	{
		g->player->gun_anim_timer -= 0.6;
		g->player->gun_frame++;
		if (g->player->gun_frame >= 5)
		{
			g->player->gun_frame = 0;
			g->player->gun_anim_timer = 0;
		}
	}
}

t_door	*find_door(t_game *g, int y, int x)
{
	int	i;

	if (!g->door)
		return (NULL);
	i = 0;
	while (g->door[i])
	{
		if ((int)g->door[i]->pos_y == y && (int)g->door[i]->pos_x == x)
			return (g->door[i]);
		++i;
	}
	return (NULL);
}

int	is_player_adjacent_to_door(t_game *g, t_door *door)
{
	int	player_y;
	int	player_x;
	int	door_y;
	int	door_x;
	int	diff_y;
	int	diff_x;

	player_y = (int)g->player->pos_y;
	player_x = (int)g->player->pos_x;
	door_y = (int)door->pos_y;
	door_x = (int)door->pos_x;
	diff_y = player_y - door_y;
	diff_x = player_x - door_x;
	if ((diff_y == 0 && diff_x == 0)
		|| (diff_y == 1 && diff_x == 0)
		|| (diff_y == -1 && diff_x == 0)
		|| (diff_y == 0 && diff_x == 1)
		|| (diff_y == 0 && diff_x == -1))
		return (1);
	return (0);
}

int	update_doors(t_game *g)
{
	int		i;
	int		changed;
	double	old_pct;
	double	speed;

	if (!g->door)
		return (0);
	i = 0;
	changed = 0;
	speed = g->player->frame_time * 1.5;
	while (g->door[i])
	{
		old_pct = g->door[i]->open_pct;
		g->door[i]->opening = is_player_adjacent_to_door(g, g->door[i]);
		if (g->door[i]->opening)
			g->door[i]->open_pct += speed;
		else
			g->door[i]->open_pct -= speed;
		if (g->door[i]->open_pct < 0.0)
			g->door[i]->open_pct = 0.0;
		if (g->door[i]->open_pct > 1.0)
			g->door[i]->open_pct = 1.0;
		if (fabs(g->door[i]->open_pct - old_pct) > 0.0001)
			changed = 1;
		++i;
	}
	return (changed);
}

int	is_walkable_tile(t_game *g, int y, int x)
{
	t_door	*door;

	if (!g->map[y] || !g->map[y][x])
		return (0);
	if (g->map[y][x] == '0')
		return (1);
	if (g->map[y][x] != 'D')
		return (0);
	door = find_door(g, y, x);
	if (!door)
		return (0);
	return (door->open_pct >= 0.9);
}

char	get_player_marker(t_player *player)
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
	int	y;
	int	x;

	y = 0;
	while (y < screenHeight)
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
	int	i;
	int	j;

	i = y * g->sp;
	while (i < y * g->sp + g->sp)
	{
		j = x * g->sp;
		while (j < x * g->sp + g->sp)
		{
			put_pixel(g->mlx, j, i, color);
			++j;
		}
		++i;
	}
}

int	get_color(int r, int g, int b)
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

void	init_player(t_player *p)
{
	p->kp_w = 0;
	p->kp_s = 0;
	p->kp_a = 0;
	p->kp_d = 0;

	p->old_pos_x = p->pos_x;
	p->old_pos_y = p->pos_y;

	p->plane_y = p->dir_x * 0.66;
	p->plane_x = -p->dir_y * 0.66;

	p->time = get_timestamp();
	p->old_time = p->time;
	p->frame_time = 0;

	p->move_speed = 0;
	p->rot_speed = 0;
}

void	calc_camera(t_ray *r, t_player *p, int i)
{
	r->camera_x = 2 * i / (double)screenWidth - 1;
	r->ray_dir_y = p->dir_y + p->plane_y * r->camera_x;
	r->ray_dir_x = p->dir_x + p->plane_x * r->camera_x;
}

void	calc_dda(t_ray *r, t_player *p)
{
	r->map_x = (int)p->pos_x;
	r->map_y = (int)p->pos_y;

	if (r->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1 / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1 / r->ray_dir_y);
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = ((p->pos_x - r->map_x) * r->delta_dist_x);
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = ((r->map_x + 1.0 - p->pos_x) * r->delta_dist_x);
	}
	if (r->ray_dir_y < 0)
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

int	hit_door_plane(t_ray *r, t_player *p, t_game *g)
{
	double	door_plane;
	double	hit_pos;
	double	local_pos;
	t_door	*door;

	door = find_door(g, r->map_y, r->map_x);
	if (!door || door->open_pct >= 1.0)
		return (0);
	r->door_side = get_door_side(g->map, r->map_y, r->map_x);
	if (r->door_side == 0)
	{
		if (r->ray_dir_x == 0)
			return (0);
		door_plane = r->map_x + 0.5;
		r->perp_wall_dist = (door_plane - p->pos_x) / r->ray_dir_x;
		hit_pos = p->pos_y + r->perp_wall_dist * r->ray_dir_y;
		local_pos = hit_pos - r->map_y;
		if (r->perp_wall_dist > 0 && local_pos >= 0.0
			&& local_pos <= (1.0 - door->open_pct))
		{
			r->wall_hit_pos_x = local_pos + door->open_pct;
			return (1);
		}
	}
	else
	{
		if (r->ray_dir_y == 0)
			return (0);
		door_plane = r->map_y + 0.5;
		r->perp_wall_dist = (door_plane - p->pos_y) / r->ray_dir_y;
		hit_pos = p->pos_x + r->perp_wall_dist * r->ray_dir_x;
		local_pos = hit_pos - r->map_x;
		if (r->perp_wall_dist > 0 && local_pos >= 0.0
			&& local_pos <= (1.0 - door->open_pct))
		{
			r->wall_hit_pos_x = local_pos + door->open_pct;
			return (1);
		}
	}
	return (0);
}

int	get_door_count(char **map)
{
	int	y;
	int	x;
	int	doors;

	if (!map || !map[0])
		return (0);
	y = 0;
	doors = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'D')
				++doors;
			++x;
		}
		++y;
	}
	return (doors);
}

void	fill_door_cords(t_door **door, char **map)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'D')
			{
				door[i]->pos_y = y;
				door[i]->pos_x = x;
				door[i]->open_pct = 0.0;
				door[i]->opening = 0;
				++i;
			}
			++x;
		}
		++y;
	}
}

t_door	**get_door_cords(char **map)
{
	t_door	**door;
	int		i;
	int		door_count;

	i = 0;
	door_count = get_door_count(map);
	door = malloc(sizeof(t_door *) * (door_count + 1));
	if (!door)
		return (NULL);
	while (i < door_count)
	{
		door[i] = malloc(sizeof(t_door));
		if (!door[i])
		{
			while (--i)
				free(door[i]);
			return (NULL);
		}
		++i;
	}
	door[door_count] = NULL;
	fill_door_cords(door, map);
	return (door);
}

void	run_dda(t_ray *r, t_player *p, t_game *g)
{
	r->hit = 0;
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
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
		if (g->map[r->map_y][r->map_x] == 'D')
		{
			if (hit_door_plane(r, p, g))
			{
				r->hit = 2;
				r->side = r->door_side;
			}
		}
		else if (g->map[r->map_y][r->map_x] != '0')
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
	int		pos;
	int		j;
	int		tex_x;
	int		tex_y;
	int		color;

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

		if (t->path_ceiling)
		{
			int *pixels = (int *)t->tex_ceiling->data;
			tex_x = (int)(t->tex_ceiling->width * frac_x);
			tex_y = (int)(t->tex_ceiling->height * frac_y);
			color = pixels[tex_y * (t->tex_ceiling->line_len / 4) + tex_x];
			buffer[screenHeight - i - 1][j] = color;
		}
		if (t->path_floor)
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
	t_texture	*t;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	int			tex_y;
	int			start;
	int			end;
	int			color;

	t = NULL;
	if (r->perp_wall_dist <= 0)
		r->perp_wall_dist = 0.1;
	line_height = (int)(screenHeight / r->perp_wall_dist);
	draw_start = ((-1 * line_height) >> 1) + (screenHeight >> 1);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (line_height >> 1) + (screenHeight >> 1);
	if (draw_end >= screenHeight)
		draw_end = screenHeight - 1;
	if (r->hit != 2 && r->side == 0)
		r->wall_hit_pos_x = p->pos_y + r->perp_wall_dist * r->ray_dir_y;
	else if (r->hit != 2)
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
	tex_x = (int)(r->wall_hit_pos_x * (1.0 * t->width));
	if (r->side == 0 && r->ray_dir_x > 0)
		tex_x = t->width - tex_x - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		tex_x = t->width - tex_x - 1;
	start = draw_start;
	end = draw_end;
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
	int	half_h;

	x = 0;
	half_h = screenHeight >> 1;
	while (x < screenWidth)
	{
		y = 0;
		while (y < half_h)
		{
			if (buffer[y][x] == 0)
				buffer[y][x] = get_color(tex->rgb_ceiling[0],
						tex->rgb_ceiling[1], tex->rgb_ceiling[2]);
			++y;
		}
		++x;
	}
}

void	get_f_colored(t_ori_tex *tex)
{
	int	x;
	int	y;
	int	half_h;

	x = 0;
	half_h = screenHeight >> 1;
	while (x < screenWidth)
	{
		y = half_h;
		while (y < screenHeight)
		{
			if (buffer[y][x] == 0)
				buffer[y][x] = get_color(tex->rgb_floor[0],
						tex->rgb_floor[1], tex->rgb_floor[2]);
			++y;
		}
		++x;
	}
}

void	get_time(t_player *p)
{
	p->old_time = p->time;
	p->time = get_timestamp();
	p->frame_time = p->time - p->old_time;
	p->move_speed = p->frame_time * 3.0;
	p->rot_speed = p->frame_time * 2.0;
}

void	upd_player_minimap(t_game *g)
{
	g->minimap[(int)g->player->old_pos_y][(int)g->player->old_pos_x] = g->player->prev_tile;
	g->player->prev_tile = g->minimap[(int)g->player->pos_y][(int)g->player->pos_x];
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

void	calc_rays(t_mlx *mlx, t_ray *ray, t_player *player, t_game *g)
{
	int	i;
	int	x;
	int	size;

	i = 0;
	size = mlx->line_len * screenHeight;
	while (i < size)
	{
		mlx->addr[i] = 0;
		++i;
	}
	i = 0;
	while (i < screenHeight)
	{
		get_fc(ray, player, g->o_text, i);
		++i;
	}
	i = 0;
	while (i < screenWidth)
	{
		calc_camera(ray, player, i);
		calc_dda(ray, player);
		run_dda(ray, player, g);
		get_walls(ray, player, g->o_text, i);
		++i;
	}
	if (!g->o_text->path_ceiling)
		get_c_colored(g->o_text);
	if (!g->o_text->path_floor)
		get_f_colored(g->o_text);
	draw_gun_hud(g, g->player->gun_frame);
	drawbuffer(g->mlx);
	i = 0;
	while (i < screenHeight)
	{
		x = 0;
		while (x < screenWidth)
		{
			buffer[i][x] = 0;
			++x;
		}
		++i;
	}
	minimap(g);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int mouse_press(int button, int x, int y, t_game *g)
{
    (void)x; 
    (void)y;

if (button == 1)
    {
        g->player->kp_lc = 1;
        if (g->player->gun_frame == 0)
        {
            g->player->gun_frame = 1;
            g->player->gun_anim_timer = 0;
        }
    }
    return (0);
}

int mouse_release(int button, int x, int y, t_game *g)
{
    (void)x; 
    (void)y;

    if (button == 1)
    {
		printf("Left click release detected\n");
        g->player->kp_lc = 0;
    }
    return (0);
}

int	key_press(int key, t_game *g)
{
	if (key == KEY_W)
		g->player->kp_w = 1;
	if (key == KEY_S)
		g->player->kp_s = 1;
	if (key == KEY_A)
		g->player->kp_a = 1;
	if (key == KEY_D)
		g->player->kp_d = 1;
	if (key == KEY_LEFT)
		g->player->kp_la = 1;
	if (key == KEY_RIGHT)
		g->player->kp_ra = 1;
	if (key == KEY_ESC)
		exit(0);
	return (0);
}

int	key_release(int key, t_game *g)
{
	if (key == KEY_W)
		g->player->kp_w = 0;
	if (key == KEY_S)
		g->player->kp_s = 0;
	if (key == KEY_A)
		g->player->kp_a = 0;
	if (key == KEY_D)
		g->player->kp_d = 0;
	if (key == KEY_LEFT)
		g->player->kp_la = 0;
	if (key == KEY_RIGHT)
		g->player->kp_ra = 0;
	return (0);
}

int	mouse_move(int x, int y, t_game *g)
{
	(void)y;
	if (g->warping)
	{
		g->warping = 0;
		return (0);
	}
	g->mouse_dx += x - g->center_x;
	g->warping = 1;
	mlx_mouse_move(g->mlx->mlx, g->mlx->win, g->center_x, g->center_y);
	return (0);
}

void	apply_mouse_rotation(t_game *g)
{
	double	rot;
	double	old_dir_x;
	double	old_plane_x;

	if (g->mouse_dx == 0)
		return ;
	rot = g->mouse_dx * 0.002;
	old_dir_x = g->player->dir_x;
	g->player->dir_x = g->player->dir_x * cos(rot)
		- g->player->dir_y * sin(rot);
	g->player->dir_y = old_dir_x * sin(rot)
		+ g->player->dir_y * cos(rot);
	old_plane_x = g->player->plane_x;
	g->player->plane_x = g->player->plane_x * cos(rot)
		- g->player->plane_y * sin(rot);
	g->player->plane_y = old_plane_x * sin(rot)
		+ g->player->plane_y * cos(rot);
	g->mouse_dx = 0;
}

int	handle_input(t_game *g)
{
	int	moved;
	int	door_changed;
	int	redraw;

	moved = 0;
	redraw = 0;
	get_time(g->player);
	if (g->player->kp_w)
	{
		if (is_walkable_tile(g, (int)g->player->pos_y,
				(int)(g->player->pos_x + (g->player->dir_x
					* g->player->move_speed))))
			g->player->pos_x += g->player->dir_x * g->player->move_speed;
		if (is_walkable_tile(g,
				(int)(g->player->pos_y + (g->player->dir_y
					* g->player->move_speed)), (int)g->player->pos_x))
			g->player->pos_y += g->player->dir_y * g->player->move_speed;
		moved = 1;
	}
	if (g->player->kp_s)
	{
		if (is_walkable_tile(g, (int)g->player->pos_y,
				(int)(g->player->pos_x - g->player->dir_x
					* g->player->move_speed)))
			g->player->pos_x -= g->player->dir_x * g->player->move_speed;
		if (is_walkable_tile(g,
				(int)(g->player->pos_y - g->player->dir_y
					* g->player->move_speed), (int)g->player->pos_x))
			g->player->pos_y -= g->player->dir_y * g->player->move_speed;
		moved = 1;
	}
	if (g->player->kp_d)
	{
		if (is_walkable_tile(g,
				(int)(g->player->pos_y + g->player->dir_x
					* g->player->move_speed), (int)g->player->pos_x))
			g->player->pos_y += g->player->dir_x * g->player->move_speed;
		if (is_walkable_tile(g, (int)g->player->pos_y,
				(int)(g->player->pos_x - g->player->dir_y
					* g->player->move_speed)))
			g->player->pos_x -= g->player->dir_y * g->player->move_speed;
		moved = 1;
	}
	if (g->player->kp_a)
	{
		if (is_walkable_tile(g,
				(int)(g->player->pos_y - g->player->dir_x
					* g->player->move_speed), (int)g->player->pos_x))
			g->player->pos_y -= g->player->dir_x * g->player->move_speed;
		if (is_walkable_tile(g, (int)g->player->pos_y,
				(int)(g->player->pos_x + g->player->dir_y
					* g->player->move_speed)))
			g->player->pos_x += g->player->dir_y * g->player->move_speed;
		moved = 1;
	}
	if (g->player->kp_ra)
	{
		g->player->old_dir_x = g->player->dir_x;
		g->player->dir_x = g->player->dir_x * cos(g->player->rot_speed) - g->player->dir_y * sin(g->player->rot_speed);
		g->player->dir_y = g->player->old_dir_x * sin(g->player->rot_speed) + g->player->dir_y * cos(g->player->rot_speed);
		g->player->old_plane_x = g->player->plane_x;
		g->player->plane_x = g->player->plane_x * cos(g->player->rot_speed) - g->player->plane_y * sin(g->player->rot_speed);
		g->player->plane_y = g->player->old_plane_x * sin(g->player->rot_speed) + g->player->plane_y * cos(g->player->rot_speed);
		moved = 1;
	}
	if (g->player->kp_la)
	{
		g->player->old_dir_x = g->player->dir_x;
		g->player->dir_x = g->player->dir_x * cos(-g->player->rot_speed) - g->player->dir_y * sin(-g->player->rot_speed);
		g->player->dir_y = g->player->old_dir_x * sin(-g->player->rot_speed) + g->player->dir_y * cos(-g->player->rot_speed);
		g->player->old_plane_x = g->player->plane_x;
		g->player->plane_x = g->player->plane_x * cos(-g->player->rot_speed) - g->player->plane_y * sin(-g->player->rot_speed);
		g->player->plane_y = g->player->old_plane_x * sin(-g->player->rot_speed) + g->player->plane_y * cos(-g->player->rot_speed);
		moved = 1;
	}
	if (g->mouse_dx != 0)
	{
		apply_mouse_rotation(g);
		moved = 1;
	}
	if (g->player->gun_frame != 0)
	{
		run_gun_animation(g);
		redraw = 1;
	}
	door_changed = update_doors(g);
	if (moved)
		upd_player_minimap(g);
	if (moved || door_changed || redraw)
		calc_rays(g->mlx, g->ray, g->player, g);
	return (0);
}

void	start(t_game *game)
{
	mlx_mouse_hide(game->mlx->mlx, game->mlx->win);
	game->minimap = copy_map(game->map, 0, game->map_h);
	game->map[(int)game->player->pos_y][(int)game->player->pos_x] = '0';
	game->player->prev_tile = '0';
	game->center_x = screenWidth / 2;
	game->center_y = screenHeight / 2;
	game->mouse_dx = 0;
	game->warping = 0;
	game->player->kp_lc = 0;
	game->player->gun_frame = 0;
	game->player->gun_anim_timer = 0;
	mlx_hook(game->mlx->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx->win, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->mlx->win, 4, 1L << 2, mouse_press, game);
	mlx_hook(game->mlx->win, 5, 1L << 3, mouse_release, game);
	mlx_mouse_move(game->mlx->mlx, game->mlx->win, game->center_x, game->center_y);
	game->door = NULL;
	game->door = get_door_cords(game->map);
	mlx_loop_hook(game->mlx->mlx, handle_input, game);
	get_guns_sprite(game);
	calc_rays(game->mlx, game->ray, game->player, game);
}
