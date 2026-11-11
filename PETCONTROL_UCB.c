#include <stdio.h>
#include <string.h>
#define MAX_TUTORES 30
#define MAX_ANIMAIS 50
#define MAX_ATENDIMENTOS 100

typedef struct {
    int idT;
    char nome[50];
    char telefone[20];
} Tutor;

typedef struct{
    int idA;
    char nome[50];
    char especie[50];
    int idT;
} Animal;

// Prótotipos das funções
void pausar();
void menu_principal();
void cadastrar_tutor(Tutor tutores[], int *qtdTutores);
void listar_cadastros(Tutor tutores[], int qtdTutores);

int main() {
    int opcao, qtd_tutor = 0, qtd_animal = 0;
    Tutor tutores[MAX_TUTORES];
    Animal animais[MAX_ANIMAIS];

    do {
        menu_principal();
        scanf("%d", &opcao);
        // Consome o Enter(\n) que fica no buffer!
        while(getchar() != '\n');

        switch(opcao) {
            case 1:
                cadastrar_tutor(tutores, &qtd_tutor);
                break;
            case 2:
                // Cadastrar Animal
                break;
            case 3:
                listar_cadastros(tutores, qtd_tutor);
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
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpcao Invalida, escolha novamente!\n");
                break;
        }
        if(opcao != 8){
            pausar();
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

    // Pega o nome do Tutor e retira a quebra de linha!
    printf("\nInforme o nome do Tutor: ");
    fgets(tutores[*qtdTutores].nome, sizeof tutores[*qtdTutores].nome, stdin);
    tutores[*qtdTutores].nome[strcspn(tutores[*qtdTutores].nome, "\n")] = '\0';
    // Pega o telefone do tutor.
    printf("\nAgora, informe o numero de telefone do tutor: ");
    fgets(tutores[*qtdTutores].telefone, sizeof tutores[*qtdTutores].telefone, stdin);
    tutores[*qtdTutores].telefone[strcspn(tutores[*qtdTutores].telefone, "\n")] = '\0';
    // Imprime os dados para checagem!
    printf("\nTutor Cadastrado com sucesso!\n"
        "\nO nome cadastrado foi: %s\n"
        "O telefone cadastrado foi: %s\n"
        "O ID desse tutor e: %d\n", tutores[*qtdTutores].nome, tutores[*qtdTutores].telefone,
        tutores[*qtdTutores].idT);
    (*qtdTutores)++;
}
// Função para listar os cadastros se houver! Ainda falta listar também os animais cadastrados por tutor.
void listar_cadastros(Tutor tutores[], int qtdTutores) {
    if (qtdTutores == 0) {
        printf("\nNao ha tutores cadastrados no sistema!\n");
        return;
    }
    printf("\nEsses sao os tutores cadastrados: \n");
    for (int i = 0; i < qtdTutores; i++) {
        printf("%d - %s\n", tutores[i].idT, tutores[i].nome);
    }
}
// Pausa após cada iteração!
void pausar(void) {
    printf("\nPressione Enter para continuar...");
    getchar();
}