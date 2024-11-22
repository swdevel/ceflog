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

Если компиляция библиотеки выполнялась с флагом "-DBUILD_TESTS=on", в каталоге для сборки появятся исполняемые файлы "unit-tests" и "integration-tests".

### Модульное тестирование

Файл "unit-tests" служит для запуска модульного тестирования, результат которого выводится в лог:
~~~
$> ./unit-tests
[==========] Running 14 tests from 3 test suites.
[----------] Global test environment set-up.
[----------] 12 tests from CEFEventTest
[ RUN      ] CEFEventTest.ConstructorTest
[       OK ] CEFEventTest.ConstructorTest (0 ms)
[ RUN      ] CEFEventTest.CopyConstructorTest
[       OK ] CEFEventTest.CopyConstructorTest (0 ms)
...
[----------] Global test environment tear-down
[==========] 14 tests from 3 test suites ran. (1 ms total)
[  PASSED  ] 14 tests.
~~~

### Интеграционное тестирование

#### Подготовка к интеграционному тестированию

В процессе интеграционного тестирования, будет осуществлена попытка передачи тестовых сообщений по протоколу syslog на локальный сервер (localhost) по порту 514. Для успешного прохождения тестирования, необходимо выполнить установку и настройку rsyslog server.
Приведённая ниже инструкция составлена и проверена для Ubuntu 24.04 LTS.

#### Шаг 1

Для проверки наличия установленного rsyslog сервиса необходимо выполнить следующую команду:
~~~
$> apt list -a rsyslog
~~~
Если rsyslog отсутствует, то его можно установить при помощи следующей команды:
~~~
$> sudo apt-get install rsyslog -y or sudo apt install rsyslog -y
~~~
После установки сервиса необходимо настроить его запуск при старте системы и запустить. Для этого необходимо выполнить следующие команды:
~~~
$> sudo systemctl start rsyslog
$> sudo systemctl enable rsyslog
~~~

#### Шаг 2

Далее необходимо сконфигурировать сервис для приёма сообщений по протоколу UDP. Для этого необходимо открыть для редактирования конфигурационный файл сервиса:
~~~
sudo vi /etc/rsyslog.conf
~~~
В конфигурационном файле необходимо найти следующие строки:
~~~
...
# provides UDP syslog reception
# module(load="imudp")
# input(type="imudp" port="514")

# provides TCP syslog reception
# module(load="imtcp")
# input(type="imtcp" port="514")
...
~~~
Если они закомментированы, то необходимо удалить символ комментария "#":
~~~
...
# provides UDP syslog reception
module(load="imudp")
input(type="imudp" port="514")

# provides TCP syslog reception
module(load="imtcp")
input(type="imtcp" port="514")
...
~~~
Ниже необходимо добавить следующие строки:
~~~
$template RemInputLogs, "/var/log/remotelogs/%FROMHOST-IP%/%PROGRAMNAME%.log"
*.* ?RemInputLogs
~~~
Пример результата:
~~~
...
# provides UDP syslog reception
module(load="imudp")
input(type="imudp" port="514")

# provides TCP syslog reception
module(load="imtcp")
input(type="imtcp" port="514")

$template RemInputLogs, "/var/log/remotelogs/%FROMHOST-IP%/%PROGRAMNAME%.log"
*.* ?RemInputLogs
...
~~~
После этого необходимо сохранить изменения и завершить редактирование конфигурационного файла.
Для валидации изменений конфигурационного файла можно использовать команду:
~~~
$> rsyslogd -f /etc/rsyslog.conf -N1
rsyslogd: version 8.2312.0, config validation run (level 1), master config /etc/rsyslog.conf
rsyslogd: End of config validation run. Bye.
~~~

#### Шаг 3
Если в тестовом окружении используется firewall, то необходимо настроить доступы для rsyslog. Для это необходимо выполнить следующие команды:
~~~
$> sudo ufw allow 514/tcp
$> sudo ufw allow 514/udp
~~~

#### Шаг 4
Для того чтобы применились изменения конфигурации, необходимо перезапустить сервис rsyslogd при помощи команды:
~~~
sudo systemctl restart rsyslog
~~~
Статус сервиса можно проверить при помощи команды:
~~~
$> sudo systemctl status rsyslog
~~~

### Запуск интеграционных тестов

TODO:

## Документация

При разработке библиотеки использовался документ ["ArcSight Common Event Format"](https://www.microfocus.com/documentation/arcsight/arcsight-smartconnectors-8.4/pdfdoc/cef-implementation-standard/cef-implementation-standard.pdf)