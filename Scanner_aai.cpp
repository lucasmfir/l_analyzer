/****************************************************************************************************
 * Universidade FUMEC             									                                *
 * Autoinstrucional - Compiladores
 * Alunos: Lucas Firmo
 *         Luís Henrique C. Oliviera
 ****************************************************************************************************/

//Bibliotecas
#include <stdio.h>
//#include <curses.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

//Define's
#define oper "+/-*><"
#define num  "0123456789"
#define letra  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

int search(char a, const char * str) {
	int j = 0, ret = 0;
	while (str[j] && !ret) {
		ret = (str[j] == a);
		j++;
	}
	return (ret);
}

int scanner(char automato[100]) {
	int i = 0, state = 0;
	while (state != 19) {
		switch (state) {
  		case 0:
  			while (automato[i] == ' ') {
  				i++;
  			}
  			if (automato[i] == '/') {
  				state = 1;
  				i++;
  			} else if (search(automato[i], letra)) {
  				state = 2;
  				i++;
  			} else {
  				return state;
  			}
  			break;

  		case 1:
  			if (automato[i] == '*') {
  				state = 3;
          i++;
  			} else {
  				return state;
  			}
  			break;

  		case 2:
  			while ( search(automato[i], num) || search(automato[i], letra) ) {
          i++;
        }
        if (automato[i] == ' ') {
          state = 5;
          i++;
        }else if (automato[i] == '=') {
          state = 6;
          i++;
        }else if (automato[i] == '/') {
          state = 7;
          i++;
  			} else {
  				return state;
  			}
  			break;

      case 3:
        while ( automato[i] == '=' || 
				search(automato[i], num) ||
                search(automato[i], letra) ||
                search(automato[i], oper) &&
                automato[i] != '*') {
          i++;
        }
        if(automato[i] == '*') {
          state = 4;
          i++;
        }else{
          return state;
        }
        break;

      case 4:
        while ( automato[i] == '*' ) {
          i++;
        }
        if( automato[i] == '/') {
          state = 0;
          i++;
        }else if ( automato[i] == '=' || 
				   search(automato[i], num) ||
                   search(automato[i], letra) ||
                   search(automato[i], oper)) {
          state = 3;
          i++;
        }else{
          return state;
        }
        break;

        case 5:
          while( automato[i] == ' ') {
            i++;
          }
          if ( automato[i] == '=') {
            state = 6;
            i++;
          }else if ( automato[i] == '/') {
            state = 7;
            i++;
          }else{
            return state;
          }
          break;

        case 6:
          while ( automato[i] == ' ' ) {
            i++;
          }
          if ( search(automato[i], num) ) {
            state = 10;
            i++;
          }else if ( search(automato[i], letra) ) {
            state = 11;
            i++;
          }else if ( automato[i] == '/') {
            state = 12;
            i++;
          }else {
            return state;
          }
          break;

        case 7:
          if ( automato[i] == '*') {
            state = 8;
            i++;
          }else{
            return state;
          }
          break;

        case 8:
          while (automato[i] == '=' || 
		  		 search(automato[i], num) ||
                 search(automato[i], letra) ||
                 search(automato[i], oper) &&
                 automato[i] != '*') {
            i++;
          }
          if ( automato[i] == '*') {
            state = 9;
            i++;
          }else{
            return state;
          }
          break;

        case 9:
          while ( automato[i] == '*') {
            i++;
          }
          if ( automato[i] == '/') {
            state = 5;
            i++;
          }else if ( automato[i] == '=' || 
		  			 search(automato[i], num) ||
               		 search(automato[i], letra) ||
               		 search(automato[i], oper)) {
            state = 8;
            i++;
          }else{
            return state;
          }
          break;

        case 10:
          while ( search(automato[i], num) ) {
            i++;
          }
          if ( automato[i] == '/' ) {
            state = 16;
            i++;
          }else if ( automato[i] == ' ' ) {
            state = 13;
            i++;
          } else if ( search(automato[i], oper)) {
            state = 6;
            i++;
          } else if (automato[i] == 10 || automato[i] == 13) {
    				state = 19;
    			} else {
    				return state;
          }
          break;

        case 11:
          while ( search(automato[i], num) ||
                  search(automato[i], letra)) {
            i++;
          }
          if ( automato[i] == '/' ) {
            state = 16;
            i++;
          }else if ( search(automato[i], oper) ) {
            state = 6;
            i++;
          }else if (automato[i] == ' ') {
            state = 13;
            i++;
          } else if (automato[i] == 10 || automato[i] == 13) {
    				state = 19;
    			} else {
    				return state;
          }
          break;

        case 12:
          if ( automato[i] == '*') {
            state = 14;
            i++;
          }else{
            return state;
          }
          break;

        case 13:
          while ( automato[i] == ' ' ) {
            i++;
          }
          if ( automato[i] == '/') {
            state = 16;
            i++;
          } else if (search(automato[i], oper) ) {
            state = 6;
            i++;
          } else if (automato[i] == 10 || automato[i] == 13) {
    				state = 19;
    			} else {
    				return state;
          }
          break;

        case 14:
          while ( automato[i] == '=' || 
		  		  search(automato[i], num) ||
                  search(automato[i], letra) ||
                  search(automato[i], oper) &&
                  automato[i] != '*') {
            i++;
          }
          if ( automato[i] == '*' ) {
            state = 15;
            i++;
          }else{
            return state;
          }
          break;

        case 15:
          while ( automato[i] == '*' ) {
            i++;
          }
          if ( automato[i] == '/' ) {
            state = 6;
            i++;
          }else if ( automato[i] == '=' || 
		  			 search(automato[i], num) ||
                     search(automato[i], letra) ||
                     search(automato[i], oper) &&
                     automato[i] != '*') {
            state = 14;
            i++;
          }else{
            return state;
          }
          break;

        case 16:
          if ( automato[i] == '*' ) {
            state = 17;
            i++;
          } else if ( automato[i] == ' ' ) {
            state = 6;
            i++;
          } else if ( search(automato[i], num) ) {
            state = 10;
            i++;
          } else if ( search(automato[i], letra) ) {
            state = 11;
            i++;
          } 
		  else {
            return state;
          }
          break;

        case 17:
          while( automato[i] == '=' || 
		  		 search(automato[i], num) ||
                 search(automato[i], letra) ||
                 search(automato[i], oper) &&
                 automato[i] != '*') {
            i++;
          }
          if( automato[i] == '*') {
            state = 18;
            i++;
          }else{
            return state;
          }
          break;

        case 18:
          while ( automato[i] == '*' ) {
            i++;
          }
          if ( automato[i] == '/' ) {
            state = 13;
            i++;
          }else if (automato[i] == '=' || 
		  			search(automato[i], num) ||
                    search(automato[i], letra) ||
                    search(automato[i], oper) &&
                    automato[i] != '*') {
            state = 17;
            i++;
          }else{
            return state;
          }
          break;
    }
  }
	return -1;
}

int main(void) {
	char massaF[100], resultados[200], *expressoes[200];
	printf("\tTrabalho Autoinstrucional - Lucas Firmo e Luís Henrique\n");
	printf("\nDigite o nome do arquivo de teste:");

	scanf("%s", massaF);
	FILE * pFile, *pFile2;
	char mystring[100];

	pFile = fopen(massaF, "r");

	pFile2 = fopen("saida.txt", "w+");

	if (pFile == NULL)
		perror("Error opening file");
	else {
		int i = 0;
		while (fgets(mystring, 100 * 100, pFile) != NULL) {
			if (scanner(mystring) == -1) {
				printf("\n%d - Expressao correta", i);
        printf("\n%s", mystring);
				fprintf(pFile2, "\nExpressao correta - %s", mystring);
			} else {
				printf("\n%d - Expressao Incorreta - State: %d",
						i, scanner(mystring));
        printf("\n%s", mystring);
        fprintf(pFile2, "\nExpressao Incorreta State: %d - %s",
						scanner(mystring), mystring);
			}
			i++;
		}
		fclose(pFile);
		fclose(pFile2);
		getch();
	}
}
