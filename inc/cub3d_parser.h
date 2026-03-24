/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:25:07 by hgutterr          #+#    #+#             */
/*   Updated: 2026/03/24 17:51:12 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSER_H
# define CUB3D_PARSER_H

int		parser(int argc, char **argv, t_game *g);
void	free_int_arr(int **arr, int i);
void	free_char_arr(char **arr, int i);
void	free_memory(char **arr);

# include <cub3d.h>

#endif