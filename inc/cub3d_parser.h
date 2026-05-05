/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:25:07 by hgutterr          #+#    #+#             */
/*   Updated: 2026/05/05 23:29:37 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSER_H
# define CUB3D_PARSER_H

void	free_int_arr(int **arr, int i);
void	free_char_arr(char **arr, int i);
void	free_memory(char **arr);
void	free_memory_int(int **arr);


int 	check_rbg(char *str, int *arr);
void	choose_corect_path(char *line, int value, t_ori_tex *tex);
int		handle_texture(char *line, int value, t_ele_var *vars, char **tex_path);
int		handle_floor_ceiling(char *line, int value, t_ele_var *vars, t_ori_tex *tex);
int		check_elements(char **elements, t_ori_tex *tex, t_ele_var *vars);
void	process_element_line(char *line, t_ele_var *vars, t_ori_tex *tex);



int		*get_player_coords(char **map);
void	get_player_orientation(char player_orientation, t_player *p);
int		check_walls(char **map, int y, int x);
int		check_map_borders(char **map, t_game *g);
int		check_map_interior(char **map, t_ele_var *vars);
int		check_doors(char **map, int y, int x);
int		check_walls_doors(char **map, int y, int x);
int		is_wall(char c);
int		is_player(char c);
int		check_map(char **map, t_player *p, t_game *g, t_ele_var *vars);



int		calc_clean_size(char **splited);
void	copy_cleaned(char **splited, char *cleaned);
char	*looksmax_string(char *str);



int	    f_c_type(char *str);
int	    is_numeric_str(char *str);
int		validate_rgb_values(char **splited, int *arr);



int		count_elements(char **cub, int y, int *door_found);
int		process_line(char *line, char **elements_file, int i, int *stop, int door_found);
char	**fill_elements(char **cub, int *y, int count, int door_found);
char	**get_elements(char **cub, int *y, t_ele_var *vars);



int		get_map_bounds(char **cub, int *y);
char	**copy_map(char **cub, int start, int count);
char	**get_map(char **cub, int *y, t_game *g);


int		find_player(char **map, int *coord);
char	*ft_findspace(char *str);



char	*read_into_buffer(char *file);
int		count_lines(char *buff, int size);
char	*extract_line(char *buff, int *j);
char	**split_lines(char *buff, int count);
char	**read_file(char *file);



int		parser(int argc, char *argv[], t_game *g);
int		validate_args(int argc, char *argv[]);
int		load_cub_file(t_game *g, char *file);
int		load_elements_and_map(t_game *g, t_ele_var *vars);
void	print_debug(t_game *g);
void	free_all(t_game *g);
void	free_memory(char **arr);

int get_textures(t_mlx *mlx, t_ori_tex *tex);
void load_texture(t_mlx *mlx, t_texture **tex_d, char *path);


# include <cub3d.h>

#endif