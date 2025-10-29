/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:47:51 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/29 18:54:27 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  update_pwd_vars(t_env **env_lst, char *oldpwd, char *newpwd)
{
    char *oldpwd_str;
	char *newpwd_str;

	if (!oldpwd || !newpwd)
	{
		return (EXIT_FAILURE);
	}

    oldpwd_str = ft_strjoin("OLDPWD=", oldpwd);
    if (!oldpwd_str)
        return (EXIT_FAILURE);
    newpwd_str = ft_strjoin("PWD=", newpwd);
    if (!newpwd_str)
    {
        free(oldpwd_str);
        return (EXIT_FAILURE);
    }
    if (!ft_add_env(env_lst, oldpwd_str, 1))//ft_add_env内のmalloc_error処理(rinka)
        return (EXIT_FAILURE);
    if (!ft_add_env(env_lst, newpwd_str, 1))//ft_add_env内のmalloc_error処理(rinka)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int ft_cd(char **argv, t_env **env_lst)
{
    const char  *path;
    char  *oldpwd;
    int         argc;
	char *newpwd;
	char	*pwd;

	int i = 0;
	while (argv[i])
	{
		printf("ft_cd argv[%d]: %s\n", i, argv[i]);
		i++;
	}

    argc = 0;
    while (argv[argc])
		argc++;
	printf("argc=%d\n", argc);

    if (argc > 2)
    {
        write(2, "minishell: cd: too many arguments\n", 34);
        return (EXIT_FAILURE);
    }

    else if (argc == 1) //home
    {
        path = *ft_get_env(*env_lst, "HOME");
		printf("HOME=%s\n", path);
        if (path == NULL)
        {
            write(2, "minishell: cd: HOME not set\n", 28);
            return (EXIT_FAILURE);
        }
    }
    else if (ft_strcmp(argv[1], "-") == 0) //oldpwd
    {
        path = *ft_get_env(*env_lst, "OLDPWD");
        if (path == NULL)
        {
            write(2, "minishell: cd: OLDPWD not set\n", 30);
            return (EXIT_FAILURE);
        }
        write(1, path, ft_strlen(path)); // bashの挙動で移動先を表示
        write(1, "\n", 1);
    }
    else
        path = argv[1];


    oldpwd = getcwd(NULL, 0);//malloc
    if (oldpwd == NULL)
    {
        pwd = *ft_get_env(*env_lst, "PWD");//*
        if (pwd)
            oldpwd = ft_strdup(pwd);
        else
            oldpwd = ft_strdup("");
    }


    if (chdir(path) == -1)//main func
    {
        free(oldpwd);
        write(2, "minishell: cd: ", 15);
        write(2, path, ft_strlen(path));
        write(2, ": No such file or directory\n", 28);
        return (EXIT_FAILURE);
    }

	newpwd = getcwd(NULL, 0);//malloc
    if (newpwd == NULL)
    {
        pwd = *ft_get_env(*env_lst, "PWD");
        if (pwd)
            newpwd = ft_strdup(pwd);
        else
            newpwd = ft_strdup("");
    }

    if (update_pwd_vars(env_lst, oldpwd, newpwd) == EXIT_FAILURE)
    {
        free(oldpwd);
		free(newpwd);
        return (EXIT_FAILURE);
    }
    free(oldpwd);
	free(newpwd);
    return (EXIT_SUCCESS);
}


//// テスト用main関数
//#include <stdio.h>
//int main()
//{
//    printf("=== ft_cd テスト ===\n\n");

//    // 環境変数リストの初期化
//    char *envp[] = {
//        "USER=testuser",
//        "HOME=/Users/testuser",
//        "PWD=/Users/testuser/Desktop",
//        "OLDPWD=/Users/testuser",
//        NULL
//    };
//    t_env *env_lst = ft_set_env(envp);

//    printf("初期PWD: %s\n", *ft_get_env(env_lst, "PWD"));
//    printf("初期OLDPWD: %s\n\n", *ft_get_env(env_lst, "OLDPWD"));

//    // テスト1: 引数なし（HOMEに移動）
//    printf("テスト1: cd (HOMEに移動)\n");
//    char *test1[] = {"cd", NULL};
//    int result1 = ft_cd(test1, &env_lst);
//    printf("結果: %d\n", result1);
//    printf("PWD: %s\n", *ft_get_env(env_lst, "PWD"));
//    printf("OLDPWD: %s\n\n", *ft_get_env(env_lst, "OLDPWD"));

//    // テスト2: 特定のディレクトリに移動
//    printf("テスト2: cd /tmp\n");
//    char *test2[] = {"cd", "/tmp", NULL};
//    int result2 = ft_cd(test2, &env_lst);
//    printf("結果: %d\n", result2);
//    printf("PWD: %s\n", *ft_get_env(env_lst, "PWD"));
//    printf("OLDPWD: %s\n\n", *ft_get_env(env_lst, "OLDPWD"));

//    // テスト3: cd - (前のディレクトリに戻る)
//    printf("テスト3: cd -\n");
//    char *test3[] = {"cd", "-", NULL};
//    int result3 = ft_cd(test3, &env_lst);
//    printf("結果: %d\n", result3);
//    printf("PWD: %s\n", *ft_get_env(env_lst, "PWD"));
//    printf("OLDPWD: %s\n\n", *ft_get_env(env_lst, "OLDPWD"));

//    // テスト4: 存在しないディレクトリ
//    printf("テスト4: cd /nonexistent\n");
//    char *test4[] = {"cd", "/nonexistent", NULL};
//    int result4 = ft_cd(test4, &env_lst);
//    printf("結果: %d (エラーが表示されるはず)\n\n", result4);

//    // テスト5: 引数が多すぎる場合
//    printf("テスト5: cd arg1 arg2\n");
//    char *test5[] = {"cd", "arg1", "arg2", NULL};
//    int result5 = ft_cd(test5, &env_lst);
//    printf("結果: %d (エラーが表示されるはず)\n\n", result5);

//    ft_lst_clear(&env_lst);
//    return 0;
//}
