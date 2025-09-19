/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:30:53 by rinka             #+#    #+#             */
/*   Updated: 2025/09/19 16:53:35 by ayusa            ###   ########.fr       */
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
#include "../libft/libft.h"
#include "struct.h"

void ft_add_env(t_env **env_lst, char *str, int is_export);
t_env *ft_set_env(char **envp);
char *ft_get_env(t_env *env_lst, const char *key);
char **env_to_array(t_env *env);

int ft_env(t_env *env_lst, int fd);
int ft_export(t_env *env_lst, int fd);
int ft_unset(t_env **env_lst, char *delkey);
int ft_pwd(t_env *env_lst, int fd);
int ft_cd(char **argv, t_env **env_lst);


#endif
