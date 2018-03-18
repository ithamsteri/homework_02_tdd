## Домашнее задание 02

[![Build Status](https://travis-ci.org/ithamsteri/homework_02_tdd.svg?branch=master)](https://travis-ci.org/ithamsteri/homework_02_tdd)

**Цель:** найти применение возможностям стандарта C++14

**Необходимо:**
* В приложенном к задании исходном файле необходимо заменить, где это возможно
  конструкции на аналогичные из стандарта C++14;
* Реализовать недостающий функционал;
* Результат опубликовать в своём репозитории на bintray;
* Выслать на адрес электронной почты название пакета содержащим исполняемый
  файл ip_filter;
* Выдержка из файла со списком адресов к задаче прилагается.

**Дополнительно:**
* Наличие тестов.

### Установка пакета

Для Ubuntu Trusty нужно сделать следующее:

```shell
echo "deb http://hamsterisoft.bintray.com/apt-repo trusty main" | sudo tee -a /etc/apt/sources.list
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 379CE192D401AB61
sudo apt-get update && sudo apt-get install ip_filter
```

И можно пользоваться:

```shell
cat datafile.tsv | ip_filter | md5sum
```

### Генерация сборки

Запустить в корневом каталоге проекта

```shell
cmake -H. -BBuild
```

### Сборка проекта

Запустить в каталоге Build

```shell
cmake --build .
```