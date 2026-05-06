/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:22:54 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 00:56:54 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1e6);
}

void	get_time(t_player *p)
{
	p->old_time = p->time;
	p->time = get_timestamp();
	p->frame_time = p->time - p->old_time;
	p->move_speed = p->frame_time * 3.0;
	p->rot_speed = p->frame_time * 2.0;
}
