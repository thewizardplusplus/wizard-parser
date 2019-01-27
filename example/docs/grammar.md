### Грамматика

```
expression = disjunction;
disjunction = conjunction, {"or", conjunction};
conjunction = equality, {"and", equality};
equality = comparison, {("==" | "/="), comparison};
comparison = sum, {("<" | "<=" | ">" | ">="), sum};
sum = product, {("+" | "-"), product};
product = unary, {("*" | "/" | "%"), unary};
unary = {"-" | "not"}, atom;

atom = NUMBER | identifier | function call | ("(", expression, ")");
identifier = BASE IDENTIFIER - key words;
key words = "not" | "and" | "or";
function call = identifier, "(", [expression, {",", expression}], ")";

NUMBER = ? /\d+(\.\d+)?(e-?\d+)?/ ?;
BASE IDENTIFIER = ? /[a-z_]\w*/i ?;
```
