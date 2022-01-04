%{

%}

%%

double 					printf("a\t %s\n", yytext);
int					printf("b\t %s\n", yytext);
main 					printf("c\t %s\n", yytext);
return 					printf("d\t %s\n", yytext);
cout 					printf("t\t %s\n", yytext);
cin 					printf("f\t %s\n", yytext);
[0-9]+\.[0-9]+				printf("g\t %s\n", yytext);
[1-9]+[0-9]*|0				printf("h\t %s\n", yytext);
";"					printf("i\t %s\n", yytext);
"<<"					printf("j\t %s\n", yytext);
">>"					printf("k\t %s\n", yytext);
"="					printf("l\t %s\n", yytext);
"*"					printf("m\t %s\n", yytext);
"+"					printf("n\t %s\n", yytext);
"-"					printf("o\t %s\n", yytext);
"("					printf("p\t %s\n", yytext);
")"					printf("q\t %s\n", yytext);
"{"					printf("r\t %s\n", yytext);
"}"					printf("s\t %s\n", yytext);
[a-zA-Z]{9,} 				printf("The id: %s is too long\n", yytext);
[a-zA-Z]{1,8} 				printf("z\t %s\n", yytext);
[ \t\n]+				/* skip whitespace */
.					printf("Something is wrong with\t %s\n", yytext);

%%

int yywrap(){}

int main(){

	yylex();
	return 0;
}
