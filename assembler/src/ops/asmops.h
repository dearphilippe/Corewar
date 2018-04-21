/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asmops.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 17:07:59 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/27 17:24:00 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASMOPS_H
#define ASMOPS_H

#include "state.h"

void	genop(char **sfile, t_buffers *cor, t_ininit *handler);
void	ft_live(char **sfile, t_buffers *cor);
void	ft_ld(char **sfile, t_buffers *cor);
void	ft_st(char **sfile, t_buffers *cor);
void	ft_add(char **sfile, t_buffers *cor);
void	ft_sub(char **sfile, t_buffers *cor);
void	ft_and(char **sfile, t_buffers *cor);
void	ft_or(char **sfile, t_buffers *cor);
void	ft_xor(char **sfile, t_buffers *cor);
void	ft_zjmp(char **sfile, t_buffers *cor);
void	ft_ldi(char **sfile, t_buffers *cor);
void	ft_sti(char **sfile, t_buffers *cor);
void	ft_fork(char **sfile, t_buffers *cor);
void	ft_lld(char **sfile, t_buffers *cor);
void	ft_lldi(char **sfile, t_buffers *cor);
void	ft_lfork(char **sfile, t_buffers *cor);
void	ft_aff(char **sfile, t_buffers *cor);

#endif
