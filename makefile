makelexical: LexicalAnalyzer.c ./Machines/idres.c ./Machines/whitespace.c ./LinkedLists/TokenLinkedList.c reservedWords.c SymbolTable.c ./Machines/Catchall.c ./Machines/Relop.c ./Machines/Number.c
	gcc -o Lex LexicalAnalyzer.c ./Machines/idres.c ./Machines/whitespace.c ./LinkedLists/TokenLinkedList.c reservedWords.c SymbolTable.c ./Machines/Catchall.c ./Machines/Relop.c ./Machines/Number.c
