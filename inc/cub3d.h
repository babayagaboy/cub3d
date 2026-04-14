/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:26:31 by hgutterr          #+#    #+#             */
/*   Updated: 2026/04/13 17:36:15 by hgutterr         ###   ########.fr       */
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

# define mapWidth		24
# define mapHeight		24
# define screenWidth	1040
# define screenHeight	980
# define KEY_UP			119
# define KEY_DOWN		115
# define KEY_LEFT		97
# define KEY_RIGHT		100
# define KEY_ESC		65307


typedef struct s_player
{
	double	pos_y; // y/2
	double	pos_x; // x/2
	double	dir_y; // -1=N 1=S
	double	dir_x; // -1=W 1=E
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

}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
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

typedef struct s_game
{
	t_mlx		*mlx;
	t_player	*player;
	t_ray		*ray;
	char		**cub;
	char		**elements_file;
	char		**map;
}	t_game;

# include <cub3d_exec.h>
# include <cub3d_parser.h>

#endif
