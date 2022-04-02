/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjkim2 <42.4.minjkim2@student.42seoul    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:59:05 by Minjun            #+#    #+#             */
/*   Updated: 2022/04/02 00:13:39 by minjkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void
	error_exit(char *errormsg)
{
	printf("%s\n", errormsg);
	exit(1);
}

void
	system_error(char *errormsg)
{
	perror(errormsg);
	exit(1);
}

int
	error_return(char *errormsg)
{
	printf("%s\n", errormsg);
	return (EXIT_FAILURE);
}
