/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:30:53 by rinka             #+#    #+#             */
/*   Updated: 2025/10/31 15:08:10 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "struct.h"
# include "minishell.h"

int	ft_add_env(t_env **env_lst, char *str, int is_export);
t_env	*ft_set_env(char **envp);
char	**ft_get_env(t_env *env_lst, const char *key);
char	**env_to_array(t_env *env);
int	add_local_envs(t_shell *sh);

int		ft_env(t_shell *sh, int fd);
int		ft_export(int fd, t_shell *sh);
int		ft_unset(t_env **env_lst, char **args);
int		ft_pwd(t_env *env_lst, int fd);
int		ft_cd(char **argv, t_env **env_lst);

void	ft_lst_delone(t_env *lst);
void	ft_lst_clear(t_env **lst);
t_env	*ft_lst_last(t_env *lst);
void	ft_lst_add_back(t_env **lst, t_env *new);
void	ft_lst_add_front(t_env **lst, t_env *new);
t_env	*ft_lst_new(char *key, char *value, int is_export);

#endif
