/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:39:33 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/29 09:50:12 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

void	ft_pwd(t_data *Data)
{
	char	*route;

	route = getcwd(NULL, 0);
	printf("%s\n", route);
	Data->last_out = 0;
	free(route);
	exit(0);
}
