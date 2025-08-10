# テストよう環境変数をexport
export TEST=test/path

#自作env,export,unsetの実行
#main関数内でunset前と後のenv,exportを別ファイルに書き込んでいる
cc -Wall -Wextra -Werror *.c ../libft/*.c -o env_pg
./env_pg my_env.txt my_unset.txt

#bashのenv,export
env > original_env.txt
export >> original_env.txt

#bashのunset
unset TEST

#bashのenv,export（unset後）
env > original_unset.txt 
export >> original_unset.txt


echo "-----MY_env-----"
cat my_env.txt | grep TEST
echo "
"
echo "-----ORIGINAL_env-----"
cat original_env.txt | grep TEST
echo "

"
echo "-----MY_unset-----"
cat my_unset.txt | grep TEST 
echo "
"
echo "-----ORIGINAL_unset-----"
cat original_unset.txt | grep TEST 
echo "
"


rm my_env.txt my_unset.txt original_env.txt original_unset.txt
rm ./env_pg