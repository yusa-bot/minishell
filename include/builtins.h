/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:30:53 by rinka             #+#    #+#             */
/*   Updated: 2025/10/23 08:50:40 by ayusa            ###   ########.fr       */
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

//ft_lst__utils.c
void	ft_lst_delone(t_env *lst);
void	ft_lst_clear(t_env **lst);
t_env *ft_lst_last(t_env *lst);
void	ft_lst_add_back(t_env **lst, t_env *new);
void	ft_lst_add_front(t_env **lst, t_env *new);
t_env *ft_lst_new(char *key, char *value, int is_export);

void ft_add_env(t_env **env_lst, char *str, int is_export);

void ft_env(t_env *lst, int fd);

void ft_exports(t_env *env_lst, int fd);

void ft_unset(t_env **lst, char *delkey);

t_env *ft_set_env(char **envp);

#endif
