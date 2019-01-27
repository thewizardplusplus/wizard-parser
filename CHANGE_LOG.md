# Change Log

## [v3.0](https://github.com/thewizardplusplus/wizard-parser/tree/v3.0) (2019-01-27)

**Closed issues:**

* Processing errors:
  * Add the universal exception for an unexpected entity.
  * Symplify processing an error:
    * with an unexpected symbol;
    * with an unexpected token;
    * with an unexpected EOI.
* Remove:
  * code entities:
    * header including all parsers;
    * functions:
      * function for repeating in a range of times;
      * overload of the `parser::parse()` function accepting a string;
    * operators:
      * for repeating an exact number of times;
      * for parsing separated lists;
  * possibilities:
    * ignoring some tokens;
    * auto-selection:
      * of longest token;
      * of longest node;
    * serialization to JSON:
      * from the `lexer` module;
      * from the `parser` module.
* Refactoring:
  * of the `lexer` module:
    * combine in a single file:
      * `token` and `token_group` types;
    * add new types:
      * `lexeme_group` type alias;
      * `token_span` type alias;
    * refactoring:
      * of the `find_matched_token()` function;
      * of the `tokenize()` function;
  * of the `parser` module:
    * simplify a code of parsers;
    * combine in a single file:
      * `ast_node_flag` and `ast_node` types;
      * `parsing_result` and `rule_parser` types;
      * `match_type` and `match_parser` types;
    * add new types:
      * `ast_node_group` type alias;
    * replace:
      * magic constants of AST node types to an enumeration;
      * custom bitwise operators for the `ast_node_flag` enumeration to using the [grisumbras/enum-flags](https://github.com/grisumbras/enum-flags) library;
      * mutable instances in parameters to constant references;
    * remove:
      * some C++ class specifiers;
      * usages of move semantics;
    * refactoring:
      * of the `append_node()` function;
      * of the `repetition_parser::parse()` method;
  * of the `utilities` module:
    * rename it to `exceptions`;
    * replace:
      * mutable instances in parameters to constant references;
    * remove:
      * usages of move semantics;
  * of the example:
    * combine in a single function:
      * `make_atom_parser()` and `make_expression_parser()` functions;
    * refactoring:
      * of the grammar;
      * of the `main()` function;
      * of the tests runner.

## [v2.2](https://github.com/thewizardplusplus/wizard-parser/tree/v2.2) (2018-12-23)

**Closed issues:**

- Simplify the building configurations
- Migrate to the C++17 standard:
  - Specify the standard in the building configurations
  - Replace the `optional` type from the [akrzemi1/Optional](https://github.com/akrzemi1/Optional) library to the `std::optional` type
  - Replace the `string_span` type from the [Microsoft/GSL](https://github.com/Microsoft/GSL) library to the `std::string_view` type
  - Use nested namespaces
- Update dependencies:
  - Update the [fmtlib/fmt](https://github.com/fmtlib/fmt) library to `v5.2.1`
  - Update the [Microsoft/GSL](https://github.com/Microsoft/GSL) library to `v2.0.0`
  - Update the [nlohmann/json](https://github.com/nlohmann/json) library to `v3.4.0`
  - Update the [docopt/docopt.cpp](https://github.com/docopt/docopt.cpp) library to `7476f8e` commit
- Project design:
  - Use upper-case names for service files
  - Fix the license information

## [v2.1](https://github.com/thewizardplusplus/wizard-parser/tree/v2.1) (2017-03-17)

**Closed issues:**

- Убрать ненужную универсальность из парсера флагов [\#23](https://github.com/thewizardplusplus/wizard-parser/issues/23)
- Вынести общую функциональность из парсеров с присваиванием [\#22](https://github.com/thewizardplusplus/wizard-parser/issues/22)
- Добавить парсер пустоты [\#21](https://github.com/thewizardplusplus/wizard-parser/issues/21)
- Добавить комбинатор списка с разделителем [\#20](https://github.com/thewizardplusplus/wizard-parser/issues/20)
- Заменить комбинатор опциональности на комбинатор повторений [\#19](https://github.com/thewizardplusplus/wizard-parser/issues/19)
- Добавить поддержку негативного просмотра вперёд в комбинатор просмотра вперёд [\#18](https://github.com/thewizardplusplus/wizard-parser/issues/18)
- Переименовать комбинатор сокрытия ноды в комбинатор просмотра вперёд [\#17](https://github.com/thewizardplusplus/wizard-parser/issues/17)
- Объединить парсеры определённого текста и определённой лексемы [\#16](https://github.com/thewizardplusplus/wizard-parser/issues/16)
- Добавить поддержку указания лимитов в комбинаторе повторений [\#15](https://github.com/thewizardplusplus/wizard-parser/issues/15)
- Заменить иерархию парсеров на её листья [\#14](https://github.com/thewizardplusplus/wizard-parser/issues/14)
- Заменить итераторы токенов на тип `span` из библиотеки [Microsoft/GSL](https://github.com/Microsoft/GSL) [\#13](https://github.com/thewizardplusplus/wizard-parser/issues/13)
- Заменить класс `lexer::tokenizer` на набор функций [\#12](https://github.com/thewizardplusplus/wizard-parser/issues/12)
- Заменить строковые итераторы на тип `string_span` из библиотеки [Microsoft/GSL](https://github.com/Microsoft/GSL) [\#11](https://github.com/thewizardplusplus/wizard-parser/issues/11)
- Добавить тесты из Wizard Steps \(на основе [Bats](https://github.com/sstephenson/bats)\) для примера [\#10](https://github.com/thewizardplusplus/wizard-parser/issues/10)
- Добавить поддержку чтения выражения из `stdin` в пример [\#9](https://github.com/thewizardplusplus/wizard-parser/issues/9)
- Добавить опцию `-t`/`--tokens` для вывода списка токенов в пример [\#8](https://github.com/thewizardplusplus/wizard-parser/issues/8)
- Использовать библиотеку [docopt/docopt.cpp](https://github.com/docopt/docopt.cpp) для парсинга опций в примере [\#7](https://github.com/thewizardplusplus/wizard-parser/issues/7)
- Использовать библиотеку [fmtlib/fmt](https://github.com/fmtlib/fmt) для форматирования строк [\#6](https://github.com/thewizardplusplus/wizard-parser/issues/6)
- Заменить флаг `parser::parsing_result::is_parsed` на тип `optional` из библиотеки [akrzemi1/Optional](https://github.com/akrzemi1/Optional) [\#5](https://github.com/thewizardplusplus/wizard-parser/issues/5)
- Заменить тип `std::pair<T, bool>` на тип `optional` из библиотеки [akrzemi1/Optional](https://github.com/akrzemi1/Optional) [\#4](https://github.com/thewizardplusplus/wizard-parser/issues/4)
- Удалить функцию `utilities::contains()` [\#3](https://github.com/thewizardplusplus/wizard-parser/issues/3)
- Использовать библиотеку [nlohmann/json](https://github.com/nlohmann/json) для сериализации [\#2](https://github.com/thewizardplusplus/wizard-parser/issues/2)
- Реализовать функцию `to_string()` в пару к каждой функции `operator<<()` [\#1](https://github.com/thewizardplusplus/wizard-parser/issues/1)

_This change log was automatically generated by [github_changelog_generator](https://github.com/skywinder/Github-Changelog-Generator)._

## [v2.0](https://github.com/thewizardplusplus/wizard-parser/tree/v2.0) (2017-02-20)

## [v1.0](https://github.com/thewizardplusplus/wizard-parser/tree/v1.0) (2015-03-29)
