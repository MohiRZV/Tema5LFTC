%{

%}

%%

int|double|main|return|cout|cin 	printf("Keyword:\t %s\n", yytext);
[0-9]+\.[0-9]+				printf("Double:\t %s\n", yytext);
[1-9]+[0-9]*|0				printf("Integer:\t %s\n", yytext);
";"|"<<"|">>"|"="|"*"|"+"|"-"		printf("Operator:\t %s\n", yytext);
"("|")"|"{"|"}"				printf("Paranthesis:\t %s\n", yytext);
[a-zA-Z]{9,} 				printf("The id: %s is too long\n", yytext);
[a-zA-Z]{1,8} 				printf("Identifier:\t %s\n", yytext);
[ \t\n]+				/* skip whitespace */
.					printf("Something is wrong with\t %s\n", yytext);

%%

int yywrap(){}

int main(){

	yylex();
	return 0;
}
