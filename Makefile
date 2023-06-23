include .env

default: up

build: start composeri import

up:
	@lando start

start:
	@lando start

composeri:
	@cp -n .env.example .env || true
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

# User login
uli:
	lando dr uli

# Drush commands
cr:
	lando dr cr
cim:
	lando dr cim -y
cex:
	lando dr cex -y
st:
	lando dr st
sql:
	lando dr sqlc
ws:
	lando dr ws
wd:
	lando dr wd-del all --yes
updb:
	lando dr updb -y
