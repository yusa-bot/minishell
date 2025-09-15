/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:16:17 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/14 16:31:24 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LST_H
# define ENV_LST_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

typedef struct s_env {
	char			*key;
	char			*value;
	int				is_export; //<->ローカル変数
	struct s_env	*next;
} t_env;

void	ft_lst_delone(t_env *lst);
void	ft_lst_clear(t_env **lst);
t_env	*ft_lst_last(t_env *lst);
void	ft_lst_add_back(t_env **lst, t_env *new);
void	ft_lst_add_front(t_env **lst, t_env *new);
t_env	*ft_lst_new(char *key, char *value, int is_export);

#endif
