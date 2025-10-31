/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:29:18 by rinka             #+#    #+#             */
/*   Updated: 2025/10/29 19:26:34 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// envリストをexecve用のchar**に変換
char **env_to_array(t_env *env_lst)
{
    int     count = 0;
    char    **arr;
    char    *str;
    t_env   *cur;

    cur = env_lst;
    while (cur)
    {
        if (cur->is_export)
            count++;
        cur = cur->next;
    }
    arr = malloc(sizeof(char *) * (count + 1));
    if (!arr)
        return (NULL);
    count = 0;
    cur = env_lst;
    while (cur)
    {
        if (cur->is_export)
        {
            if (cur->value)
            {
                str = ft_strjoin_oneptr(cur->key, "=");
                str = ft_strjoin_oneptr(str, cur->value);
            }
            else
                str = ft_strdup(cur->key);
            arr[count++] = str;
        }
        cur = cur->next;
    }
    arr[count] = NULL;
    return arr;
}


// minishellで動的に追加/変更した環境変数の取得用
char **ft_get_env(t_env *env_lst, const char *key)
{
	while (env_lst)
	{
		if (ft_strcmp(env_lst->key, key) == 0)
			return (&env_lst->value);
		env_lst = env_lst->next;
	}
	return NULL;
}

t_env *ft_set_env(char **envp)
{
	t_env *env_lst;
	int	i;
	char *key;
	char *value;
	char *equal;

	env_lst = NULL;
	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (!equal)
		{
			i++;
			continue;
		}
		key = ft_strndup(envp[i], equal - envp[i]);
		if (!key)
        {
			ft_lst_clear(&env_lst);
			exit(EXIT_FAILURE);
		}
		value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		if (!value)
		{
			free(key);
			ft_lst_clear(&env_lst);
			exit(EXIT_FAILURE);
		}
		ft_lst_add_back(&env_lst, ft_lst_new(key, value, 1));//ft_lst_newのmalloc失敗時の処理を加えた方がいいかも
		i++;
	}
	return (env_lst);
}

int	ft_add_env(t_env **env_lst, char *str, int is_export)
{
	char *key;
	char *value;
	char *equal_pos;
	t_env *cur;

	equal_pos = ft_strchr(str, '=');
	if (equal_pos == NULL)// "export TEST" の場合（=がない）
	{
		key = ft_strdup(str);
		value = NULL;
	}
	else// "export TEST=value" の場合（=がある）
	{
		key = ft_strndup(str, equal_pos - str);
		value = ft_strdup(equal_pos + 1);
	}
	if (key == NULL || (equal_pos != NULL && value == NULL))//malloc_error(呼び出し元で処理)
	{
		free(key);
		free(value);
		return(0);
	}

	cur = *env_lst;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)// すでに存在する変数を更新する場合
		{
			if (equal_pos)//valueの更新を含む場合
			{
				free(cur->value);
				cur->value = value;
			}
			cur->is_export = is_export;
			free(key);
			return (1);
		}
		cur = cur->next;
	}
	if (equal_pos)//存在しない＆valueがない場合、何もしない
		ft_lst_add_front(env_lst, ft_lst_new(key, value, is_export));//新しい変数追加の場合
	return (1);
}

static t_env *ft_env_dup(t_env *lst)
{
	t_env *res;
	char    *key_copy;
	char    *value_copy;

	if (!lst || !lst->key)
		return (NULL);
	res = NULL;
	key_copy = ft_strdup(lst->key);
	if (!key_copy)
		return (NULL); //marroc_error
	value_copy = ft_strdup(lst->value);
	if (!value_copy)
		return (NULL); //marroc_error
	res = ft_lst_new(key_copy, value_copy, 0);
	if (res == NULL)
		return (NULL); //marroc_error
	return (res);
}

//readlineがパイプなし＆変数代入のみの時は変数代入をローカル変数に加える
int	add_local_envs(t_shell *sh)
{
	printf("add_local_envs\n");
	t_env *tmp;
	t_env *cpy;
	char **ptr_to_change;
	tmp = sh->cmd->tmp_env;
	while (tmp)
	{
		ptr_to_change = ft_get_env(sh->env, tmp->key);
		if (ptr_to_change)
		{
			free(*ptr_to_change);
			*ptr_to_change = ft_strdup(tmp->value);
			if (*ptr_to_change == NULL)
				return (EXIT_FAILURE);
		}
		else
		{
			cpy = ft_env_dup(tmp);
			if (cpy == NULL)
				return (EXIT_FAILURE);
			ft_lst_add_back(&(sh->env), cpy);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);//戻り値これでいい？？(rinka)
}


// #include <fcntl.h>
//int main(int argc, char **argv, char **envp) // export TEST=/test/pathでテスト
//{
//	(void)argc;
//	t_env *env_lst;

//	env_lst = ft_set_env(envp);

//	int env_fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	if (env_fd == -1)
//		return (1);

//	// export TEST=/test/path
//	ft_add_env(&env_lst, "TEST=/test/path", 1);
//	// export TEST2=/test2/path
//	ft_add_env(&env_lst, "TEST2=/test2/path", 0);

//	// unset前
//	ft_env(env_lst, env_fd);
//	write(env_fd, "\n", 1);
//	ft_export(env_lst, env_fd);
//	write(env_fd, "\n", 1);

//	int unset_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	if (unset_fd == -1)
//		return (1);

//	// TEST=/test/pathをunset
//	ft_unset(&env_lst, "TEST");

//	// unset後
//	ft_env(env_lst, unset_fd);
//	write(unset_fd, "\n", 1);
//	ft_export(env_lst, unset_fd);

//	ft_lst_clear(&env_lst);
//}
