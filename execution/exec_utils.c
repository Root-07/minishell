/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:09:01 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/22 12:30:58 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_last_status(int stts)
{
	g_global.status = stts;
}

int	get_last_status(void)
{
	return (g_global.status);
}

int	get_exit_status(int pid)
{
	int		stts;
	char	*ptr;

	if (pid <= 0)
		return (get_last_status());
	waitpid(pid, &stts, 0);
	ptr = (char *) &stts;
	if (*ptr)
		return (*ptr + 128);
	return (*(ptr + 1));
}
