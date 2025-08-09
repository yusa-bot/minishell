/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:29:18 by rinka             #+#    #+#             */
/*   Updated: 2025/08/10 00:49:13 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

t_env *set_env(char **envp)
{
	t_env *lst;
	int	i;
	char *key;
	char *value;

	lst = NULL;
	i = 0;
	while (envp[i])
	{
		key = strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
		if (key == NULL)
		{
			ft_lstclear(&lst);
			return (NULL);
		}
		value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		if (key == NULL)
		{
			free (key);
			ft_lstclear(&lst);
			return (NULL);
		}
		ft_lstadd_back(&lst,ft_lstnew(key, value, 1));//初期はすべてexportなのでflagたてる
		if (key == NULL)
		{
			ft_lstclear(&lst);
			return (NULL);
		}
		i++;
	}
	return (lst);
}


// void	ft_add_export(t_env *env_lst, char)

// int main(int argc, char **argv, char **envp)
// {
// 	t_env *env_lst;
// 	(void)argc;
// 	(void)argv;

// 	env_lst = NULL;
// 	env_lst = set_env(envp);
	
// 	ft_put_envs(env_lst, 1);
// 	write(1, "\n", 1);
// 	ft_put_exports(env_lst, 1);
// 	write(1, "\n", 1);
// 	ft_unset(&env_lst, "TEST");//"export TEST=/test/pathでテスト"
// 	ft_put_envs(env_lst, 1);
// 	write(1, "\n", 1);
// 	ft_put_exports(env_lst, 1);
// }
