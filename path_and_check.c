/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_and_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:10:17 by gcapa-pe          #+#    #+#             */
/*   Updated: 2023/05/24 17:36:12 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_and_check2(char *command, t_pipex *pipex)
{
	char	*str;
	int		i;

	i = 0;
	while (pipex->paths[i])
	{
		str = ft_strjoin(pipex->paths[i], command);
		if (access(str, F_OK) == 0)
			break ;
		free(str);
		i++;
	}
	if (pipex->paths[i] == NULL)
	{
		ft_free_all(pipex->paths);
		return (command);
	}
	ft_free_all(pipex->paths);
	return (str);
}

char	*path_and_check(char *envp[], char *command, t_pipex *pipex)
{
	int		i;
	char	*temp1;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	pipex->paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (pipex->paths[++i])
	{
		temp1 = pipex->paths[i];
		pipex->paths[i] = ft_strjoin(pipex->paths[i], "/");
		free(temp1);
	}
	return (path_and_check2(command, pipex));
}
