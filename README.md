# Sequences-Generator
>Клиент-серверное приложение с возможностью взаимодействия с несколькими пользователями. 
Приложение генерирует 3 последовательности, каждая из которых задана соответсвенной командой. Свзяь клиента и сервера реализована на основе сокетов. 
Работа с множеством пользователей реализована с помощью вызова select(). Данное решение обусловлено более прозрачной и надежной
реализацией. Это также избавляет от многих проблем связанных с многопоточной реализацией.

## Launching 
Building project with Makefile:
`make`

Run server with: `make run`

Clean project directory with: `make clean`

## Application Interface

After launch server start listening on port `8888`. Use telnet to connect new user.

`telnet localhost 8888`

After successful connection to server socket you can generate your sequences. For example:

`seq1 3 4`

Export generated sequences to the user terminal with: `export seq`

You could break user connection using: `Ctrl + ]` and after that type command `close`