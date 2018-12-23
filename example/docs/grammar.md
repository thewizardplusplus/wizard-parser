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

atom = NUMBER CONSTANT | identifier | function call | ("(", expression, ")");
identifier = BASE IDENTIFIER - key words;
function call = identifier, "(", [expression, {",", expression}], ")";

NUMBER CONSTANT = ? /\d+(\.\d+)?(e-?\d+)?/ ?;
BASE IDENTIFIER = ? /[a-z_]\w*/i ?;

key words = "and" | "not" | "or";
```
