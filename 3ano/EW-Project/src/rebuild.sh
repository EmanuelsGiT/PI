#!/bin/bash
docker-compose down
docker rmi src-interface-1
docker rmi src-auth-1
docker rmi src-api-1
docker rmi src-mongodb-1
docker-compose up -d --build