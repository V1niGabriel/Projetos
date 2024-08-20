/*
Título: Poker de Dados
Descrição: Um jogo semelhante o poker que funciona com dados do computador.
Autor: Vinicius Gabriel
Data de Criação: 13/08/2024
*/

//Bibliotecas
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

//variavéis globais
int armazenamento[5], maior = 0;

//função de valor aleatório
void jogar_dados (){
	for (int j = 0; j < 5; j++){
		int n = (rand() % 6) + 1;
        armazenamento[j] = n; // Formula para gerar um numero aleatorio entre 1 e 6    
	}
}

//verifica se o número é maior
int verifica(int m){
	if (m > maior){
		maior = m;
	}
	return (maior);
}

//Linha 1 até 6 - soma de todos os 1's até 6's: Soma os valores igauis
int Soma_valor(int valor) {
	int retorno;
	retorno = 0;
	for (int i = 0; i < 5; i++) {
		if (armazenamento[i] == valor) {
			retorno += valor;
		}
	}
	return (retorno);
}

//Verificação do valor das linha 7 e 8: (caso haja 3 ou mais dados com o mesmo valor) - soma de todos os dados
int ganhar_ponto(int valor) {
	int cont; 
	int retorno;
	int copy_armazenamento[5];
	
	//cópia do vetor global amrazenamento para um vetor local
	for (int i = 0; i < 5; i++){
		copy_armazenamento[i] = armazenamento[i]; 
	}
	
	//conta a quantidade de repetições dos elementos presentes no vetor
	cont = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if ((armazenamento[i] == copy_armazenamento[j]) && i != j && copy_armazenamento[j] != 0){
				cont++;
				copy_armazenamento[j] = 0;
			}
		}
	}
	if (cont == valor) {
		int i = 0;
		retorno = 0;
		while (armazenamento[i] != '\0') {
			retorno += armazenamento[i];
			i++;
		}
	}
	
	return (retorno);	
}

//verificação da linha 9: caso haja 3 dados com um valor e 2 dados com o mesmo valor, diferente do primeiro - 25pt
int Par_trio () {
	int cont;
	int contadores[5], copy_armazenamento[5];
	
	//cópia do vetor global amrazenamento para um vetor local
	for (int i = 0; i < 5; i++){
		copy_armazenamento[i] = armazenamento[i]; 
	}
	
	for (int i = 0; i < 5; i++){
		cont = 0;
		for(int j = 0; j < 5; j++){
			if ((copy_armazenamento[i] == copy_armazenamento[j]) && i != j && copy_armazenamento[j] != 0){
				cont++;
				copy_armazenamento[j] = 0;
			}
		}
		contadores[i] = cont + 1;
	}
	
	if ((contadores[0] || contadores[1] == 2) && (contadores[0] || contadores[1] == 3) != 1){
		return (25);
	}
}

/*Verficação da linha 10 e 11: 
	Linha 10 (sequência menor): caso haja 4 ou mais dados em sequência - 30pt
	Linha 11 (sequência maior): caso haja 5 dados em sequência - 40pt
*/
int Sequencia_menor_maior(int valor) {
	int cont_sequencia; 
	
	cont_sequencia = 0;
	for(int a = 0; a < 5; a++) {
		//verifica se o valor atual é consecutivo do anterior 
		if (armazenamento[a] == armazenamento[a-1] + 1){
			cont_sequencia += 1;
		}
		else if (armazenamento[a] == armazenamento[a-1]) {
			continue;
		}
	}
	
	if (cont_sequencia >= valor) {
		if(valor = 4) {  //pontos da sequência menor (4)
			return(30);
		}
		else if (valor = 5) { //pontos da sequência maior (5)
			return(40);
		}
	}
	else {
		return (0);
	}
}

//Linha 12: caso todos os dados tenham o mesmo valor - 50pt
int iguais_os_5 () {
	int cont;
	
	cont = 0;
	for (int i = 0; i < 5; i++){
		if ((armazenamento[0] == armazenamento[i]) && 0 != i) {
			cont++;
		}
	}
	if (cont == 4){
		return (50);
	}
}

//Linha 13: com qualquer combinação de dados - a soma de todos os dados
int Reserva() {
	int somatorio;
	
	somatorio = 0;
	for (int i = 0; i < 5; i++){
		somatorio += armazenamento[i];
	}
	
	return (somatorio);
}

//Inicialização principal do código
int main() {
	
	srand(time(NULL)); // Server para gerar uma semente com numeros aleatórios
	
	char requisito[3]; //controle de rodada e continuação do jogo.
	char Linha[100];
	int jogador1[13] = {0}, jogador2[13] = {0};
	int retorno1, jogador_atual, soma, partida, Soma_total1, Soma_total2, comparador;
	int a, b, c;
	
	a = 0;
	b = 0;
	for (partida = 1; partida < 27; partida++) {
		printf("\nPARTIDA %d\n", partida);
		soma = 0;
		maior = 0;
		
		jogador_atual = (partida % 2) == 0 ? 2:1;
		
		printf("Jogador %d \nJogar os dados? [s/n]:", jogador_atual); // Quem tá jogando (Jogador 1 ou jogador 2).
		fgets(requisito, 2, stdin);
		while ((c = getchar()) != '\n' && c !=  EOF); //limpa o buffer
	
		if (requisito[0] == 's') {
			jogar_dados(); //chama a função de números aleatórios
			
			//Linha 1 até 6
			for (int n = 0; n < 7; n++){
				retorno1 = Soma_valor(n);
				soma = verifica(retorno1);
					
				//Linha 7 e 8
				if ((n == 3) || (n == 4)){ // 3 ou 4 -> pois é a quantidade de elemento repitidos necessários.
					retorno1 = ganhar_ponto(n); // n -> vai para "valor" na função ganhar_pontos.
					soma = verifica(retorno1);
				}
			}					
			//Linha 9
			retorno1 = Par_trio();
			soma = verifica(retorno1);
			//Linha 10 e 11
			for (int n = 4; n <= 5; n++){
				retorno1 = Sequencia_menor_maior(n);
				soma = verifica(retorno1);
			}
			//Linha 12
			retorno1 = iguais_os_5();
			soma = verifica(retorno1);
			//Linha 13
			retorno1 = Reserva();
			soma = verifica(retorno1);
			
			//Verificador da linha com maior pontuação
			for (int j = 1; j < 7; j++){
				if (comparador < Soma_valor(j)){
					comparador = Soma_valor(j);
					if ((comparador % 1) == 0){
						strcpy(Linha, "Linha 1, Soma todos os 1's");
					}
					else if((comparador % 2) == 0 && ((comparador % 4) != 0)){
						strcpy(Linha, "Linha 2, Soma todos os 2's");
					}
					else if ((comparador % 3) == 0) {	
					}
				}
			}
				
			//Armazenamento dos pontos das rodadas
			if (jogador_atual == 1){
				jogador1[a] = soma;
				printf("Pontuacao(1): %d\n", jogador1[a]);
				a++;
			}
			else {
				jogador2[b] = soma;
				printf("Pontuacao(2): %d\n", jogador2[b]);
				b++;
			}
		}
		else {
			if (jogador_atual == 1){
				jogador1[a] = 0;
				a++;
			}
			else {
				jogador2[b] = 0;
				b++;
			}
			continue;
		}
	}
	Soma_total1 = 0;
	Soma_total2 = 0;
	//Soma de todos  os pontos
	for (int n = 0; n < 13; n++){
		Soma_total1 += jogador1[n];
		Soma_total2 += jogador2[n];
	}
	
	//Saída de dados;
	printf("\nPontuacao Total\n Jogador1: %d\n Jogador2: %d\n", Soma_total1, Soma_total2);
		if (Soma_total1 > Soma_total2){
		printf("JOGADOR 1 VENCEDOR!!!!!!!");
	}
	else {
		printf("JOGADOR 2 VENCEDOR!!!!!!!");
	}

		
	return 0;
}
