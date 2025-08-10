/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:30:53 by rinka             #+#    #+#             */
/*   Updated: 2025/08/10 23:48:40 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_env {
	 char *key;
		char *value;
		int is_export;
		struct s_env *next;
} t_env;

//ft_utils.c
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *s, size_t n);

//ft_lst_utils.c
void	ft_lstdelone(t_env *lst);
void	ft_lstclear(t_env **lst);
t_env *ft_lstlast(t_env *lst);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env *ft_lstnew(char *key, char *value, int is_export);

void ft_put_envs(t_env *lst, int fd);

void ft_put_exports(t_env *env_lst, int fd);

void ft_unset(t_env **lst, char *delkey);

#endif