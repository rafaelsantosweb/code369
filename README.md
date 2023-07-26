# Projeto Observatório da Firjan

## Equipe técnica

| Nome | Função |
| Alessandro Feijó | Tech Lead |
| Rafael | Dev Sr |
| Glaucio | Dev Jr |
| Daniel | Dev Jr |


# Comandos Make

## Instalação de dependências (lando, composer, npm, yarn, etc)

```bash
make install
```

## Iniciar o projeto

```bash
make up
```

## Para o projeto

```bash
make stop
```

## Importar o banco

```bash
make import
```

## Roda composer install

```bash
make composer
```

## Roda composer update

```bash
make composeru
```

## Atualizar o banco

```bash
make import
```
# Comandos Drush

- **make st** - Mostra o estado do site
- **make cr** - Limpa o cache do Drupal
- **make updb** - Atualiza o banco de dados
- **make cim** - Importa a configuração do site
- **make cex** - Exporta a configuração do site
- **make deploy** - Atualiza o banco de dados e limpa o cache e importa a config
- **make sql** - Acessa o terminal do mysql
- **make ws** - Lista as ultimas msgs do log do drupal
- **make wt** - Lista e fica escutando o log do drupal
- **make wd** - Apaga o log do drupal
