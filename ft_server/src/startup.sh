#!/bin/bash

echo "  __  _
 / _|| |_        ___ ___  _ _ __ __ ___  _ _
|  _||  _|      (_-// -_)| '_|\ V // -_)| '_|
|_|   \__|      /__/\___||_|   \_/ \___||_|
"
echo -e "For cheching autoindex, access \e[4mlocalhost/test\e[3m"
# for testing autoindex
mkdir /var/www/html/test
touch /var/www/html/test/hi
mkdir /var/www/html/test/test1

if [ "$autoindex" = "off" ]; then
	sed -i -e "/^server {$/a autoindex off;" /etc/nginx/sites-available/default &&

	echo " _______________________"
	echo -e "< autoindex is \e[31mdisabled\e[m >"
	echo " -----------------------"
	echo "        \\   ^__^"
	echo "         \  (oo)\_______"
	echo "            (__)\       )\/\\"
	echo "                ||----w |"
	echo "                ||     ||"
else
	sed -i -e "/^server {$/a autoindex on;" /etc/nginx/sites-available/default &&
	echo " ______________________"
	echo -e "< autoindex is \e[32menabled\e[m >"
	echo " ----------------------"
	echo "  \\"
	echo "   \\"
	echo "      /\\_)o<"
	echo "     |      \\"
	echo "     | O . O|"
	echo "      \\_____/"
	echo ""
	echo "/ \----------------------------------------,"
	echo "\_,|                                       |"
	echo "   |    If you want to disable autoindex,  |"
	echo -e "   |    please add \e[7m--env autoindex=off\e[m     |"
	echo -e "   |    when you \e[4mdocker run\e[m.               |"
	echo "   |  ,--------------------------------------"
	echo "   \_/_____________________________________/"
fi

/usr/bin/supervisord -c /etc/supervisord.conf
