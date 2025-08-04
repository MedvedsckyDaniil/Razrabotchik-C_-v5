## Инструкция по сборке и использованию

### Сборка библиотеки и консольного приложения
#### Динамическая сборка
```bash
mkdir build
cd build
cmake .. -DBUILD_SHARED_LIBS=ON
make
```
#### Статическая сборка
```bash
mkdir build
cd build
cmake .. -DBUILD_SHARED_LIBS=OFF
make
```

### Запуск консольного приложения
`./logger_app <log_file> <LEVEL>`
* `<log_file>` – лог-файл (файл журнала)
* `<LEVEL>` – уровень логирования (важности сообщения) по умолчанию
```bash
./logger_app myapp.log INFO
```
Запуск консольного приложения производится так же из папки `build`.

### Работа с консольным приложением

#### Формат сообщения
`<LEVEL>:<message>`
* `<LEVEL>` – уровень логирования
* `<message>` – сообщение
#### Уровни логирования (важности сообщения)
0. `ERROR`
1. `WARNING`
2. `INFO`
3. `DEBUG`
#### Формат записи в журнал
`<TIME> <LEVEL> <message>`
