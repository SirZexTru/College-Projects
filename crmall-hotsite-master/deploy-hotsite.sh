#!/bin/bash

colorGreen="\033[0;32m"
colorRed='\033[0;31m'
notColor="\033[0m"

echo "${colorGreen}Iniciando deploy hotsite!${colorGreen}"

echo "--------------------------------------------------------------------------${notColor}"

if [ -d "app" ]; then
  echo "${colorRed}\nRepositório já se encontra-se clonado na máquina!\n${notColor}"
  exit
else
    echo "\n\nInforme a url do repositório que deseja clonar:"
    read urlRepository
fi

git clone $urlRepository app

echo "\n\nRepositório clonado com sucesso!"

cd app/

echo "${colorGreen}\n Baixando o composer${notColor}"

echo "${colorGreen}--------------------------------------------------------------------------${notColor}"

## Using composer
wget https://getcomposer.org/composer.phar

echo "${colorGreen}\n Instalando as dependências${notColor}"

echo "${colorGreen}--------------------------------------------------------------------------${notColor}"

php composer.phar install

echo "${colorGreen}\nCopiando variáries de ambiente${notColor}"

echo "${colorGreen}--------------------------------------------------------------------------${notColor}"

cp .env.example .env




