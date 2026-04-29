/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:26:31 by hgutterr          #+#    #+#             */
/*   Updated: 2026/04/23 17:38:06 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>
# include "../mlx/mlx.h"

# define screenWidth	1520
# define screenHeight	980
# define KEY_W			119
# define KEY_S			115
# define KEY_A			97
# define KEY_D			100
# define KEY_LEFT 		65361
# define KEY_RIGHT 		65363
# define KEY_ESC		65307

typedef struct s_door
{
	double	pos_x;
	double	pos_y;
	double	open_pct;
	int		opening;
}			t_door;


typedef struct s_elements_var
{
	char	*line;
	int 	elements_found;
	int 	opened;
	int 	f_c_element;
	int		door_found;
}	t_ele_var;

typedef struct s_texture
{
	void	*img_ptr;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;


typedef struct s_player
{
	double	pos_y; // y/2
	double	pos_x; // x/2
	double	pos_z; // where the camera "is"
	char	prev_tile;
	double	old_pos_y;
	double	old_pos_x;
	double	dir_y; // -1=N 1=S
	double	dir_x; // -1=W 1=E
	double	row_dis;
	double	old_dir_x;
	double	plane_y; // FOV is 2 * atan(0.66/1.0)=66°
	double	plane_x;
	double	old_plane_x;
	double	time;
	double	old_time;
	double	frame_time;
	double	move_speed;
	double	rot_speed;
	int		kp_w;
	int		kp_s;
	int		kp_a;
	int		kp_d;
	int		kp_la;
	int		kp_ra;
	int		kp_lc;
}	t_player;

typedef struct s_gun
{
	t_texture	**tex_arr;
}			t_gun;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_x_l;
	double	ray_dir_x_r;
	double	ray_dir_y;
	double	ray_dir_y_l;
	double	ray_dir_y_r;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	double	wall_hit_pos_x;
	int		door_side;
	double	tex_step;
	double	tex_pos;
	double	floor_step_x;
	double	floor_step_y;
	double	floor_x;
	double	floor_y;
}	t_ray;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_mlx;

typedef struct s_ori_tex
{
	t_texture	*tex_north;
	t_texture	*tex_south;
	t_texture	*tex_east;
	t_texture	*tex_west;
	t_texture	*tex_floor;
	t_texture	*tex_ceiling;
	t_texture	*tex_door;
	t_texture	*tex_one;
	t_texture	*tex_two;
	t_texture	*tex_three;
	t_texture	*tex_four;
	t_texture	*tex_five;

	char	*path_north;
	char	*path_south;
	char	*path_east;
	char	*path_west;
	char	*path_floor;
	char	*path_ceiling;
	char	*path_door;
	char	*path_one;
	char	*path_two;
	char	*path_three;
	char	*path_four;
	char	*path_five;

	int		rgb_floor[3];
	int		rgb_ceiling[3];
}	t_ori_tex;

typedef struct s_game
{
	t_mlx		*mlx;
	t_player	*player;
	t_ray		*ray;
	t_texture	*txt;
	t_ori_tex	*o_text;
	t_door		**door;
	t_gun		*pistol1;
	t_gun		*pistol2;
	char		**cub;
	char		**elements_file;
	char		**map;
	char		**minimap;
	int			map_h;
	int			map_w;
	int			sp;
	int			mouse_x;
	int			mouse_y;
	int			old_mx;
	int			center_x;
	int			center_y;
	int			mouse_dx;
	int			warping;
}	t_game;

# include <cub3d_exec.h>
# include <cub3d_parser.h>

#endif
