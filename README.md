# ceflog

Библиотека для логирования событий в формате ArcSight Common Event Format (CEF)

## Требования

### Linux
~~~
"CMake >= 3.0"
~~~

Для сборки модульных тестов потребуется установить следующие пакеты:
~~~
$> sudo apt-get install libgtest-dev
~~~

## Сборка

### Linux

~~~
$> mkdir -p $CEFLOG_PATH && cd $CEFLOG_PATH
$> git clone https://github.com/swdevel/ceflog.git .
$> mkdir -p $CEFLOG_BUILD_PATH && cd $CEFLOG_BUILD_PATH
$> cmake $CEFLOG_PATH
$> make
~~~

Для сборки тестов:
~~~
$> cmake $CEFLOG_PATH -DBUILD_TESTS=ON
~~~

Для сборки примеров:
~~~
$> cmake $CEFLOG_PATH -DBUILD_EXAMPLES=ON
~~~