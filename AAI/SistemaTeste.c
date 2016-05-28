#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "MinhaString.h"

typedef struct {
	char nome[120];
	char endereco[120];
	char dataNascimento[11];
} usuario;
int MenuPrincipal();
int Menu1();
int Menu2();
//int validarData(char *data);
	
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	String string = NEW;

	int users;
	printf("Informe a quantidade de usuário que devem ser cadastrados: ");
	scanf("%d", &users);
	
	usuario *u;
	u = (usuario *)malloc(users * sizeof(usuario));
	
	system("cls");
	
	printf("|**** CADASTRANDO OS USUÁRIOS NO SISTEMA ****|\n");
	int i;
	for(i = 0; i < users; i++) {
		do {
			printf("Informe o nome do Usuário %d: ", i+1);
			fflush(stdin);
			gets(u->nome);
		} while (1 != 1);
		printf("\n");
		do {
			printf("Informe o endereço do Usuário %d: ", i+1);
			fflush(stdin);
			gets(u->endereco);
		} while (1 != 1);
		printf("\n");
		do {
			printf("Informe a data de nascimento do Usuário %d: ", i+1);
			fflush(stdin);
			gets(u->dataNascimento);
		} while ((string.firstIndexOf(u->dataNascimento, '/') != 3) || (string.lastIndexOf(u->dataNascimento, '/') != 6));
		printf("\n");
		printf("|****                       PROXÍMO                       ****|\n");
	}
	
	system("cls");
	
	int op = MenuPrincipal();
	
	system("cls");
	
	switch(op) {
		case 1:
			op = Menu1();
			if(op == 1) {
				// Mostrar número da casa
				char numero[5];
				system("cls");
				for(i = 0; i < users; i++) {
				    string.substring(u->endereco, numero, string.firstIndexOf(u->endereco, ','), string.length(u->endereco));
					printf("Número da casa do usuário %d: %s \n", i+1, numero);
				}
				
			} else if(op == 2) {
				// Mostrar ano de nascimento
				char ano[5];
				system("cls");
				for(i = 0; i < users; i++) {
				    string.substring(u->dataNascimento, ano, string.lastIndexOf(u->dataNascimento, '/'), string.length(u->dataNascimento));
					printf("Ano de nascimento do usuário %d: %s \n", i+1, ano);
				}
				
			} else if(op == 3) {
				// Mostrar mes de nascimento
				char mes[3];
				system("cls");
				for(i = 0; i < users; i++) {
				    string.substring(u->dataNascimento, mes, string.firstIndexOf(u->dataNascimento, '/'), string.length(u->dataNascimento));
					printf("Mês de nascimento do usuário %d: %s \n", i+1, mes);
				}
				
			} else if(op == 4) {
				// Mostrar dia de nascimento
				char dia[3];
				system("cls");
				for(i = 0; i < users; i++) {
				    string.substring(u->dataNascimento, dia, string.lastIndexOf(u->dataNascimento, '/'), string.length(u->dataNascimento));
					printf("Ano de nascimento do usuário %d: %s \n", i+1, dia);
				}
				
			} else if(op == 5) {
				// Mostrar ultimo nome
				char ultimoNome[20];
				system("cls");
				for(i = 0; i < users; i++){
					string.substring(u->nome, ultimoNome, string.lastIndexOf(u->nome, ' '), string.length(u->nome));
					printf("Último sobrenome do usuário %d: %s \n", i+1, ultimoNome);
				}
				
			} else if(op == 6) {
				// Mostrar primeiro nome
				char primeiroNome[20];
				system("cls");
				for(i = 0; i < users; i++){
					string.substring(u->nome, primeiroNome, string.firstIndexOf(u->nome, ' '), string.length(u->nome));
					printf("Primeiro nome do usuário %d: %s \n", i+1, primeiroNome);
				}
				
			} else if(op == 7) {
				// Mostrar os nome do meio
				char meioNome[20];
				system("cls");
				for(i = 0; i < users; i++){
					string.substring(u->nome, meioNome, string.firstIndexOf(u->nome, ' '), string.length(u->nome));
					printf("Nome(s) do meio do usuário %d: %s \n", i+1, meioNome);
				}
				
			} else {
				exit(0);
			}
			break;
		case 2:
			op = Menu2();
			if(op == 1) {
				// Pesquisa pelo nº casa
				printf("Informe o número para pesquisa: ");
				fflush(stdin);
				char numeroPesquisa[5];
				gets(numeroPesquisa);
			
				char numero[5];
				for(i = 0; i < users; i++) {
				    string.substring(u->endereco, numero, string.firstIndexOf(u->endereco, ','), string.length(u->endereco));
					if(string.equals(numeroPesquisa,numero) == 1){
						printf("\nNome do Usuário %s: ", u->nome);		
						printf("\nEndereço do Usuário %s: ", u->endereco);		
						printf("\nData de nascimento do Usuário %s: ", u->dataNascimento);			
					}
				}
			} else if(op == 2) {
				// Pesquisa pelo sobrenome
				printf("Informe o sobrenome para pesquisa: ");
				fflush(stdin);
				char sobrenomePesquisa[20];
				gets(sobrenomePesquisa);
			
				char sobrenome[20];
				for(i = 0; i < users; i++) {
				    string.substring(u->nome, sobrenome, string.lastIndexOf(u->nome, ' '), string.length(u->nome));
					if(string.equals(sobrenomePesquisa,sobrenome) == 1){
						printf("\nNome do Usuário %s: ", u->nome);		
						printf("\nEndereço do Usuário %s: ", u->endereco);		
						printf("\nData de nascimento do Usuário %s: ", u->dataNascimento);			
					}
				}
		
			} else if(op == 3) {
				// Pesquisa pelo ano de nascimento
				printf("Informe o ano para pesquisa: ");
				fflush(stdin);
				char anoPesquisa[5];
				gets(anoPesquisa);
				
				char ano[5];
				for(i = 0; i < users; i++) {
				    string.substring(u->dataNascimento, ano, string.lastIndexOf(u->dataNascimento, '/'), string.length(u->dataNascimento));
					if(string.equals(anoPesquisa,ano) == 1){
						printf("\nNome do Usuário %s: ", u->nome);		
						printf("\nEndereço do Usuário %s: ", u->endereco);		
						printf("\nData de nascimento do Usuário %s: ", u->dataNascimento);			
					}
				}
				
			} else if(op == 4) {
				// Pesquisa pelo mes de nascimento
				printf("Informe o mês para pesquisa: ");
				fflush(stdin);
				char mesPesquisa[3];
				gets(mesPesquisa);
				
				char mes[3];
				for(i = 0; i < users; i++) {
				    string.substring(u->dataNascimento, mes, string.firstIndexOf(u->dataNascimento, '/'), string.length(u->dataNascimento));
					if(string.equals(mesPesquisa,mes) == 1){
						printf("\nNome do Usuário %s: ", u->nome);		
						printf("\nEndereço do Usuário %s: ", u->endereco);		
						printf("\nData de nascimento do Usuário %s: ", u->dataNascimento);			
					}
				}
				
			} else {
				exit(0);
			}
			break;
		default:
			exit(0);
			break;
	}
	
	free(u);
	system("pause");
	return 0;
}

int MenuPrincipal() {
	int opcao = 0;
	printf("|******************************|\n");
	printf("| 1 - Listagem                 |\n");
	printf("| 2 - Pesquisa                 |\n");
	printf("| 0, 3 ou outro - SAIR         |\n");
	printf("|******************************|");
	printf("\n");
	scanf("%d",&opcao);
	
	return opcao;
}

int Menu1() {
	int opcao = 0;
	printf("|**************************************************|\n");
	printf("| 1 - Mostrar apenas o número da casa              |\n");
	printf("| 2 - Mostrar Ano do nascimento                    |\n");
	printf("| 3 - Mostrar Mês do nascimento                    |\n");
	printf("| 4 - Mostrar Dia do nascimento                    |\n");
	printf("| 5 - Mostrar qual o último Sobrenome              |\n");
	printf("| 6 - Mostrar o primeiro nome                      |\n");
	printf("| 7 - Mostrar os nomes do meio, caso houver        |\n");
	printf("| 8, 9 ou outro - SAIR                             |\n");
	printf("|**************************************************|");
	printf("\n");
	scanf("%d",&opcao);
	
	return opcao;
}

int Menu2() {
	int opcao = 0;
	printf("|**************************************************|\n");
	printf("| 1 - Buscar por número de casa                    |\n");
	printf("| 2 - Buscar pessoas pelo sobrenome                |\n");
	printf("| 3 - Buscar pessoas pelo ano de nascimento        |\n");
	printf("| 4 - Buscar pessoas pelo mês de nascimento        |\n");
	printf("| 5, 6 ou outro - SAIR                             |\n");
	printf("|**************************************************|");
	printf("\n");
	scanf("%d",&opcao);
	
	return opcao;
}

/*int validarData(char *data) { // 0 - erro | 1 - ok
	printf("|%s| - ", data);
	char dia[2];
	dia[0] = data[0];
	dia[1] = data[1];
	char mes[2];
	mes[0] = data[3];
	mes[1] = data[4];
	char ano[4];
	ano[0] = data[6];
	ano[1] = data[7];
	ano[2] = data[8];
	ano[3] = data[9];
	printf("|%s| - ", dia);
	printf("|%s & %s| - ", data[3], data[4]);
	printf("|%s| - ", ano);
	if((string.firstIndexOf(u->dataNascimento, '/') == 3) && (string.lastIndexOf(u->dataNascimento, '/') == 6)) {
		//string.substring(data, data, 0, 2);
		//printf("[%s] - ", data);
		//if(data < 32 && data > 0) {
		if(dia < 32 && dia > 0) {
			//string.substring(u->dataNascimento, data, 3, 5);
			//printf("{%s} - ", data);
			//if(data < 13 && data > 0) {
			if(mes < 13 && mes > 0) {
				//string.substring(u->dataNascimento, data, 6, 9);
				//printf("(%s) ¬", data);
				//if(data < 2016 && data > 1900)
				if(ano < 2016 && ano > 1900)
					return 1;
			}
		}
	} else {
		return 0;
	}
}*/
