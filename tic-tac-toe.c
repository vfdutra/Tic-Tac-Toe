#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool converte_jogada(char jogada1[], int *lin, int *col);
void verJogo(char jogo[][3]);
bool testeVitoria(char jogo[][3], char nome1[], char nome2[], char jogador);

int main(void)
{
  char jogo[3][3] = {'-','-','-','-','-','-','-','-','-',};
  char nome[100], nome1[100], nome2[100], jogada[100], jogador;
  bool vitoria, jogada_valida, deu_velha = false;
  int  linha, coluna, vez = 1;
  int *lin = &linha, *col = &coluna;
  printf("Digite o nome do jogador X\n");
  scanf(" %[^\n]s", nome1);
  printf("\n");
  printf("Digite o nome do jogador O\n");
  scanf(" %[^\n]s", nome2);
  printf("\n");
  do{
    if(vez % 2 == 0){
      jogador = 'O';
      strcpy(nome, nome2);
    }else{
      jogador = 'X';
      strcpy(nome, nome1);
    }
    printf("\nDigite a jogada\n");
    do{
      verJogo(jogo);
      printf("Jogada de %s (%c)\n", nome, jogador);
      scanf(" %[^\n]s", jogada);
      jogada_valida = converte_jogada(jogada,lin,col);
      if(jogo[linha][coluna] == '-' && jogada_valida == true){
        jogo[linha][coluna] = jogador;
      }else{
        printf("\nJogada invalida\n");
        jogada_valida = false;
      }
      if(vez > 8){
        deu_velha = true;
	break;
      }
    }while(!jogada_valida);

    vitoria = testeVitoria(jogo, nome1, nome2, jogador);
    vez++;

    if(deu_velha == true){
      printf("\nDeu Velha\n");
      break;
    }

  }while(!vitoria);

  verJogo(jogo);
}

//Funcao que mostra o jogo na tela, recebe a matriz preenchida ate o momento e nao tem retorno
void verJogo(char jogo[][3])
{
  for(int linha = 0; linha < 3; linha++){
    for(int coluna = 0; coluna < 3;coluna++){
      printf("%c ",jogo[linha][coluna]);
    }
    printf("\n");
  }
  printf("\n");
}

//Funcao p/ converter a jogada, retornando true em uma jogada valida ou false em uma invalida
//Recebe a string da jogada e os ponteiros referentes a posicao linha e coluna da matriz
bool converte_jogada(char jogada[], int *lin, int *col)
{
  int cont = 0;
  bool flag = false;
  for(int i = 0; i < strlen(jogada); i++){
    if(jogada[i] > 48 && jogada[i] < 52){
      cont++;
    }
  }
  if(cont == 1){
    for(int i = 0; i < strlen(jogada); i++){
      if(jogada[i] > 48 && jogada[i] < 52){
        *col = jogada[i] - 49;
	flag = true;
	break;
      }else{
        flag = false;
      }
    }
  }else{
    flag = false;
  }
  cont = 0;
  for (int i = 0; i < strlen(jogada); i++){
    if(jogada[i] > 64 && jogada[i] < 68){
      cont++;
	}else if(jogada[i] > 96 && jogada[i] < 100){
	  cont++;
	}
  }
  if(flag == true && cont == 1){
    for(int i = 0; i < strlen(jogada); i++){
      if(jogada[i] > 64 && jogada[i] < 68) {
        *lin = jogada[i]- 65;
	flag = true;
        break;
      }else if(jogada[i] > 96 && jogada[i] < 100){
        *lin = jogada[i] - 97;
	flag = true;
	break;
      }else{
      	flag = false;
      }
    }
  }else{
    flag = false;
  }
  if(flag == true){
    return true;
  }else{
    return false;
  }
}

//Funcao que faz o teste a respeito da vitoria do jogo, retornando true caso haja ganhador
//Recebe a matriz do jogo, o nome de ambos os jogadores
//e a peca do jogador atual p/ teste vitoria
bool testeVitoria(char jogo[][3], char nome1[], char nome2[], char jogador)
{
  char nome[20];
  if(jogador == 'X'){
    strcpy(nome, nome1);
  }else{
    strcpy(nome, nome2);
  }
  for(int i = 0; i < 3; i++){
    if(jogo[i][0] == jogador && jogo[i][1] == jogador && jogo[i+1][2] == jogador){
      printf("\n%s Ganhou\n", nome);
      return true;
    }
    if(jogo[i][0] == jogador && jogo[i+1][1] == jogador && jogo[i+1][2] == jogador){
      printf("\n%s Ganhou\n", nome);
      return true;
    }
  }
  for(int i = 1; i < 3; i++){
    if(jogo[i][0] == jogador && jogo[i][1] == jogador && jogo[i-1][2] == jogador){
      printf("\n%s Ganhou\n", nome);
      return true;
    }
    if(jogo[i][0] == jogador  && jogo[i-1][1] == jogador && jogo[i-1][2] == jogador){
      printf("\n%s Ganhou\n", nome);
      return true;
    }
  }
  for(int j = 0; j < 3; j++){
    if(jogo[0][j] == jogador  && jogo[1][j] == jogador && jogo[2][j+1] == jogador){
      printf("\n%s Ganhou\n", nome);
      return true;
    }
    if(jogo[0][j] == jogador && jogo[1][j+1] == jogador && jogo[2][j+1] == jogador){
      printf("\n%s Ganhou\n", nome);
      return true;
    }
  }
  for(int j = 1; j < 3; j++){
    if(jogo[0][j] == jogador && jogo[1][j-1] == jogador && jogo[2][j-1] == jogador){
      printf("\n%s Ganhou\n", nome);
      return true;
    }
    if(jogo[0][j] == jogador && jogo[1][j] == jogador && jogo[2][j-1] == jogador){
      printf("\n%s Ganhou\n", nome);
      return true;
    }
  }
}
