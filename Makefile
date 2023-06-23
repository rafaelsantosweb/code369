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
