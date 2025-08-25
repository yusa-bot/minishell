/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:30:53 by rinka             #+#    #+#             */
/*   Updated: 2025/08/25 00:04:31 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env {
	 char *key;
		char *value;
		int is_export;
		struct s_env *next;
} t_env;

//ft_envlst__utils.c
void	ft_envlst_delone(t_env *lst);
void	ft_envlst_clear(t_env **lst);
t_env *ft_envlst_last(t_env *lst);
void	ft_envlst_add_back(t_env **lst, t_env *new);
void	ft_envlst_add_front(t_env **lst, t_env *new);
t_env *ft_envlst_new(char *key, char *value, int is_export);

void ft_add_env(t_env **env_lst, char *str, int is_export);

void ft_put_envs(t_env *lst, int fd);

void ft_put_exports(t_env *env_lst, int fd);

void ft_unset(t_env **lst, char *delkey);

t_env *set_env(char **envp);

#endif