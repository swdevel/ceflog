# ceflog

Библиотека для логирования событий в формате ArcSight Common Event Format (CEF) и передачи по протоколу syslog на удалённый или локальный сервер.

## Содержание
- [Технологии](#Технологии)
- [Требования](#Требования)
- [Сборка](#Сборка)
- [Тестирование](#Тестирование)
- [Документация](#Документация)

## Технологии
- [gtest](https://google.github.io/googletest/)
- [doxygen](https://www.doxygen.nl/)

## Требования

Для сборки библиотеки потребуется утилита "cmake" >= 3.0 и библиотека "boost" >= 1.54.0.

## Сборка

### Linux

Перед началом работы с библиотекой потребуется установить:
~~~
$> sudo apt-get install libboost-dev
~~~
Для сборки модульных и интеграционных тестов потребуется установить:
~~~
$> sudo apt-get install libgtest-dev
~~~
Для генерации документации на основе исходных текстов потребуется установить:
~~~
$> sudo apt-get install doxygen
~~~

Для сборки библиотеки потребуется выполнить следующие команды:
~~~
$> mkdir -p $CEFLOG_PATH && cd $CEFLOG_PATH
$> git clone https://github.com/swdevel/ceflog.git .
$> mkdir -p $CEFLOG_BUILD_PATH && cd $CEFLOG_BUILD_PATH
$> cmake $CEFLOG_PATH -DBUILD_TESTS=bool -DBUILD_EXAMPLES=bool
$> make
~~~

Описание переменных:
~~~
CEFLOG_PATH - каталог для хранения локальной копии проекта
CEFLOG_BUILD_PATH - каталог для сборки
BUILD_TESTS - флаг для сборки модульных и интеграционных тестов, допустимые значения: on/off
BUILD_EXAMPLES - флаг для сборки примеров использования библиотеки, допустимые значения: on/off
~~~

Для генерации документации на основе исходных текстов потребуется выполнить следующие команды:
~~~
$> cd $CEFLOG_PATH
$> doxygen
$> firefox doxygen/html/index.html
~~~

## Тестирование

TODO:

## Документация

При разработке библиотеки использовался документ ["ArcSight Common Event Format"](https://www.microfocus.com/documentation/arcsight/arcsight-smartconnectors-8.4/pdfdoc/cef-implementation-standard/cef-implementation-standard.pdf)