include .env

default: up

build: start composeri import

up:
	@lando start

start:
	@lando start

update: composeri deploy compile

install:
	@cp -n .env.example .env || true
	@lando start
	@make composeri

composeri:
	@lando composer install

composeru:
	@lando composer update

import:
	@(cd database;lando db-import *)

export:
	@(cd database;rm *.gz;lando db-export)

stop:
	@lando stop

poweroff:
	@lando poweroff

npmi:
	@(cd web/themes/custom/observatorio;lando npm i)

watch:
	@lando watch

compile:
	@lando production

# User login
uli:
	@lando dr uli

# Drush commands
deploy:
	@lando dr deploy
cr:
	@lando dr cr
cim:
	@lando dr cim -y
cex:
	@lando dr cex -y
st:
	@lando dr st
sql:
	@lando dr sqlc
ws:
	@lando dr ws
wt:
	@lando dr wt
wd:
	@lando dr wd-del all --yes
updb:
	@lando dr updb -y
