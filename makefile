makelexical: LexicalAnalyzer.c ./Machines/idres.c ./Machines/whitespace.c ./DataStructures/LinkedList.c reservedWords.c SymbolTable.c
	gcc -o Lex LexicalAnalyzer.c ./Machines/idres.c ./Machines/whitespace.c ./DataStructures/LinkedList.c	reservedWords.c SymbolTable.c
