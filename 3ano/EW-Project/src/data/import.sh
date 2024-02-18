#!/bin/bash

mongoimport --db Project --collection users --file users.json --jsonArray
mongoimport --db Project --collection inquiricoes --file inquiricoes.json --jsonArray
mongoimport --db Project --collection posts --file posts.json --jsonArray
mongoimport --db Project --collection sugestoes --file sugestoes.json --jsonArray
