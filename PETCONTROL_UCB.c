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

typedef struct {
    int idAt;
    int idA;
    int idS;
    int quantidade;
    float valor_total;
} Atendimento_t;

// Prototipos das funcoes
void pausar(void);
void menu_principal(void);
int ler_id(void);
int buscar_tutor(Tutor_t tutores[], int qtdTutores, int id);
int buscar_animal(Animal_t animais[], int qtdAnimais, int id);
void cadastrar_tutor(Tutor_t tutores[], int *qtdTutores);
void cadastrar_animal(Animal_t animais[], int *qtdAnimais, Tutor_t tutores[], int qtdTutores);
void listar_cadastros(Tutor_t tutores[], int qtdTutores, Animal_t animais[], int qtdAnimais);
void buscar_registros(Tutor_t tutores[], int qtdTutores, Animal_t animais[], int qtdAnimais);
void listar_servicos(char nomes[][30], float precos[], int usa_qtd[], int qtd_servicos);
void registrar_atendimentos (Atendimento_t atendimentos[], int *qtdAtendimentos, Animal_t animais[],
int qtdAnimais, char nomes[][30], float precos[], int usaQtd[], int qtdServicos);
void alterar_cadastro(Animal_t animais[], Tutor_t tutores[], int qtdAnimais, int qtdTutores);
void alterar_tutor(Tutor_t *tutor);
void alterar_animal(Animal_t *animal, Tutor_t tutores[], int qtdTutores);

int main() {
    int opcao, qtd_tutor = 0, qtd_animal = 0, qtd_servicos = 4, qtd_atendimento = 0;
    Tutor_t tutores[MAX_TUTORES];
    Animal_t animais[MAX_ANIMAIS];
    Atendimento_t atendimentos[MAX_ATENDIMENTOS];
    char nomes_servicos[4][30] = {"Banho","Tosa", "Consulta", "Vacinacao"};
    float preco_servicos[4] = {50.00f, 70.00f, 120.00f, 80.00f};
    int usa_quantidade[4] = {0, 0, 0, 1}; // Se o valor for 1, pergunta a quantidade;

    do {
        menu_principal();
        opcao = ler_id();

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
                buscar_registros(tutores, qtd_tutor, animais, qtd_animal);
                break;
            case 5:
                registrar_atendimentos(atendimentos, &qtd_atendimento, animais, qtd_animal,
                           nomes_servicos, preco_servicos, usa_quantidade, qtd_servicos);
                break;
            case 6:
                alterar_cadastro(animais, tutores, qtd_animal, qtd_tutor);
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

    return 0;
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

// Le um inteiro e limpa o resto da linha. Se nao for numero, devolve -1.
int ler_id(void){
    int numero;
    if (scanf("%d", &numero) != 1){
        numero = -1;
    }
    while (getchar() != '\n');
    return numero;
}

// Procura um tutor pelo ID. Retorna a posição dele no vetor, ou -1 se nao existir.
int buscar_tutor(Tutor_t tutores[], int qtdTutores, int id){
    for (int i = 0; i < qtdTutores; i++){
        if (tutores[i].idT == id){
            return i;
        }
    }
    return -1;
}

// Procura um animal pelo ID. Retorna a posição dele no vetor, ou -1 se nao existir.
int buscar_animal(Animal_t animais[], int qtdAnimais, int id){
    for (int i = 0; i < qtdAnimais; i++){
        if (animais[i].idA == id){
            return i;
        }
    }
    return -1;
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

    int idTutor, indice;
    printf("\nInforme o ID do Tutor: ");
    idTutor = ler_id();

    // Valida se o ID fornecido existe e guarda sua posição.
    indice = buscar_tutor(tutores, qtdTutores, idTutor);
    if (indice == -1){
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
        "\nEste animal pertence ao tutor %s de ID %d\n"
        "O nome do animal e: %s\n"
        "Sua especie e: %s\n"
        "O ID do animal e: %d\n", tutores[indice].nome, idTutor, animal->nome,
        animal->especie, animal->idA
    );
    (*qtdAnimais)++;

}
// Função para listar os cadastros se houver!
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

void buscar_registros(Tutor_t tutores[], int qtdTutores, Animal_t animais[], int qtdAnimais){
    int escolha;
    // Checa se ha tutores!
    if (qtdTutores == 0){
        printf("\nNao ha nenhum tutor cadastrado no sistema!\n");
        return;
    }
    do {
        printf("\nVoce deseja: \n"
            "1 - Procurar pelo ID de um tutor.\n"
            "2 - Procurar pelo ID de um animal.\n"
            "3 - Sair. \n"
        );
        // Se o usuario digitar algo que nao e numero, escolha vira -1 (cai no default).
        escolha = ler_id();
 
        switch(escolha){
            // Checa os registros de um tutor em especifico.
            case 1: {
                int idTutor, indice_tutor;
                printf("\nQual o ID do Tutor que voce quer ver os registros?\n");
                idTutor = ler_id();
                // Procura pelo ID informado dentro da Struct/Vetor
                indice_tutor = buscar_tutor(tutores, qtdTutores, idTutor);
                if (indice_tutor == -1){
                    printf("\nTutor nao encontrado.\n");
                    break;
                }
                printf("Tutor encontrado: %s\n"
                    "Telefone do Tutor: %s\n", tutores[indice_tutor].nome, tutores[indice_tutor].telefone
                );
                // Procura e compara o ID do tutor com o dos animais para ver se ele tem animais.
                int tem_animal = 0;
                for (int j = 0; j < qtdAnimais; j++){
                    if (animais[j].idT == idTutor){
                        if (tem_animal == 0){
                            printf("Animais encontrados: \n");
                        }
                        printf(" | %d - %s (%s)\n", animais[j].idA, animais[j].nome, animais[j].especie);
                        tem_animal = 1;
                    }
                }
                if (tem_animal == 0){
                    printf(" | Sem animais cadastrados\n");
                }
                break;
            }
            // Checa os registros de um animal em especifico.
            case 2: {
                int idAnimal, indice_animal;
                if (qtdAnimais == 0) {
                    printf("\nNao ha animais cadastrados.\n");
                    break;
                }
                printf("\nQual o ID do Animal que voce quer ver os registros?\n");
                idAnimal = ler_id();

                indice_animal = buscar_animal(animais, qtdAnimais, idAnimal);
                if (indice_animal == -1){
                    printf("\nAnimal nao encontrado.\n");
                    break;
                }
                printf("Animal encontrado: %s\n"
                    "Especie do Animal: %s\n", animais[indice_animal].nome, animais[indice_animal].especie
                );
                // Procura o tutor pelo idT guardado no animal.
                int indice_tutor = buscar_tutor(tutores, qtdTutores, animais[indice_animal].idT);
                if (indice_tutor != -1){
                    printf("Tutor: %s (ID: %d)\n", tutores[indice_tutor].nome, tutores[indice_tutor].idT);
                }
                break;
            }
            case 3:
                printf("\nVoltando ao menu inicial...\n");
                break;
            default:
                printf("\nOpcao Invalida, escolha novamente!\n");
                break;
        }
        if (escolha != 3){
            pausar();
        }
    } while(escolha != 3);
}

void listar_servicos(char nomes[][30], float precos[], int usa_qtd[], int qtd_servicos){
    printf("\nEsses sao os servicos disponiveis: \n");
    for (int i = 0; i < qtd_servicos; i++){
        printf("%d - %-22s R$ %7.2f", i + 1, nomes[i], precos[i]);
        if (usa_qtd[i] != 0){
            printf(" (por unidade)");
        }
        printf("\n");
    }
}

void registrar_atendimentos (Atendimento_t atendimentos[], int *qtdAtendimentos, Animal_t animais[],
int qtdAnimais, char nomes[][30], float precos[], int usaQtd[], int qtdServicos){
    // Checa se ultrapassou o limite
    if(*qtdAtendimentos >= MAX_ATENDIMENTOS){
        printf("\nLimite de atendimentos atingido\n");
        return;
    }
    // Checa se há animais cadastrados
    if (qtdAnimais == 0){
        printf("\nNao ha animais cadastrados.\n");
        return;
    }
    // indice_animal guarda a POSICAO do animal no vetor (-1 = nao encontrado).
    int id_animal = 0, indice_animal;
    printf("\nInforme o ID do animal: \n");
    id_animal = ler_id();
    // checa se o id existe no banco de dados.
    indice_animal = buscar_animal(animais, qtdAnimais, id_animal);
    if (indice_animal == -1){
        printf("\nAnimal nao encontrado.\n");
        return;
    }

    listar_servicos(nomes, precos, usaQtd, qtdServicos);
    int id_servico;
    printf("\nEscolha o servico: ");
    id_servico = ler_id();

    if (id_servico < 1 || id_servico > qtdServicos){
        printf("\nServico Invalido.\n");
        return;
    }
    int pos_servico = id_servico - 1;
    
    int quantidade = 1;
    if(usaQtd[pos_servico] == 1){
        printf("Escolha a quantidade: ");
        quantidade = ler_id();
        if (quantidade < 1) {
            printf("\nQuantidade Invalida\n");
            return;
        }
    }
    // Salva o atendimento na struct.
    Atendimento_t *atende = &atendimentos[*qtdAtendimentos];
    atende->idAt = *qtdAtendimentos + 1;
    atende->idA = id_animal;
    atende->idS = id_servico;
    atende->quantidade = quantidade;
    atende->valor_total = precos[pos_servico] * quantidade;

    printf("\nAtendimento registrado com sucesso!\n"
        "\nAtendimento: %d\n"
        "Animal: %s (ID: %d)\n"
        "Servico: %s\n"
        "Quantidade: %d\n"
        "Valor total: R$ %.2f\n",
        atende->idAt, animais[indice_animal].nome, id_animal,
        nomes[pos_servico], quantidade, atende->valor_total);
    (*qtdAtendimentos)++;
}
void alterar_cadastro(Animal_t animais[], Tutor_t tutores[], int qtdAnimais, int qtdTutores){
    int escolha;
    // Checa se ha tutores!
    if (qtdTutores == 0){
        printf("\nNao ha nenhum tutor cadastrado no sistema!\n");
        return;
    }
    do{
        printf("\nVoce deseja: \n"
            "1 - Alterar o cadastro de um Tutor.\n"
            "2 - Alterar o cadastro de um Animal\n"
            "3 - Sair. \n"
        );
        escolha = ler_id();
        switch(escolha){
            case 1: {
                int id_tutor, indice_tutor;
                printf("\nQual o ID do tutor que voce deseja alterar os dados?\n");
                id_tutor = ler_id();
                indice_tutor = buscar_tutor(tutores, qtdTutores, id_tutor);
                if (indice_tutor == -1){
                    printf("\nTutor nao encontrado.\n");
                    break;
                }
                alterar_tutor(&tutores[indice_tutor]);
                break;
            }
            case 2: {
                int id_animal, indice_animal;
                if(qtdAnimais == 0){
                    printf("\nNao ha nenhum animal cadastrado no sistema\n");
                    break;
                }
                printf("\nQual o ID do animal que voce deseja alterar os dados?\n");
                id_animal = ler_id();
                indice_animal = buscar_animal(animais, qtdAnimais, id_animal);
                if(indice_animal == -1){
                    printf("\nAnimal nao encontrado.\n");
                    break;
                }
                alterar_animal(&animais[indice_animal], tutores, qtdTutores);
                break;
            }
            case 3: {
                printf("\nVoltando ao menu inicial...\n");
                break;
            }
            default:
                printf("\nOpcao Invalida, escolha novamente!\n");
                break;
        }
            if (escolha != 3){
                pausar();
            }
    } while (escolha != 3);
}

void alterar_tutor(Tutor_t *tutor){
    int escolha_tutor;
    do{
        printf("\nQual dado voce deseja alterar:\n"
            "1 - Nome do Tutor\n"
            "2 - Telefone do Tutor\n"
            "3 - Sair\n"
        );
        escolha_tutor = ler_id();

        switch(escolha_tutor) {
        case 1: {
            char novo_nome[50];
            printf("\nO nome atual e: %s\n", tutor->nome);
            printf("\nQual voce quer que seja o novo nome? ");
            fgets(novo_nome, sizeof(novo_nome), stdin);
            novo_nome[strcspn(novo_nome, "\n")] = '\0';
            if (novo_nome[0] == '\0'){
                printf("\nNome vazio. Nada foi alterado.\n");
            } else {
                strcpy(tutor->nome, novo_nome);
                printf("\nNome alterado com sucesso!\n");
            }
            break;
        }
        case 2: {
            char novo_telefone[20];
            printf("\nO telefone atual e: %s\n", tutor->telefone);
            printf("\nQual voce quer que seja o novo telefone? ");
            fgets(novo_telefone, sizeof(novo_telefone), stdin);
            novo_telefone[strcspn(novo_telefone, "\n")] = '\0';
            if (novo_telefone[0] == '\0'){
                printf("\nTelefone Vazio. Nada foi alterado.\n");
            } else {
                strcpy(tutor->telefone, novo_telefone);
                printf("\nTelefone alterado com sucesso!\n");
            }
            break;
        }
        case 3: {
            printf("\nVoltando...\n");
            break;
        }
        default:
            printf("\nEscolha Invalida.\n");
            break;
        }
    } while (escolha_tutor != 3);
}

void alterar_animal(Animal_t *animal, Tutor_t tutores[], int qtdTutores){
    int escolha_animal;
    do{
        printf("\nQual dado voce deseja alterar:\n"
            "1 - Nome do Animal\n"
            "2 - Especie do Animal\n"
            "3 - Tutor do Animal\n"
            "4 - Sair\n"
        );
        escolha_animal = ler_id();

        switch(escolha_animal){
            case 1:{
                char novo_nome[50];
                printf("\nO nome atual e: %s\n", animal->nome);
                printf("\nQual voce quer que seja o novo nome? ");
                fgets(novo_nome, sizeof(novo_nome), stdin);
                novo_nome[strcspn(novo_nome, "\n")] = '\0';
                if (novo_nome[0] == '\0'){
                printf("\nNome vazio. Nada foi alterado.\n");
                } else {
                    strcpy(animal->nome, novo_nome);
                    printf("\nNome alterado com sucesso!\n");
                }
                break;
            }
            case 2:{
                char nova_especie[50];
                printf("\nA especie cadastrada e: %s\n", animal->especie);
                printf("\nQual voce quer que seja a nova especie cadastrada? ");
                fgets(nova_especie, sizeof(nova_especie), stdin);
                nova_especie[strcspn(nova_especie, "\n")] = '\0';
                if (nova_especie[0] == '\0'){
                    printf("\nEspecie vazia. Nada foi alterado.\n");
                } else{
                    strcpy(animal->especie, nova_especie);
                    printf("\nEspecie alterada com sucesso!\n");
                }
                break;
            }
            case 3:{
                int novo_tutor_ID, novo_tutor;
                // Mostra o tutor atual (procurado pelo idT guardado no animal).
                int tutor_atual = buscar_tutor(tutores, qtdTutores, animal->idT);
                if (tutor_atual != -1){
                    printf("\nO tutor atual e: %s (ID: %d)\n", tutores[tutor_atual].nome, tutores[tutor_atual].idT);
                }
                printf("\nInforme o ID do novo tutor: ");
                novo_tutor_ID = ler_id();
                novo_tutor = buscar_tutor(tutores, qtdTutores, novo_tutor_ID);
                if(novo_tutor == -1){
                    printf("\nTutor nao encontrado. Nada foi alterado.\n");
                } else{
                    animal->idT = novo_tutor_ID;
                    printf("\nTutor responsavel alterado com sucesso\n"
                        "O novo tutor e: %s\n", tutores[novo_tutor].nome
                    );
                }
                break;
            }
            case 4:{
                printf("\nVoltando...\n");
                break;
            }
            default:{
                printf("Escolha Invalida.");
                break;
            }
        }
    } while (escolha_animal != 4);
}
// Pausa após cada iteração!
void pausar(void) {
    printf("\nPressione Enter para continuar...\n");
    getchar();
}