# Change Log

## [v2.2](https://github.com/thewizardplusplus/wizard-parser/tree/v2.2) (2018-12-01)

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