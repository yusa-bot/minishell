#include "minishell.h"

//"export TEST" や"export TEST="にも対応する等に修正必要

void ft_add_env(t_env **env_lst, char *str, int is_export)
{
	char *key;
	char *value;

	key = ft_strndup(str, ft_strchr(str, '=') - str);
	if (key == NULL)
	{
		ft_envlst_clear(env_lst);
		return ;/////error_exit?
	}
	value = ft_strdup(ft_strchr(str, '=') + 1);
	if (value == NULL)
	{
		free (key);
		ft_envlst_clear(env_lst);
		return ;/////error_exit?
	}
	if (*env_lst == NULL)
	{
		*env_lst = ft_envlst_new(key, value, is_export);
	}
	else
		ft_envlst_add_front(env_lst,ft_envlst_new(key, value, is_export));
}