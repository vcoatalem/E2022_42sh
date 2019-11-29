echo test: '@' variable
echo $@

echo test: '*' variable
echo "$*"

echo test: '#' variable
echo $#

echo test: '$?' variable
echo $?

echo test: dollar number
echo $1 $2

echo test: dollar dolar
echo $$

echo test: UID
echo $UID

echo test: oldPWD
echo $OLDPWD

echo test: IFS
echo $IFS
