### Грамматика

```
expression = sum;

sum = product, {("+" | "-"), product};
product = unary, {("*" | "/" | "%"), unary};
unary = {"-"}, atom;

atom = NUMBER | IDENTIFIER | function call | ("(", expression, ")");
function call = IDENTIFIER, "(", [expression, {",", expression}], ")";

NUMBER = ? /\d+(\.\d+)?(e-?\d+)?/ ?;
IDENTIFIER = ? /[a-z_]\w*/i ?;
```
