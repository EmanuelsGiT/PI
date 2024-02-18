# Dockerfile for the laravel.io application

FROM ubuntu:22.04

ENV seed_database false

WORKDIR /laravel.io

COPY . .

RUN cp .env.example .env

RUN apt update
RUN apt install -y software-properties-common
RUN add-apt-repository ppa:ondrej/php
RUN apt update
RUN apt install -y php8.2 php8.2-redis php8.2-fpm php8.2-zIP php8.2-mbstring php8.2-tokenizer php8.2-mysql php8.2-gd php8.2-xml php8.2-bcmath php8.2-intl php8.2-curl
RUN apt install -y nodejs
RUN apt install -y composer
RUN apt install -y npm
RUN apt install -y mysql-client

RUN npm install
RUN composer install

EXPOSE 8000

RUN chmod +x script.sh

RUN php artisan key:generate

EXPOSE 8000

CMD ./script.sh
