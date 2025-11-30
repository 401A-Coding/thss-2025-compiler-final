lexer grammar SysYLexer;

// 关键字
CONST: 'const';
INT: 'int';
VOID: 'void';
IF: 'if';
ELSE: 'else';
WHILE: 'while';
BREAK: 'break';
CONTINUE: 'continue';
RETURN: 'return';

// 运算符
PLUS: '+';
MINUS: '-';
MUL: '*';
DIV: '/';
MOD: '%';
ASSIGN: '=';
EQ: '==';
NEQ: '!=';
LT: '<';
GT: '>';
LE: '<=';
GE: '>=';
NOT: '!';
AND: '&&';
OR: '||';

// 分隔符
L_PAREN: '(';
R_PAREN: ')';
L_BRACE: '{';
R_BRACE: '}';
L_BRACKT: '[';
R_BRACKT: ']';
COMMA: ',';
SEMICOLON: ';';

// 标识符和常量
IDENT: [a-zA-Z_] [a-zA-Z0-9_]*;
INTEGER_CONST:
	'0' [0-7]* // 八进制
	| [1-9] [0-9]* // 十进制
	| '0' [xX] [0-9a-fA-F]+; // 十六进制

// 空白和注释
WS: [ \r\n\t]+ -> skip;
LINE_COMMENT: '//' .*? '\n' -> skip;
MULTILINE_COMMENT: '/*' .*? '*/' -> skip;