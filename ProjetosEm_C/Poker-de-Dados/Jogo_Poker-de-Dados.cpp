/*
T�tulo: Poker de Dados
Descri��o: Um jogo semelhante o poker que funciona com dados do computador.
Autor: Vinicius Gabriel
Data de Cria��o: 13/08/2024
*/

//Bibliotecas
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

//variav�is globais
int armazenamento[5], maior = 0;

//fun��o de valor aleat�rio
void jogar_dados (){
	for (int j = 0; j < 5; j++){
		int n = (rand() % 6) + 1;
        armazenamento[j] = n; // Formula para gerar um numero aleatorio entre 1 e 6    
	}
}

//verifica se o n�mero � maior
int verifica(int m){
	if (m > maior){
		maior = m;
	}
	return (maior);
}

//Linha 1 at� 6 - soma de todos os 1's at� 6's: Soma os valores igauis
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

//Verifica��o do valor das linha 7 e 8: (caso haja 3 ou mais dados com o mesmo valor) - soma de todos os dados
int ganhar_ponto(int valor) {
	int cont; 
	int retorno;
	int copy_armazenamento[5];
	
	//c�pia do vetor global amrazenamento para um vetor local
	for (int i = 0; i < 5; i++){
		copy_armazenamento[i] = armazenamento[i]; 
	}
	
	//conta a quantidade de repeti��es dos elementos presentes no vetor
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

//verifica��o da linha 9: caso haja 3 dados com um valor e 2 dados com o mesmo valor, diferente do primeiro - 25pt
int Par_trio () {
	int cont;
	int contadores[5], copy_armazenamento[5];
	
	//c�pia do vetor global amrazenamento para um vetor local
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
	
	if ((contadores[0] || contadores[1] == 2) && (contadores[0] || contadores[1] == 3)){
		return (25);
	}
}

/*Verfica��o da linha 10 e 11: 
	Linha 10 (sequ�ncia menor): caso haja 4 ou mais dados em sequ�ncia - 30pt
	Linha 11 (sequ�ncia maior): caso haja 5 dados em sequ�ncia - 40pt
*/
int Sequencia_menor_maior(int valor) {
	int cont_sequencia; 
	
	cont_sequencia = 0;
	for(int a = 0; a < 5; a++) {
		//verifica se o valor atual � consecutivo do anterior 
		if (armazenamento[a] == armazenamento[a-1] + 1){
			cont_sequencia += 1;
		}
		else if (armazenamento[a] == armazenamento[a-1]) {
			continue;
		}
	}
	
	if (cont_sequencia >= valor) {
		if(valor = 4) {  //pontos da sequ�ncia menor (4)
			return(30);
		}
		else if (valor = 5) { //pontos da sequ�ncia maior (5)
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

//Linha 13: com qualquer combina��o de dados - a soma de todos os dados
int Reserva() {
	int somatorio;
	
	somatorio = 0;
	for (int i = 0; i < 5; i++){
		somatorio += armazenamento[i];
	}
	
	return (somatorio);
}

//Inicializa��o principal do c�digo
int main() {
	
	srand(time(NULL)); // Server para gerar uma semente com numeros aleat�rios
	
	char requisito[3]; //controle de rodada e continua��o do jogo.
	int jogador1[13], jogador2[13];
	int retorno1, jogador_atual, soma, partida;
	int a, b, c;
	
	for (partida = 1; partida < 27; partida++) {
		printf("\nPARTIDA %d\n", partida);
		
		jogador_atual = (partida % 2) == 0 ? 2:1;
		
		printf("Jogador %d \nJogar os dados? [s/n]:", jogador_atual); // Quem t� jogando (Jogador 1 ou jogador 2).
		fgets(requisito, 2, stdin);
		while ((c = getchar()) != '\n' && c !=  EOF); //limpa o buffer
	
		if (requisito[0] == 's') {
			jogar_dados(); //chama a fun��o de n�meros aleat�rios
			
			//Linha 1 at� 6
			for (int n = 0; n < 7; n++){
				retorno1 = Soma_valor(n);
				soma = verifica(retorno1);
					
				//Linha 7 e 8
				if ((n == 3) || (n == 4)){ // 3 ou 4 -> pois � a quantidade de elemento repitidos necess�rios.
					retorno1 = ganhar_ponto(n); // n -> vai para "valor" na fun��o ganhar_pontos.
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
				
			//Armazenamento dos pontos das rodadas
			if (jogador_atual == 1){
				jogador1[a] = soma;
				a++;
			}
			else {
				jogador2[b] = soma;
				b++;
			}
		}
		else {
			continue;
		}
	}
		
	return 0;
}


