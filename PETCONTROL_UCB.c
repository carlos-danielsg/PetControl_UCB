#include <stdio.h>
#define MAX_TUTORES 30
#define MAX_ANIMAIS 50
#define MAX_ATENDIMENTOS 100

// Prótotipos das funções
void menu_principal();
void cadastrar_tutor(Tutor tutores[], int *qtdTutores);

typedef struct {
    int idT;
    char nome[50];
    char telefone[12];
} Tutor;

typedef struct{
    int idA;
    char nome[50];
    char especie[50];
    int idT;
} Animal;

int main() {
    int opcao, qtd_tutor = 0, qtd_animal = 0;
    Tutor tutores[MAX_TUTORES];
    Animal animais[MAX_ANIMAIS];

    do {
        menu_principal();
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrar_tutor(tutores, qtd_tutor);
                break;
            case 2:
                // Cadastrar Animal
                break;
            case 3:
                // Listar Cadastros
                break;
            case 4:
                // Buscar Registros
                break;
            case 5:
                // Registrar Atendimentos
                break;
            case 6:
                // Alterar Cadastros
                break;
            case 7:
                // Relatórios
                break;
            case 8:
                printf("\nEncerrando o progama...\n");
                break;
            default:
                printf("\nOpcao Invalida, escolha novamente!\n");
                break;
        }
    } while(opcao != 8);
    
}

void menu_principal(void){
    // Vetor criado para armazenar os nomes das opções que o menu oferece!
    char opcoes_nomes[8][50] = {
        "Cadastrar Tutor", "Cadastrar Animal","Listar Cadastros", "Buscar Registros",
        "Registrar Atendimentos", "Alterar Cadastro", "Relatorios", "Sair"
    }; 
    printf("\n===================================\n");
    printf("%23s\n", "PETCONTROL");
    printf("===================================\n");
    // Usei um For para imprimir corretamente e diminuir o número de linhas necessárias para o Menu.
    for (int i = 0; i < 8; i++) {
        printf("%d - %s\n", i + 1, opcoes_nomes[i]);
    };
    printf("\nEscolha a sua opcao: ");
}

void cadastrar_tutor(Tutor tutores[], int *qtdTutores) {
    if (*qtdTutores >= MAX_TUTORES){
        printf("\nO Limite de tutores foi atingido.\n");
        return;
    }
    // Registra o número do ID/Cadastro do tutor no Vetor.
    tutores[*qtdTutores].idT = *qtdTutores + 1;

    //
    printf("\nInforme o nome do Tutor: ");
    
}

