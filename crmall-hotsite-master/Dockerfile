FROM php:7.3-fpm

LABEL maintainer="web@crmall.com"

WORKDIR "/application"

RUN apt-get update \
    && apt-get install -y \
    curl \
    git \
    gnupg \
    libpng-dev \
    zlib1g-dev \
    libicu-dev \
    libcurl4-openssl-dev \
    libmcrypt-dev \
    libfreetype6-dev \
    libjpeg62-turbo-dev \
    libmcrypt-dev
RUN docker-php-ext-install -j$(nproc) iconv mcrypt \
    	&& docker-php-ext-configure gd --with-freetype-dir=/usr/include/ --with-jpeg-dir=/usr/include/ \
    	&& docker-php-ext-install -j$(nproc) gd

# Install xDebug
RUN pecl install xdebug \
    && docker-php-ext-enable xdebug \
    && apt-get clean; rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* /usr/share/doc/* \
    && echo "xdebug.remote_enable=on" >> /usr/local/etc/php/conf.d/php-dev.ini \
    && echo "xdebug.remote_handler=dbgp" >> /usr/local/etc/php/conf.d/php-dev.ini \
    && echo "xdebug.remote_port=9000" >> /usr/local/etc/php/conf.d/php-dev.ini \
    && echo "xdebug.remote_autostart=on" >> /usr/local/etc/php/conf.d/php-dev.ini \
    && echo "xdebug.remote_connect_back=0" >> /usr/local/etc/php/conf.d/php-dev.ini \
    && echo "xdebug.idekey=docker" >> /usr/local/etc/php/conf.d/php-dev.ini

ENV TZ America/Sao_Paulo

COPY phpdocker/php-fpm/php-ini-overrides.ini /etc/php/7.1/fpm/conf.d/99-overrides.ini