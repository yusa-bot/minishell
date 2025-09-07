/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:47:51 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/06 22:23:15 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//TODO?: 同一化
static int  print_cd_error(const char *arg)
{
    // minishell: cd: <arg>: <strerror>
    write(2, "minishell: cd: ", 15);
    if (arg)
        write(2, arg, strlen(arg));
    write(2, ": ", 2);
    write(2, strerror(errno), strlen(strerror(errno)));
    write(2, "\n", 1);
    return (1);
}

static int  update_pwd_vars(t_env **env, const char *oldpwd)
{
    char buf[PATH_MAX];

    if (!getcwd(buf, sizeof(buf)))
        return (print_cd_error("getcwd")); // 取得失敗時はエラー返す
    //if (env_set(env, "OLDPWD", oldpwd) != 0)
	if (ft_envlst_add_back(&lst, ft_envlst_new("OLDPWD", oldpwd, 1)) != 0)//TODO: lst & return int
        return (1);
    //if (env_set(env, "PWD", buf) != 0)
	if (ft_envlst_add_back(&lst, ft_envlst_new("PWD", buf, 1)) != 0)//TODO: lst & return int
        return (1);
    return (0);
}

static const char *resolve_target(char **argv, t_env *env)
{
    if (!argv[1])
        return get_env(env, "HOME"); // 無ければ NULL -> 呼び出し側でエラー化
    return argv[1];
}

int ft_cd(char **argv, t_env **env)
{
    const char  *target;
    const char  *oldpwd;
    int         argc;

    // 引数個数チェック
    argc = 0;
    while (argv[argc])
        argc++;
    if (argc > 2)
    {
        write(2, "minishell: cd: too many arguments\n", 34);
        return (1);
    }
    target = resolve_target(argv, *env);
    if (!target || !*target)
    {
        write(2, "minishell: cd: HOME not set\n", 28);
        return (1);
    }
    oldpwd = get_env(*env, "PWD"); // 無くても致命的ではない
    if (chdir(target) == -1)
        return (print_cd_error(target));
    if (update_pwd_vars(env, oldpwd ? oldpwd : "")) // PWD/OLDPWD更新
        return (1);
    return (0);
}
