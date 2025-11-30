parser grammar SysYParser;

options {
	tokenVocab = SysYLexer;
}

// 编译单元：多个声明或函数定义
compUnit: (decl | funcDef)+;

// 声明：常量声明/变量声明
decl: constDecl | varDecl;

// 常量声明
constDecl:
	CONST bType constDef (COMMA constDef)* SEMICOLON # ConstDeclDef;
bType: INT # IntType; // 基础类型（仅int）

// 常量定义
constDef:
	IDENT (L_BRACKT constExp R_BRACKT)* ASSIGN constInitVal;

// 常量初始化值
constInitVal:
	constExp												# ConstExpInitVal
	| L_BRACE (constInitVal (COMMA constInitVal)*)? R_BRACE	# ConstArrayInitVal;

// 变量声明
varDecl: bType varDef (COMMA varDef)* SEMICOLON # VarDeclDef;

// 变量定义（有无初始化）
varDef:
	IDENT (L_BRACKT constExp R_BRACKT)*						# VarDefNoInit
	| IDENT (L_BRACKT constExp R_BRACKT)* ASSIGN initVal	# VarDefWithInit;

// 变量初始化值
initVal:
	exp												# ExpInitVal
	| L_BRACE (initVal (COMMA initVal)*)? R_BRACE	# ArrayInitVal;

// 函数定义
funcDef: funcType IDENT L_PAREN funcFParams? R_PAREN block;
funcType: VOID # VoidFuncType | INT # IntFuncType; // 函数返回类型

// 函数形参列表
funcFParams: funcFParam (COMMA funcFParam)*;
funcFParam: bType IDENT arrayDim?; // 形参（含数组维度）
arrayDim: (L_BRACKT R_BRACKT) (L_BRACKT exp R_BRACKT)*; // 数组维度（如[]/[exp]）

// 代码块
block: L_BRACE (blockItem)* R_BRACE;
blockItem:
	decl	# BlockItemDecl
	| stmt	# BlockItemStmt; // 块内元素：声明/语句

// 语句
stmt:
	lVal ASSIGN exp SEMICOLON					# AssignStmt
	| exp? SEMICOLON							# ExprStmt
	| block										# BlockStmt
	| IF L_PAREN cond R_PAREN stmt (ELSE stmt)?	# IfStmt
	| WHILE L_PAREN cond R_PAREN stmt			# WhileStmt
	| BREAK SEMICOLON							# BreakStmt
	| CONTINUE SEMICOLON						# ContinueStmt
	| RETURN exp? SEMICOLON						# ReturnStmt;

// 表达式
exp: addExp # ExpAddExp;

// 左值（变量/数组元素）
lVal: IDENT (L_BRACKT exp R_BRACKT)*;

// 条件表达式（逻辑或表达式）
cond: lOrExp # CondLOrExp;

// 基本表达式
primaryExp:
	L_PAREN exp R_PAREN	# ParenExp
	| lVal				# LValPrimaryExp
	| number			# NumberPrimaryExp;

// 数值
number: INTEGER_CONST # IntegerNumber;

// 一元表达式
unaryExp:
	primaryExp								# PrimaryUnaryExp
	| IDENT L_PAREN funcRParams? R_PAREN	# FuncCallUnaryExp
	| unaryOp unaryExp						# UnaryOpExp;

// 单目运算符
unaryOp:
	PLUS	# PlusUnaryOp
	| MINUS	# MinusUnaryOp
	| NOT	# NotUnaryOp;

// 函数实参列表
funcRParams: exp (COMMA exp)*;

// 乘除模表达式
mulExp:
	unaryExp							# UnaryMulExp
	| mulExp (MUL | DIV | MOD) unaryExp	# BinaryMulExp;

// 加减表达式
addExp:
	mulExp							# MulAddExp
	| addExp (PLUS | MINUS) mulExp	# BinaryAddExp;

// 关系表达式
relExp:
	addExp								# AddRelExp
	| relExp (LT | GT | LE | GE) addExp	# BinaryRelExp;

// 相等性表达式
eqExp:
	relExp						# RelEqExp
	| eqExp (EQ | NEQ) relExp	# BinaryEqExp;

// 逻辑与表达式
lAndExp: eqExp # EqLAndExp | lAndExp AND eqExp # BinaryLAndExp;

// 逻辑或表达式
lOrExp: lAndExp # LAndLOrExp | lOrExp OR lAndExp # BinaryLOrExp;

// 常量表达式（用于数组维度/常量初始化）
constExp: addExp;