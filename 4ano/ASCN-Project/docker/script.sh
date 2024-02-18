#!/bin/bash

# Replace database configuration in .env file
sed -i "s/DB_DATABASE=laravel/DB_DATABASE=$DB_DATABASE/g" .env
sed -i "s/DB_USERNAME=root/DB_USERNAME=$DB_USERNAME/g" .env
sed -i "s/DB_PASSWORD=password/DB_PASSWORD=$DB_PASSWORD/g" .env

composer setup

php artisan migrate

if [ "$seed_database" == "true" ]; then
  echo ">>> Running seed"
  php artisan db:seed
fi

php artisan serve --host=0.0.0.0