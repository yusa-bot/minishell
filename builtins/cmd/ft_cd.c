/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:47:51 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/15 14:36:02 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int  update_pwd_vars(t_env **env_lst, const char *oldpwd)
{

    char buf[PATH_MAX];
    char *oldpwd_str;
    char *pwd_str;

    if (!getcwd(buf, sizeof(buf)))
    {
        perror("minishell: cd: getcwd");
        return (1);
    }
    oldpwd_str = ft_strjoin("OLDPWD=", oldpwd);
    if (!oldpwd_str)
        return (1);
    pwd_str = ft_strjoin("PWD=", buf);
    if (!pwd_str)
    {
        free(oldpwd_str);
        return (1);
    }
    ft_add_env(env_lst, oldpwd_str, 1);
    ft_add_env(env_lst, pwd_str, 1);
    free(oldpwd_str);
    free(pwd_str);
    return (0);
}

int ft_cd(char **argv, t_env **env_lst)
{
    const char  *path;
    char  *oldpwd;
    int         argc;

    argc = 0;
    while (argv[argc])
        argc++;
    if (argc > 2) //valid
    {
        write(2, "minishell: cd: too many arguments\n", 34);
        return (1);
    }
    else if (argc == 1) //home
    {
        path = ft_get_env(*env_lst, "HOME");
        if (path == NULL)
        {
            write(2, "minishell: cd: HOME not set\n", 28);
            return (1);
        }
    }
    else if (ft_strcmp(argv[1], "-") == 0) //oldpwd
    {
        path = ft_get_env(*env_lst, "OLDPWD");
        if (path == NULL)
        {
            write(2, "minishell: cd: OLDPWD not set\n", 30);
            return (1);
        }
        write(1, path, ft_strlen(path)); // bashの挙動で移動先を表示
        write(1, "\n", 1);
    }
    else
        path = argv[1];

    oldpwd = getcwd(NULL, 0);//更新
    if (oldpwd == NULL)
		oldpwd = ft_get_env(*env_lst, "PWD");
    if (chdir(path) == -1)
    {
        free(oldpwd);
        write(2, "minishell: cd: ", 15);
        write(2, path, ft_strlen(path));
        write(2, ": No such file or directory\n", 28);
        return (1);
    }

    //更新
    if (oldpwd == NULL)
	    oldpwd = ft_strdup("");
    if (update_pwd_vars(env_lst, oldpwd))
    {
        free(oldpwd);
        return (1);
    }
    free(oldpwd);
    return (0);
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

//    printf("初期PWD: %s\n", ft_get_env(env_lst, "PWD"));
//    printf("初期OLDPWD: %s\n\n", ft_get_env(env_lst, "OLDPWD"));

//    // テスト1: 引数なし（HOMEに移動）
//    printf("テスト1: cd (HOMEに移動)\n");
//    char *test1[] = {"cd", NULL};
//    int result1 = ft_cd(test1, &env_lst);
//    printf("結果: %d\n", result1);
//    printf("PWD: %s\n", ft_get_env(env_lst, "PWD"));
//    printf("OLDPWD: %s\n\n", ft_get_env(env_lst, "OLDPWD"));

//    // テスト2: 特定のディレクトリに移動
//    printf("テスト2: cd /tmp\n");
//    char *test2[] = {"cd", "/tmp", NULL};
//    int result2 = ft_cd(test2, &env_lst);
//    printf("結果: %d\n", result2);
//    printf("PWD: %s\n", ft_get_env(env_lst, "PWD"));
//    printf("OLDPWD: %s\n\n", ft_get_env(env_lst, "OLDPWD"));

//    // テスト3: cd - (前のディレクトリに戻る)
//    printf("テスト3: cd -\n");
//    char *test3[] = {"cd", "-", NULL};
//    int result3 = ft_cd(test3, &env_lst);
//    printf("結果: %d\n", result3);
//    printf("PWD: %s\n", ft_get_env(env_lst, "PWD"));
//    printf("OLDPWD: %s\n\n", ft_get_env(env_lst, "OLDPWD"));

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
