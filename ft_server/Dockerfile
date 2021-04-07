#docker build -t wp .

FROM debian:buster

RUN apt update && apt install -y vim  wget unzip supervisor\
	nginx mariadb-server \
	php-fpm php-mysql php7.3 php-mysqli php-xml

# setting-up phpmyadmin
RUN cd /tmp/ && wget https://files.phpmyadmin.net/phpMyAdmin/5.1.0/phpMyAdmin-5.1.0-all-languages.zip && unzip phpMyAdmin-5.1.0-all-languages.zip -d /opt/
RUN mv -v /opt/phpMyAdmin-5.1.0-all-languages/ /opt/phpmyadmin && ln -s /opt/phpmyadmin/ /var/www/html/phpmyadmin
COPY src/config.inc.php /var/www/html/phpmyadmin/
RUN chmod 775 -v -R /opt/phpmyadmin/ && chown -v www-data:root -R /opt/phpmyadmin

# setting-up Wordpress
RUN cd /tmp && wget -v https://wordpress.org/latest.zip && unzip latest.zip -d /opt/
RUN chmod -v 775 -R /opt/wordpress && chown -v www-data:root -R /opt/wordpress && ln -s /opt/wordpress /var/www/html/wordpress

COPY src/default /etc/nginx/sites-available/

# setting-up ssl
RUN mkdir /etc/nginx/ssl && openssl genrsa -out /etc/nginx/ssl/server.key 2048 && \
openssl req -batch -new -key /etc/nginx/ssl/server.key -out /etc/nginx/ssl/server.csr && \
openssl x509 -days 3650 -req -signkey /etc/nginx/ssl/server.key -in /etc/nginx/ssl/server.csr -out /etc/nginx/ssl/server.crt

RUN touch /etc/supervisord.conf && echo '[supervisord]' >> /etc/supervisord.conf && \
echo 'nodaemon=true' >> /etc/supervisord.conf && \
echo '[program:nginx]' >> /etc/supervisord.conf && \
echo 'command=/usr/sbin/service nginx start' >> /etc/supervisord.conf && \
echo '[program:mysql]' >> /etc/supervisord.conf && \
echo 'command=/usr/sbin/service mysql start' >> /etc/supervisord.conf && \
echo '[program:php7.3-fpm]' >> /etc/supervisord.conf && \
echo 'command=/usr/sbin/service php7.3-fpm start' >> /etc/supervisord.conf

RUN service mysql start && \
mysql -e "CREATE DATABASE wordpress;" && \
mysql -e "CREATE USER 'wp_user' IDENTIFIED BY 'password';" && \
mysql -e "GRANT ALL ON wordpress.* TO 'wp_user'@'localhost' IDENTIFIED BY 'password';"

COPY src/startup.sh /startup.sh
RUN chmod 744 /startup.sh
CMD ["/startup.sh"]
