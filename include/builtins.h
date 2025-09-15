/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:30:53 by rinka             #+#    #+#             */
/*   Updated: 2025/09/15 22:19:39 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

#include "../libft/lst/lst.h"


void ft_add_env(t_env **env_lst, char *str, int is_export);
t_env *ft_set_env(char **envp);
char *ft_get_env(t_env *env, const char *key);
char **env_to_array(t_env *env);

void ft_env(t_env *lst, int fd);
void ft_export(t_env *env_lst, int fd);
void ft_unset(t_env **lst, char *delkey);
int ft_pwd(t_env *env_lst, int fd);
int ft_cd(char **argv, t_env **env_lst);
int ft_exit(char **argv);


#endif
