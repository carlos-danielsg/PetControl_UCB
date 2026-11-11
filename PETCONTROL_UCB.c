#include <stdio.h>
#include <string.h>
#define MAX_TUTORES 30
#define MAX_ANIMAIS 50
#define MAX_ATENDIMENTOS 100

typedef struct {
    int idT;
    char nome[50];
    char telefone[20];
} Tutor_t;

typedef struct{
    int idA;
    char nome[50];
    char especie[50];
    int idT;
} Animal_t;

// Prótotipos das funções
void pausar();
void menu_principal();
void cadastrar_tutor(Tutor_t tutores[], int *qtdTutores);
void cadastrar_animal(Animal_t animais[], int *qtdAnimais, Tutor_t tutores[], int qtdTutores);
void listar_cadastros(Tutor_t tutores[], int qtdTutores, Animal_t animais[], int qtdAnimais);

int main() {
    int opcao, qtd_tutor = 0, qtd_animal = 0;
    Tutor_t tutores[MAX_TUTORES];
    Animal_t animais[MAX_ANIMAIS];

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
                cadastrar_animal(animais, &qtd_animal, tutores, qtd_tutor);
                break;
            case 3:
                listar_cadastros(tutores, qtd_tutor, animais, qtd_animal);
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

void cadastrar_tutor(Tutor_t tutores[], int *qtdTutores) {
    if (*qtdTutores >= MAX_TUTORES){
        printf("\nO Limite de tutores foi atingido.\n");
        return;
    }
    // Cria um ponteiro pro Tutor atual para simplificação do Código
    Tutor_t *tutor = &tutores[*qtdTutores];
    // Registra o número do ID/Cadastro do tutor no Vetor.
    tutor->idT = *qtdTutores + 1;

    // Pega o nome do Tutor e retira a quebra de linha!
    printf("\nInforme o nome do Tutor: ");
    fgets(tutor->nome, sizeof tutor->nome, stdin);
    tutor->nome[strcspn(tutor->nome, "\n")] = '\0';
    // Pega o telefone do tutor.
    printf("\nAgora, informe o numero de telefone do tutor: ");
    fgets(tutor->telefone, sizeof tutor->telefone, stdin);
    tutor->telefone[strcspn(tutor->telefone, "\n")] = '\0';
    // Imprime os dados para checagem!
    printf("\nTutor Cadastrado com sucesso!\n"
        "\nO nome cadastrado foi: %s\n"
        "O telefone cadastrado foi: %s\n"
        "O ID desse tutor e: %d\n", tutor->nome, tutor->telefone,
        tutor->idT);
    (*qtdTutores)++;
}
void cadastrar_animal(Animal_t animais[], int *qtdAnimais, Tutor_t tutores[], int qtdTutores){
    if (*qtdAnimais >= MAX_ANIMAIS){
        printf("\nO limite de animais foi atingido.\n");
        return;
    }
    // Validar se há tutores cadastrados!
    if (qtdTutores == 0){
        printf("\nCadastre um tutor antes de cadastrar um animal!\n");
        return;
    }

    int idTutor, encontrado = 0;
    printf("\nInforme o ID do Tutor: ");
    scanf("%d", &idTutor);
    while(getchar() != '\n');
    // Valida se o ID fornecido existe!
    for (int i = 0; i < qtdTutores; i++) {
        if(tutores[i].idT == idTutor){
            encontrado = 1;
            break;
        }
    }
    if (encontrado == 0){
        printf("\nTutor nao encontrado.\n");
        return;
    }
    // Cria um ponteiro pro animal atual para simplificação do Código
    Animal_t *animal = &animais[*qtdAnimais];
    // Cria o ID do animal.
    animal->idA = *qtdAnimais + 1;
    animal->idT = idTutor;
    // Coleta o nome do animal!
    printf("\nInforme o nome do animal: ");
    fgets(animal->nome, sizeof animal->nome, stdin);
    animal->nome[strcspn(animal->nome, "\n")] = '\0';
    // Coleta a especie do animal!
    printf("\nInforme agora a especie do animal: ");
    fgets(animal->especie, sizeof animal->especie, stdin);
    animal->especie[strcspn(animal->especie, "\n")] = '\0';
    // Imprime os dados para checagem!
    printf("\nAnimal cadastrado com sucesso!\n"
        "\nEste animal pertecene ao tutor %s de ID %d\n"
        "O nome do animal e: %s\n"
        "Sua especie e: %s\n"
        "O ID do animal e: %d\n", tutores[idTutor - 1].nome, idTutor, animal->nome,
        animal->especie, animal->idA
    );
    (*qtdAnimais)++;

}
// Função para listar os cadastros se houver! Ainda falta listar também os animais cadastrados por tutor.
void listar_cadastros(Tutor_t tutores[], int qtdTutores, Animal_t animais[], int qtdAnimais) {
    if (qtdTutores == 0) {
        printf("\nNao ha tutores cadastrados no sistema!\n");
        return;
    }
    printf("\nEsses sao os tutores e os animais cadastrados: \n");
    // Primeiro loop imprime o tutor e seu id
    for (int i = 0; i < qtdTutores; i++) {
        printf("%d - %s\n", tutores[i].idT, tutores[i].nome);
        // Segundo loop imprime o animal e seu ID de acordo com o tutor
        int temAnimal = 0;
        for (int j = 0; j < qtdAnimais; j++){
            if(tutores[i].idT == animais[j].idT){
                printf(" | %d - %s\n", animais[j].idA, animais[j].nome);
                temAnimal = 1;
            }
        }
        if (temAnimal == 0){
            printf(" | Sem animais cadastrados\n");
        }
    }
}
// Pausa após cada iteração!
void pausar(void) {
    printf("\nPressione Enter para continuar...");
    getchar();
}