# Wizard Parser

LL(\*)-парсер на C++ с поддержкой DSL для описания грамматики в EBNF непосредственно в коде программы.

## Возможности

* лексинг ASCII-текста:
	* задание лексем посредством регулярных выражений;
	* возможность исключения токенов из результирующего списка;
* парсинг ASCII-текста;
* описание грамматики на EBNF непосредственно в коде программы (посредством DSL);
* представление результата в виде AST;
* гибкое управление представлением нод в AST:
	* задание имени ноды;
	* скрытие ноды;
* сериализация AST в JSON;
* комбинаторы:
	* следование;
	* альтернатива;
	* повторение 0 или больше раз;
	* опциональность;
	* исключение;
* парсеры:
	* конец текста;
	* определённый текст;
	* определённая лексема.

## Скриншоты

![Пример AST-дерева](screenshots/screenshot_00.png)

## Лицензия

The MIT License (MIT)

Copyright &copy; 2015, 2017 thewizardplusplus
