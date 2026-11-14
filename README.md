# PETCONTROL

Sistema de controle de tutores e animais, feito em **C** e executado no terminal. Projeto acadêmico do curso de Análise e Desenvolvimento de Sistemas (ADS), feito em grupo para a matéria **Práticas Profissionais 2**.

## Funcionalidades

| Opção | Funcionalidade | Status |
|---|---|---|
| 1 | Cadastrar tutor (nome e telefone) | Pronto |
| 2 | Cadastrar animal (nome e espécie, vinculado a um tutor) | Pronto |
| 3 | Listar cadastros (tutores com seus animais) | Pronto |
| 4 | Buscar registros por ID de tutor ou de animal | Pronto |
| 5 | Registrar atendimentos | Pronto |
| 6 | Alterar cadastros | Pronto |
| 7 | Relatórios | A fazer |
| 8 | Sair | Pronto |

### Detalhes

- **Cadastro de tutor:** o ID é gerado automaticamente e exibido ao final do cadastro.
- **Cadastro de animal:** só é possível se já existir ao menos um tutor. O ID do tutor informado é validado antes de salvar.
- **Listagem:** mostra cada tutor com seus animais. Tutores sem animais aparecem como "Sem animais cadastrados".
- **Busca por tutor:** mostra nome, telefone e todos os animais dele.
- **Busca por animal:** mostra nome, espécie e o tutor responsável.
- **Registrar atendimentos:** só é possível se existir ao menos um animal cadastrado. O ID do animal é validado, o serviço é escolhido no catálogo, a quantidade só é perguntada quando se aplica (vacinação) e o valor total é calculado automaticamente (preço × quantidade).
- **Alterar cadastros:** permite alterar o nome e o telefone do tutor, o nome e a espécie do animal e o tutor responsável pelo animal. Campos deixados em branco não alteram o cadastro, e o novo tutor do animal precisa existir.
- **Entradas inválidas:** letras ou IDs inexistentes em qualquer menu são tratados com mensagem de erro, sem travar o programa.

### Catálogo de serviços

| Nº | Serviço | Preço | Quantidade |
|---|---|---|---|
| 1 | Banho | R$ 50,00 | sempre 1 |
| 2 | Tosa | R$ 70,00 | sempre 1 |
| 3 | Consulta | R$ 120,00 | sempre 1 |
| 4 | Vacinação | R$ 80,00 | por unidade (pergunta a quantidade) |

Os serviços ficam em três vetores paralelos no `main` (`nomes_servicos`, `preco_servicos` e `usa_quantidade`). A mesma posição nos três vetores descreve o mesmo serviço.

## Como compilar e executar

É necessário ter um compilador C instalado, como o `gcc`.

```bash
gcc -Wall -o petcontrol PETCONTROL_UCB.c
./petcontrol
```

No Windows (MinGW), execute `petcontrol.exe`.

## Exemplo de uso

```
===================================
             PETCONTROL
===================================
1 - Cadastrar Tutor
2 - Cadastrar Animal
3 - Listar Cadastros
4 - Buscar Registros
5 - Registrar Atendimentos
6 - Alterar Cadastro
7 - Relatorios
8 - Sair

Escolha a sua opcao:
```

## Estrutura de dados

O projeto usa três `struct` armazenadas em vetores:

```c
typedef struct {
    int idT;
    char nome[50];
    char telefone[20];
} Tutor_t;

typedef struct {
    int idA;
    char nome[50];
    char especie[50];
    int idT;          // ID do tutor responsável
} Animal_t;

typedef struct {
    int idAt;
    int idA;          // ID do animal atendido
    int idS;          // número do serviço no catálogo
    int quantidade;
    float valor_total; // preço do serviço × quantidade
} Atendimento_t;
```

O tutor de um atendimento não é guardado na struct: ele é encontrado pelo `idT` do animal.

### Limites

| Item | Máximo |
|---|---|
| Tutores | 30 |
| Animais | 50 |
| Atendimentos | 100 |

## Organização do código

| Função | O que faz |
|---|---|
| `main` | Controla o menu principal e chama as demais funções |
| `menu_principal` | Exibe o menu |
| `ler_int` | Lê um número do teclado e limpa o resto da linha; devolve -1 se a entrada não for um número |
| `buscar_tutor` | Procura um tutor pelo ID e devolve a posição dele no vetor (ou -1) |
| `buscar_animal` | Procura um animal pelo ID e devolve a posição dele no vetor (ou -1) |
| `cadastrar_tutor` | Cadastra um novo tutor |
| `cadastrar_animal` | Cadastra um animal vinculado a um tutor existente |
| `listar_cadastros` | Lista tutores e seus animais |
| `buscar_registros` | Submenu de busca por ID de tutor ou de animal |
| `listar_servicos` | Exibe o catálogo de serviços com os preços |
| `registrar_atendimentos` | Registra um atendimento vinculado a um animal existente |
| `alterar_cadastro` | Submenu para escolher se vai alterar um tutor ou um animal |
| `alterar_tutor` | Altera o nome e o telefone do tutor |
| `alterar_animal` | Altera o nome, a espécie e o tutor do animal |
| `pausar` | Aguarda o Enter antes de voltar ao menu |
