/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_proto.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:15:59 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 20:28:37 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PROTO_H
# define CUB3D_PROTO_H

# include <cub3d.h>

typedef struct s_door			t_door;
typedef struct s_elements_var	t_ele_var;
typedef struct s_texture		t_texture;
typedef struct s_player			t_player;
typedef struct s_weapon			t_weapon;
typedef struct s_ray			t_ray;
typedef struct s_mlx			t_mlx;
typedef struct s_ori_tex		t_ori_tex;
typedef struct s_game			t_game;
typedef struct s_draw_params	t_draw_params;
typedef struct s_wall_calc		t_wall_calc;
typedef struct s_weapon_hud		t_weapon_hud;
typedef struct s_attack_hud		t_attack_hud;

void		free_int_arr(int **arr, int i);
void		free_char_arr(char **arr, int i);
void		free_memory(char **arr);
void		fmi(int **arr);
void		free_project(t_game *g);
void		free_t_texture(t_texture *tex, t_mlx *mlx, char *path);
void		free_weapon(t_weapon *weapon, t_mlx *mlx);
void		free_weapon_attk(t_weapon *weapon, t_mlx *mlx);
void		free_texture_pack(t_game *g);

int			check_rbg(char *str, int *arr);
void		choose_corect_path(char *line, int value, t_ori_tex *tex);
int			handle_texture(char *line, int value,
				t_ele_var *vars, char **tex_path);
int			handle_floor_ceiling(char *line, int value,
				t_ele_var *vars, t_ori_tex *tex);
int			check_elements(char **elements, t_ori_tex *tex, t_ele_var *vars);
void		process_element_line(char *line, t_ele_var *vars, t_ori_tex *tex);

int			*get_player_coords(char **map);
void		get_player_orientation(char player_orientation, t_player *p);
int			check_walls(char **map, int y, int x);
int			check_map_borders(char **map, t_game *g);
int			check_map_interior(char **map, t_ele_var *vars);
int			check_doors(char **map, int y, int x);
int			check_walls_doors(char **map, int y, int x);
int			is_wall(char c);
int			is_player(char c);
int			check_map(char **map, t_player *p, t_game *g, t_ele_var *vars);

int			calc_clean_size(char **splited);
void		copy_cleaned(char **splited, char *cleaned);
char		*looksmax_string(char *str);

int			f_c_type(char *str);
int			is_numeric_str(char *str);
int			validate_rgb_values(char **splited, int *arr);

int			count_elements(char **cub, int y, int *door_found);
int			process_line(char *line, char **elements_file, int i, t_ele_var *v);
char		**fill_elements(char **cub, int *y, int count, t_ele_var *v);
char		**get_elements(char **cub, int *y, t_ele_var *vars);

int			get_map_bounds(char **cub, int *y);
char		**copy_map(char **cub, int start, int count);
char		**get_map(char **cub, int *y, t_game *g);

int			find_player(char **map, int *coord);
char		*ft_findspace(char *str);

char		*read_into_buffer(char *file);
int			count_lines(char *buff, int size);
char		*extract_line(char *buff, int *j);
char		**split_lines(char *buff, int count);
char		**read_file(char *file);

int			parser(int argc, char *argv[], t_game *g);
int			validate_args(int argc, char *argv[]);
int			load_cub_file(t_game *g, char *file);
int			load_elements_and_map(t_game *g, t_ele_var *vars);
void		print_debug(t_game *g);
void		free_all(t_game *g);
void		free_memory(char **arr);

int			get_textures(t_mlx *mlx, t_ori_tex *tex);
int			load_texture(t_mlx *mlx, t_texture **tex_d, char *path);

void		get_guns_sprite(t_game *g);
void		get_weapon_attack_sprite(t_game *g);

int			update_weapon_timer_and_frame(t_game *g);
void		handle_weapon_state_1(t_game *g);
void		handle_weapon_state_2(t_game *g);
void		handle_weapon_state_3(t_game *g);
void		run_weapon_animation(t_game *g);

void		put_square(int y, int x, int color, t_game *g);
void		put_pixel(t_mlx *mlx, int x, int y, int color);
void		minimap(t_game *g);

int			hit_door_plane(t_ray *r, t_player *p, t_game *g);
int			get_door_side(char **map, int y, int x);
t_door		*find_door(t_game *g, int y, int x);
int			hit_door_plane_x(t_ray *r, t_player *p, t_door *door);
int			hit_door_plane_y(t_ray *r, t_player *p, t_door *door);
void		calc_perp_wall_dist(t_ray *r);
void		step_dda(t_ray *r, t_player *p, t_game *g);
void		calc_dda(t_ray *r, t_player *p);
void		calc_dda_axis_y(t_ray *r, t_player *p);
void		calc_dda_axis_x(t_ray *r, t_player *p);

int			ft_isdigit(int c);
int			is_walkable_tile(t_game *g, int y, int x);
int			get_color(int r, int g, int b);
int			init_buffer(t_game *g);
int			malloc_structs(t_game **game);
void		get_fc(t_game *g, t_player *p, t_ori_tex *t, int i);
int			handle_path(char *line, int value, t_ori_tex *tex);
char		*get_lightsaber_attack_texture_path(int i);
int			init_lightsaber_attack_struct(t_game *g);
int			load_lightsaber_attack_textures(t_game *g);
char		*get_lightsaber_texture_path(int i);
int			init_lightsaber_struct(t_game *g);
int			load_lightsaber_textures(t_game *g);
int			calc_tex_mapping(t_ray *r, t_texture *t,
				int line_height, int draw_start);
t_texture	*select_texture(t_ray *r, t_ori_tex *tex);
void		get_attack_hud_start_pos(t_texture *tex,
				float scale, int *start_x, int *start_y);
void		draw_attack_hud_row(t_attack_hud *hud, t_game *g, int y);
void		draw_attack_hud_pixels(t_attack_hud *hud, t_game *g);
void		draw_attack_hud(t_game *g, int i);
void		get_weapon_hud_start_pos(t_texture *tex,
				float scale, int *start_x, int *start_y);
void		draw_weapon_hud_row(t_weapon_hud *hud, t_game *g, int y);
void		draw_weapon_hud_pixels(t_weapon_hud *hud, t_game *g);
void		draw_weapon_hud(t_game *g, int i);
void		handle_hud(t_game *g);
void		drawbuffer(t_mlx *mlx, t_game *g);
void		draw_vertical_line(t_draw_params *dp, t_game *g);
void		clear_buffer(t_game *g);
void		run_dda(t_ray *r, t_player *p, t_game *g);
void		calc_camera(t_ray *r, t_player *p, int i);
void		upd_player_minimap(t_game *g);
void		clear_img_buffer(t_mlx *mlx);
void		get_player_door_diff(t_player *player, t_door *door,
				int *diff_x, int *diff_y);
int			check_adjacent(int diff_x, int diff_y);
int			is_player_adjacent_to_door(t_game *g, t_door *door);
int			update_single_door(t_game *g, t_door *door, double speed);
int			update_doors(t_game *g);
int			get_door_count(char **map);
int			key_press(int key, t_game *g);
int			key_release(int key, t_game *g);
int			close_window(void *param);
void		handle_left_click(t_game *g);
void		handle_right_click(t_game *g);
int			handle_mouse_rotation(t_game *g);
int			mouse_move(int x, int y, t_game *g);
void		apply_mouse_rotation(t_game *g);
int			mouse_press(int button, int x, int y, t_game *g);
int			mouse_release(int button, int x, int y, t_game *g);
void		init_mlx(t_mlx *mlx);
void		init_player(t_player *p);
void		init_floor_ceil_params(t_ray *r, t_player *p, int i);
int			calc_cell_size(t_game *g);
void		draw_cell(t_game *g, int i, int j);
void		draw_minimap_row(t_game *g, int i);
char		get_player_marker(t_player *player);
int			calc_draw_positions(t_ray *r, int *draw_start, int *draw_end);
void		calc_wall_hit(t_ray *r, t_player *p);
void		get_walls(t_game *g, t_player *p, t_ori_tex *tex, int i);
void		cast_rays(t_ray *ray, t_player *player, t_ori_tex *tex, t_game *g);
void		calc_rays(t_mlx *mlx, t_ray *ray, t_player *player, t_game *g);
int			handle_input(t_game *g);
void		start(t_game *game);
double		get_timestamp(void);
void		get_time(t_player *p);
void		draw_ceil_pixel(t_ori_tex *t, t_game *g, int screen_i, int j);
void		draw_floor_pixel(t_ori_tex *t, t_game *g, int screen_i, int j);
void		draw_floor_ceiling(t_game *g, t_player *player, t_ori_tex *tex);
void		get_c_colored(t_ori_tex *tex, t_game *g);
void		get_f_colored(t_ori_tex *tex, t_game *g);
int			move_forward(t_game *g);
int			move_backward(t_game *g);
int			move_right(t_game *g);
int			move_left(t_game *g);
int			handle_movement(t_game *g);
int			handle_rotation_keys(t_game *g);
int			handle_weapons(t_game *g);
t_door		**get_door_coords(t_game *g, char **map);

void		init_player(t_player *p);
void		init_mlx(t_mlx *mlx);
void		start(t_game *game);
int			is_xpm_path(char *path);
int			is_xpm_path_fc(char *path);
int			close_window(void *param);
int			is_cub_path(char *path);
void		free_mlx(t_mlx *m);

#endif