# PETCONTROL

Sistema de controle de tutores e animais, feito em **C** e executado no terminal. Projeto acadêmico do curso de Análise e Desenvolvimento de Sistemas (ADS) feito em grupo para a matéria **Praticas Profissionais 2**.

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
- **Registrar atendimentos** só é possivel se existir ao menos um tutor e um animal, lista serviços e salva os atendimentos.
- **Alterar cadastros** possibilita a alteração de nomes, telefone do tutor, espécie do animal e tutor cadastrado do animal.

## Como compilar e executar

É necessário ter um compilador C instalado, como o `gcc`.

```bash
gcc -Wall -o petcontrol petcontrol.c
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
    int idA;
    int idS;
    int quantidade;
    float valor_total;
} Atendimento_t;
```

### Limites

| Item | Máximo |
|---|---|
| Tutores | 30 |
| Animais | 50 |
| Atendimentos | 100 (reservado para a opção 5) |

## Organização do código

| Função | O que faz |
|---|---|
| `main` | Controla o menu principal e chama as demais funções |
| `menu_principal` | Exibe o menu |
| `cadastrar_tutor` | Cadastra um novo tutor |
| `cadastrar_animal` | Cadastra um animal vinculado a um tutor existente |
| `listar_cadastros` | Lista tutores e seus animais |
| `buscar_registros` | Submenu de busca por ID de tutor ou de animal |
| `listar_servicos` | Exibe os serviços pré definidos |
| `registrar_atendimentos` | Cadastra um atendimento vinculado a um animal existente|
| `alterar_cadastros` | Altera os dados dos tutores e dos animais|
| `alterar_tutor` | Possibilita alteração do nome e telefone do tutor|
| `alterar_animal`| Possibilita alteração do nome, especie e do tutor do animal |
| `pausar` | Aguarda o Enter antes de voltar ao menu |