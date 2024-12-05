# ceflog

Библиотека для логирования событий в формате ArcSight Common Event Format (CEF) и передачи по протоколу syslog на удалённый или локальный сервер.

## Содержание
- [Технологии](#Технологии)
- [Требования](#Требования)
- [Сборка](#Сборка)
- [Тестирование](#Тестирование)
- [Примеры](#Примеры)
- [Документация](#Документация)

## Технологии
- [gtest](https://google.github.io/googletest/)
- [doxygen](https://www.doxygen.nl/)

## Требования

- Компилятор с поддержкой стандарта C++17 (GCC 8+)
- CMake >= 3.0
- Библиотека boost >= 1.54.0

## Сборка

### Linux

Перед началом работы с библиотекой потребуется установить:
```bash
sudo apt-get install libboost-dev
```
Для сборки модульных и интеграционных тестов потребуется установить:
```bash
sudo apt-get install libgtest-dev
```
Для генерации документации на основе исходных текстов потребуется установить:
```bash
sudo apt-get install doxygen
```

Для сборки библиотеки потребуется выполнить следующие команды:
```bash
mkdir -p $CEFLOG_PATH && cd $CEFLOG_PATH
git clone https://github.com/swdevel/ceflog.git .
mkdir -p $CEFLOG_BUILD_PATH && cd $CEFLOG_BUILD_PATH
cmake $CEFLOG_PATH -DBUILD_TESTS=bool -DBUILD_EXAMPLES=bool
make
```

Описание переменных:
```bash
CEFLOG_PATH - каталог для хранения локальной копии проекта
CEFLOG_BUILD_PATH - каталог для сборки
BUILD_TESTS - флаг для сборки модульных и интеграционных тестов, допустимые значения: on/off
BUILD_EXAMPLES - флаг для сборки примеров использования библиотеки, допустимые значения: on/off
```

Для генерации документации на основе исходных текстов потребуется выполнить следующие команды:
```bash
cd $CEFLOG_PATH
doxygen
firefox doxygen/html/index.html
```

## Тестирование

Если компиляция библиотеки выполнялась с флагом "-DBUILD_TESTS=on", в каталоге для сборки появятся исполняемые файлы "unit-tests" и "integration-tests".

### Модульное тестирование

Файл "unit-tests" служит для запуска модульного тестирования, результат которого выводится в лог.

<details>
<summary>Пример лога</summary>

```bash
./unit-tests
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
```

</details>

### Интеграционное тестирование

#### Подготовка к интеграционному тестированию

В процессе интеграционного тестирования, будет осуществлена попытка передачи тестовых сообщений по протоколу syslog на локальный сервер (localhost) по порту 514. Для успешного прохождения тестирования, необходимо выполнить установку и настройку rsyslog server.
Приведённая ниже инструкция составлена и проверена для Ubuntu 24.04 LTS.

<details>
<summary>Инструкция</summary>

#### Шаг 1

Для проверки наличия установленного rsyslog сервиса необходимо выполнить следующую команду:
```bash
apt list -a rsyslog
```
Если rsyslog отсутствует, то его можно установить при помощи следующей команды:
```bash
sudo apt-get install rsyslog -y or sudo apt install rsyslog -y
```
После установки сервиса необходимо настроить его запуск при старте системы и запустить. Для этого необходимо выполнить следующие команды:
```bash
sudo systemctl start rsyslog
sudo systemctl enable rsyslog
```

#### Шаг 2

Далее необходимо сконфигурировать сервис для приёма сообщений по протоколу UDP. Для этого необходимо открыть для редактирования конфигурационный файл сервиса:
```bash
sudo vi /etc/rsyslog.conf
```
В конфигурационном файле необходимо найти следующие строки:
```bash
...
# provides UDP syslog reception
# module(load="imudp")
# input(type="imudp" port="514")

# provides TCP syslog reception
# module(load="imtcp")
# input(type="imtcp" port="514")
...
```
Если они закомментированы, то необходимо удалить символ комментария "#":
```bash
# provides UDP syslog reception
module(load="imudp")
input(type="imudp" port="514")

# provides TCP syslog reception
module(load="imtcp")
input(type="imtcp" port="514")
...
```
Ниже необходимо добавить следующие строки:
```bash
$template RemInputLogs, "/var/log/remotelogs/%FROMHOST-IP%/%PROGRAMNAME%.log"
*.* ?RemInputLogs
```
Пример результата:
```bash
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
```
После этого необходимо сохранить изменения и завершить редактирование конфигурационного файла.
Для валидации изменений конфигурационного файла можно использовать команду:
```bash
rsyslogd -f /etc/rsyslog.conf -N1
rsyslogd: version 8.2312.0, config validation run (level 1), master config /etc/rsyslog.conf
rsyslogd: End of config validation run. Bye.
```

#### Шаг 3
Если в тестовом окружении используется firewall, то необходимо настроить доступы для rsyslog. Для это необходимо выполнить следующие команды:
```bash
sudo ufw allow 514/tcp
sudo ufw allow 514/udp
```

#### Шаг 4
Для того чтобы применились изменения конфигурации, необходимо перезапустить сервис rsyslog при помощи команды:
```bash
sudo systemctl restart rsyslog
```
Статус сервиса можно проверить при помощи команды:
```bash
sudo systemctl status rsyslog
```

</details>

### Запуск интеграционных тестов

Файл "integration-tests" служит для запуска интеграционного тестирования, результат которого выводится в лог.

<details>
<summary>Пример лога</summary>

```bash
./integration-tests
[==========] Running 9 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 9 tests from SyslogAsyncClientTest
[ RUN      ] SyslogAsyncClientTest.ConstructorTest_InvalidParams
[       OK ] SyslogAsyncClientTest.ConstructorTest_InvalidParams (0 ms)
[ RUN      ] SyslogAsyncClientTest.SetMaxTransmittedMessagesPerSecondTest
[       OK ] SyslogAsyncClientTest.SetMaxTransmittedMessagesPerSecondTest (0 ms)
...
[----------] Global test environment tear-down
[==========] 9 tests from 1 test suite ran. (3765 ms total)
[  PASSED  ] 9 tests.
```

</details>

## Примеры

<details>
<summary>Пример</summary>

Пример использования библиотеки для создания события в формате CEF с последующей отправкой на локальный syslog сервер:

```cpp
#include "CEFLog.h"

using namespace ceflog::syslog;
using namespace ceflog::event;

int main()
{
    /**
     * Создание экземпляра фабрики для генерации событий в формате CEF
     */

    const uint8_t formatVersion = 0;
    const std::string deviceVendor = "Security";
    const std::string deviceProduct = "threatmanager";
    const std::string deviceVersion = "1.0";

    const CEFEventFactory factory(formatVersion, deviceVendor, deviceProduct, deviceVersion);

    /**
     * Генерация события в формате CEF
     */
    const std::string deviceEventClassId = "100";
    const std::string eventName = "worm successfully stopped";
    const CEFSeverity severity = CEFSeverity::VeryHigh;

    const std::vector<CEFEventExtension> extensions = {{"src", "10.0.0.1"},
                                                       {"dst", "2.1.2.2"},
                                                       {"spt", "1232"}};

    const auto event = factory.CreateEvent(deviceEventClassId,
                                           eventName,
                                           severity,
                                           extensions);

    /**
     * Сериализация события в строковое представление
     *
     */
    CEFEventStringSerializer serializer;
    const auto message = serializer.Serialize(event);

    /**
     * Создание логгера для передачи сообщений по протоколу syslog на локальный (localhost) syslog сервер
     *
     */
    auto sysloggerBackend = std::make_shared<SyslogBoostClientBackend>("127.0.0.1",
                                                                       deviceProduct);
    SyslogAsyncClient sysloggerClient(sysloggerBackend);

    /**
     * Передача сообщения по протоколу syslog
     */
    sysloggerClient.PushMessage(SyslogSeverity::Info, message);

    return 0;
}
```
Для сборки примера необходимо выполнить линковку с библиотеками "ceflog" и "Boost::log":
```cmake
add_executable(example
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
target_link_libraries(example ceflog Boost::log)
```

</details>

Дополнительные примеры использования библиотеки доступны по [ссылке](https://github.com/swdevel/ceflog/tree/main/examples) 

## Документация

При разработке библиотеки использовался документ ["ArcSight Common Event Format"](https://www.microfocus.com/documentation/arcsight/arcsight-smartconnectors-8.4/pdfdoc/cef-implementation-standard/cef-implementation-standard.pdf)