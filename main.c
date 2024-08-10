#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <limits.h>

int i,j,x=0,y=0,rodada=0,fim=0;
char matriz[3][3];

void limpar_tela();
void desenho_do_jogo();
void fim_de_jogo();
void condicao_de_fim();
void controle(int,int);
void melhor_jogada();

int main(){
    setlocale(LC_ALL,"");

    for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			matriz[i][j]='.';
		}
	}

    while(fim!=1){
        rodada++;
        desenho_do_jogo();
        condicao_de_fim();;
        x=0;
        y=0;
        controle(0,0);

        if(rodada%2!=0){
            int tecla='q';
            while(tecla!=13){
                tecla=getch();
                switch(tecla){
                    case 72: // Seta para cima
                        if(y>0){
                            y--;
                            controle(x*8,y*3);
                        }
                        break;
                    case 80: // Seta para baixo
                        if(y<4){
                            y++;
                            controle(x*8,y*3);
                        }
                        break;
                    case 75: // Seta para esquerda
                        if(x>0){
                            x--;
                            controle(x*8,y*3);
                        }
                        break;
                    case 77: // Seta para direita
                        if(x<4){
                            x++;
                            controle(x*8,y*3);
                        }
                        break;
                }
            }
            matriz[y][x]='X';
            fflush(stdin);
            Sleep(100);
        }
        if(rodada%2==0)
            melhor_jogada();


    }
    fim_de_jogo();
    return 0;
}

void limpar_tela(){
    system("cls");
}

void desenho_do_jogo(){
    limpar_tela();
    for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			printf("%c\t",matriz[i][j]);
		}
        printf("\n\n\n");
	}
}

void fim_de_jogo(){
    limpar_tela();
    printf("\n\tO jogo acabou!\n\tNúmero de rodadas: %d",rodada-1);
}

void condicao_de_fim(){
    for(y=0;y<3;y++){
        if((matriz[0][y]=='X')&(matriz[1][y]=='X')&(matriz[2][y]=='X')){
            printf("\n\n\n\tVocê venceu!");
            Sleep(2000);
            fim=1;
       }
        if((matriz[0][y]=='O')&(matriz[1][y]=='O')&(matriz[2][y]=='O')){
            printf("\n\n\n\tVocê Perdeu!");
            Sleep(2000);
            fim=1;
       }
    }

    for(x=0;x<3;x++){
        if((matriz[x][0]=='X')&(matriz[x][1]=='X')&(matriz[x][2]=='X')){
            printf("\n\n\n\tVocê venceu!");
            Sleep(2000);
            fim=1;
       }
        if((matriz[x][0]=='O')&(matriz[x][1]=='O')&(matriz[x][2]=='O')){
            printf("\n\n\n\tVocê Perdeu!");
            Sleep(2000);
            fim=1;
       }
    }

    if((matriz[0][0]=='X')&(matriz[1][1]=='X')&(matriz[2][2]=='X')){
        printf("\n\n\n\tVocê venceu!");
        Sleep(2000);
        fim=1;
    }
    if((matriz[0][0]=='O')&(matriz[1][1]=='O')&(matriz[2][2]=='O')){
        printf("\n\n\n\tVocê Perdeu!");
        Sleep(2000);
        fim=1;
    }

    if((matriz[0][2]=='X')&(matriz[1][1]=='X')&(matriz[2][0]=='X')){
        printf("\n\n\n\tVocê venceu!");
        Sleep(2000);
        fim=1;
    }
    if((matriz[0][2]=='O')&(matriz[1][1]=='O')&(matriz[2][0]=='O')){
        printf("\n\n\n\tVocê Perdeu!");
        Sleep(2000);
        fim=1;
    }

    if(rodada>=10){
        printf("Empate!");
        Sleep(2000);
        fim=1;
    }
}

void controle(int x,int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

// Função minimax com poda alfa-beta
int minimax(int alcance, int maximizando, int alpha, int beta) {
    if (maximizando) {
        int melhor = INT_MIN;
        // Percorre todas as células vazias
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (matriz[i][j] == '.') {
                    matriz[i][j] = 'O'; // Simula uma jogada do jogador 2
                    int val = minimax(alcance + 1, 0, alpha, beta); // Chamada recursiva para o próximo estado
                    melhor = (val > melhor) ? val : melhor; // Atualiza o melhor valor para o jogador O
                    alpha = (alpha > melhor) ? alpha : melhor; // Atualiza o valor de alpha
                    matriz[i][j] = '.'; // Desfaz a jogada para explorar outras possibilidades
                    if (beta <= alpha)
                        break; // Poda alfa-beta
                }
            }
        }
        return melhor; // Retorna o melhor valor encontrado
    } else {
        int melhor = INT_MAX;
        // Percorre todas as células vazias
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (matriz[i][j] == '.') {
                    matriz[i][j] = 'X'; // Simula uma jogada do jogador 1
                    int val = minimax(alcance + 1, 1, alpha, beta); // Chamada recursiva para o próximo estado
                    melhor = (val < melhor) ? val : melhor; // Atualiza o melhor valor para o jogador O
                    beta = (beta < melhor) ? beta : melhor; // Atualiza o valor de beta
                    matriz[i][j] = '.'; // Desfaz a jogada para explorar outras possibilidades
                    if (beta <= alpha)
                        break; // Poda alfa-beta
                }
            }
        }
        return melhor; // Retorna o melhor valor encontrado
    }
}

// Função para encontrar a melhor jogada
void melhor_jogada(){
    int melhor_val = INT_MIN;
    int melhor_lin = -1;
    int melhor_col = -1;

    // Percorre todas as células vazias
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matriz[i][j] == '.') {
                matriz[i][j] = 'O'; // Simula uma jogada do jogador 2
                int move_val = minimax(0, 0, INT_MIN, INT_MAX); // Calcula o valor da jogada
                matriz[i][j] = '.'; // Desfaz a jogada
                if (move_val > melhor_val) {
                    melhor_lin = i; // Atualiza a melhor linha
                    melhor_col = j; // Atualiza a melhor coluna
                    melhor_val = move_val; // Atualiza o melhor valor
                }
            }
        }
    }
    matriz[melhor_lin][melhor_col]='O';

    printf("A melhor jogada é: Linha %d, Coluna %d\n", melhor_lin, melhor_col);
    Sleep(1000);
}
