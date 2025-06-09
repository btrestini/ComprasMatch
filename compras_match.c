//CÓDIGO COMENTADO

//Incluindo as bibliotecas necessárias

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 512


//definindo a estrutura para os fornecedores
typedef struct {
    int id;
    char nome[100];
    char cidade[50];
    char uf[3];
    char cnpj[20];
    char ramo[50];
    char telefone[20];
    char email[100];
    char linhaFornecimento[100];
} Fornecedor;

// Definindo a estrutura para as compras
typedef struct {
    int id;
    char linhaFornecimento[100];
    char marca[50];
    char modelo[50];
    int quantidade;
    int status; // 1 - aberta, 2 - fechada
    char demandante[100];
} Compra;

// Declarando os ponteiros para os arrays dinâmicos de fornecedores e compras
Fornecedor *fornecedores = NULL;
Compra *compras = NULL;
int totalFornecedores = 0, totalCompras = 0;
int idFornecedor = 0, idCompra = 0;

// Função para exibir o cabeçalho do sistema
// e o nome do sistema
void exibirCabecalho() {
    printf("\033[44;1m\n                                                            \n");
    printf("      COMPRAS MATCH - GESTAO DE COMPRAS E FORNECEDORES      \n");
    printf("                                                            \033[0m\n\n");
}

// Função para formatar o prompt de mensagens
void formatarPrompt(char a[120]) {
    printf("\n\033[44;1m  %s  \033[0m\n", a);
}

// Função para carregar os fornecedores do arquivo
// e inicializar o array dinâmico
void carregarFornecedor() {
    FILE *f = fopen("fornecedores.txt", "r");
    if (!f) return;
    char linha[MAX];
    while (fgets(linha, sizeof(linha), f)) {
        fornecedores = realloc(fornecedores, sizeof(Fornecedor) * (totalFornecedores + 1));
        sscanf(linha, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
               &fornecedores[totalFornecedores].id,
               fornecedores[totalFornecedores].nome,
               fornecedores[totalFornecedores].cidade,
               fornecedores[totalFornecedores].uf,
               fornecedores[totalFornecedores].cnpj,
               fornecedores[totalFornecedores].ramo,
               fornecedores[totalFornecedores].telefone,
               fornecedores[totalFornecedores].email,
               fornecedores[totalFornecedores].linhaFornecimento);


        // Atualiza o ID do próximo fornecedor
        if (fornecedores[totalFornecedores].id >= idFornecedor) {
            idFornecedor = fornecedores[totalFornecedores].id + 1;
        }
      totalFornecedores++;

    }
    fclose(f);
}

// Função para salvar os fornecedores no arquivo
void salvarFornecedor() {
    FILE *f = fopen("fornecedores.txt", "w");
    for (int i = 0; i < totalFornecedores; i++) {
        fprintf(f, "%d|%s|%s|%s|%s|%s|%s|%s|%s\n",
                fornecedores[i].id, fornecedores[i].nome,
                fornecedores[i].cidade, fornecedores[i].uf,
                fornecedores[i].cnpj, fornecedores[i].ramo,
                fornecedores[i].telefone, fornecedores[i].email,
                fornecedores[i].linhaFornecimento);
    }
    fclose(f);
}


// Função para carregar as compras do arquivo
// e inicializar o array dinâmico
void carregarCompra() {
    FILE *f = fopen("compras.txt", "r");
    if (!f) return;
    char linha[MAX];
    while (fgets(linha, sizeof(linha), f)) {
        compras = realloc(compras, sizeof(Compra) * (totalCompras + 1));
        sscanf(linha, "%d|%[^|]|%[^|]|%[^|]|%d|%d|%[^\n]",
               &compras[totalCompras].id,
               compras[totalCompras].linhaFornecimento,
               compras[totalCompras].marca,
               compras[totalCompras].modelo,
               &compras[totalCompras].quantidade,
               &compras[totalCompras].status,
               compras[totalCompras].demandante);

        // Atualiza o ID da próxima compra
        if (compras[totalCompras].id >= idCompra) {
            idCompra = compras[totalCompras].id + 1;
        }
        totalCompras++;
    }
    fclose(f);
}
// Função para salvar as compras no arquivo
void salvarCompra() {
    FILE *f = fopen("compras.txt", "w");
    for (int i = 0; i < totalCompras; i++) {
        fprintf(f, "%d|%s|%s|%s|%d|%d|%s\n",
                compras[i].id, compras[i].linhaFornecimento,
                compras[i].marca,
                compras[i].modelo, compras[i].quantidade,
                compras[i].status, compras[i].demandante);
    }
    fclose(f);
}

// Função para cadastrar um novo fornecedor
void cadastrarFornecedor() {

    printf("      \033[4mCADASTRAR FORNECEDOR:\033[0m\n\n");
    Fornecedor f;

    f.id = ++idFornecedor;
    printf("  NOME: "); scanf(" %[^\n]", f.nome);
    printf("  CIDADE: "); scanf(" %[^\n]", f.cidade);
    printf("  UF: "); scanf(" %[^\n]", f.uf);
    printf("  CNPJ: "); scanf(" %[^\n]", f.cnpj);
    printf("  RAMO DE ATIVIDADE: "); scanf(" %[^\n]", f.ramo);
    printf("  TELEFONE: "); scanf(" %[^\n]", f.telefone);
    printf("  EMAIL: "); scanf(" %[^\n]", f.email);
    printf("  LINHA DE FORNECIMENTO: "); scanf(" %[^\n]", f.linhaFornecimento);

    fornecedores = realloc(fornecedores, sizeof(Fornecedor) * (totalFornecedores + 1));
    fornecedores[totalFornecedores++] = f;

    salvarFornecedor();
    formatarPrompt("FORNECEDOR CADASTRADO COM SUCESSO! PRESSIONE ENTER.");
    setbuf(stdin, NULL);
    getchar();
}

// Função para listar todos os fornecedores cadastrados
void listarFornecedor() {

    if (totalFornecedores == 0) {
        formatarPrompt("NENHUM FORNECEDOR CADASTRADO. PRESSIONE ENTER.");
        setbuf(stdin, NULL);
        getchar();
        return;
    }

    printf("      \033[4mLISTA DE FORNECEDORES:\033[0m\n\n");
    for (int i = 0; i < totalFornecedores; i++) {
        printf("\033[100;97m[ID: %d]\033[0m \nNome: %s | Cidade: %s | UF: %s | CNPJ: %s | Ramo: %s | Telefone: %s | Email: %s | Linha de Fornecimento: %s\n",
               fornecedores[i].id, fornecedores[i].nome, fornecedores[i].cidade,
               fornecedores[i].uf, fornecedores[i].cnpj, fornecedores[i].ramo,
               fornecedores[i].telefone, fornecedores[i].email, fornecedores[i].linhaFornecimento);
    }

    formatarPrompt("LISTA DE FORNECEDORES. PRESSIONE ENTER.");
    setbuf(stdin, NULL);
    getchar();
}

// Função para atualizar os dados de um fornecedor
void atualizarFornecedor() {

    if (totalFornecedores == 0) {
        formatarPrompt("NENHUM FORNECEDOR CADASTRADO. CADASTRE UM FORNECEDOR PRIMEIRO.");
        setbuf(stdin, NULL);
        getchar();
        return;
    }

    int id;
    listarFornecedor();
    formatarPrompt("DIGITE O ID DO FORNECEDOR A SER ATUALIZADO:");
    scanf("%d", &id);

    for (int i = 0; i < totalFornecedores; i++) {
        if (fornecedores[i].id == id) {
            int opcao;
            do {
                system("cls");
                exibirCabecalho();
                printf("      \033[4mATUALIZAR FORNECEDOR DE ID %d :\033[0m\n\n", id);
                printf("  [1] NOME: %s\n", fornecedores[i].nome);
                printf("  [2] CIDADE: %s\n", fornecedores[i].cidade);
                printf("  [3] UF: %s\n", fornecedores[i].uf);
                printf("  [4] CNPJ: %s\n", fornecedores[i].cnpj);
                printf("  [5] RAMO DE ATIVIDADE: %s\n", fornecedores[i].ramo);
                printf("  [6] TELEFONE: %s\n", fornecedores[i].telefone);
                printf("  [7] EMAIL: %s\n", fornecedores[i].email);
                printf("  [8] LINHA DE FORNECIMENTO: %s\n", fornecedores[i].linhaFornecimento);
                formatarPrompt("ESCOLHA O CAMPO PARA ATUALIZAR OU [0] PARA SAIR:");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        printf("  NOVO NOME: ");
                        scanf(" %[^\n]", fornecedores[i].nome);
                        break;
                    case 2:
                        printf("  NOVA CIDADE: ");
                        scanf(" %[^\n]", fornecedores[i].cidade);
                        break;
                    case 3:
                        printf("  NOVA UF: ");
                        scanf(" %[^\n]", fornecedores[i].uf);
                        break;
                    case 4:
                        printf("  NOVO CNPJ: ");
                        scanf(" %[^\n]", fornecedores[i].cnpj);
                        break;
                    case 5:
                        printf("  NOVO RAMO DE ATIVIDADE: ");
                        scanf(" %[^\n]", fornecedores[i].ramo);
                        break;
                    case 6:
                        printf("  NOVO TELEFONE: ");
                        scanf(" %[^\n]", fornecedores[i].telefone);
                        break;
                    case 7:
                        printf("  NOVO EMAIL: ");
                        scanf(" %[^\n]", fornecedores[i].email);
                        break;
                    case 8:
                        printf("  NOVA LINHA DE FORNECIMENTO: ");
                        scanf(" %[^\n]", fornecedores[i].linhaFornecimento);
                        break;
                    case 0:
                        formatarPrompt("SAINDO SEM ALTERACOES! PRESSIONE ENTER.");
                        break;
                    default:
                        formatarPrompt("OPCAO INVALIDA!");
                }

                if (opcao != 0) {
                    formatarPrompt("DESEJA ATUALIZAR OUTRO CAMPO? (1-SIM / 0-NAO):");
                    int continuar;
                    scanf("%d", &continuar);
                    if (!continuar) {
                        salvarFornecedor();
                        formatarPrompt("ALTERACOES SALVAS COM SUCESSO! PRESSIONE ENTER.");
                        setbuf(stdin, NULL);
                        getchar();
                        break;
                    }
                }

            } while (opcao != 0);

            return;
        }
    }

}

// Função para excluir um fornecedor
void excluirFornecedor() {

    if (totalFornecedores == 0) {
        formatarPrompt("NENHUM FORNECEDOR CADASTRADO. CADASTRE UM FORNECEDOR PRIMEIRO.");
        setbuf(stdin, NULL);
        getchar();
        return;
    }

    int id;
    listarFornecedor();
    formatarPrompt("DIGITE O ID DO FORNECEDOR A SER EXCLUIDO:");
    setbuf(stdin, NULL);
    scanf("%d", &id);

    for (int i = 0; i < totalFornecedores; i++) {
        if (fornecedores[i].id == id) {
            for (int j = i; j < totalFornecedores - 1; j++) {
                fornecedores[j] = fornecedores[j + 1];
            }
            totalFornecedores--;
            fornecedores = realloc(fornecedores, sizeof(Fornecedor) * totalFornecedores);

            salvarFornecedor();
            formatarPrompt("FORNECEDOR EXCLUIDO COM SUCESSO! PRESSIONE ENTER.");
            setbuf(stdin, NULL);
            getchar();
            return;

        }
    }

}

// Função para cadastrar uma nova compra
void cadastrarCompra() {
    Compra c;

    c.id = ++idCompra;

    char buffer[100];
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("      \033[4mCADASTRAR COMPRA:\033[0m\n\n");

    printf("  MATERIAL (OBJETO DA COMPRA):");
    fgets(c.linhaFornecimento, sizeof(c.linhaFornecimento), stdin);
    c.linhaFornecimento[strcspn(c.linhaFornecimento, "\n")] = '\0';

    printf("  MARCA DE REFERENCIA:");
    fgets(c.marca, sizeof(c.marca), stdin);
    c.marca[strcspn(c.marca, "\n")] = '\0';

    printf("  MODELO DE REFERENCIA:");
    fgets(c.modelo, sizeof(c.modelo), stdin);
    c.modelo[strcspn(c.modelo, "\n")] = '\0';

    int quantidadeValida = 0;
    while (!quantidadeValida) {
        printf("  QUANTIDADE:");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &c.quantidade) == 1) quantidadeValida = 1;
        else formatarPrompt("ENTRADA INVALIDA! DIGITE UM NUMERO INTEIRO:\n");
    }

    do {
        printf("  STATUS DA COMPRA (1-ABERTA / 2-FECHADA):");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &c.status);
    } while (c.status != 1 && c.status != 2);

    printf("  DEMANDANTE COM CONTATO: ");
    fgets(c.demandante, sizeof(c.demandante), stdin);
    c.demandante[strcspn(c.demandante, "\n")] = '\0';

    compras = realloc(compras, sizeof(Compra) * (totalCompras + 1));
    compras[totalCompras++] = c;
    salvarCompra();
    formatarPrompt("COMPRA CADASTRADA COM SUCESSO! APERTE ENTER.");
    getchar();
}

// Função para listar todas as compras cadastradas
void listarCompra() {
    if (totalCompras == 0) {
        formatarPrompt("NENHUMA COMPRA CADASTRADA. PRESSIONE ENTER.");
        setbuf(stdin, NULL);
        getchar();
        return;
    }
    printf("      \033[4mLISTA DE COMPRAS\033[0m\n\n");

    // Listar compras abertas
    printf("  \033[4mCOMPRAS ABERTAS:\033[0m\n\n");
    for (int i = 0; i < totalCompras; i++) {
        if (compras[i].status == 1) { // Status 1 - Aberta
            Compra c = compras[i];
            printf("\n\033[100;97m[ID: %d]\033[0m \n", c.id);
            printf("Objeto: %s | ", c.linhaFornecimento);
            printf("Marca de referencia: %s | ", c.marca);
            printf("Modelo de referencia: %s | ", c.modelo);
            printf("Quantidade: %d | ", c.quantidade);
            printf("Status: Aberta | ");
            printf("Demandante com contato: %s", c.demandante);
        }
    }

    // Listar compras fechadas
    printf("\n\n  \033[4mCOMPRAS FECHADAS:\033[0m\n\n");
    for (int i = 0; i < totalCompras; i++) {
        if (compras[i].status == 2) { // Status 2 - Fechada
            Compra c = compras[i];
            printf("\n\033[100;97m[ID: %d]\033[0m \n", c.id);
            printf("Objeto: %s | ", c.linhaFornecimento);
            printf("Marca de referencia: %s | ", c.marca);
            printf("Modelo de referencia: %s | ", c.modelo);
            printf("Quantidade: %d | ", c.quantidade);
            printf("Status: Fechada | ");
            printf("Demandante com contato: %s", c.demandante);
        }
    }

    formatarPrompt("LISTA DE COMPRAS. PRESSIONE ENTER.");
    setbuf(stdin, NULL);
    getchar();
}

// Função para atualizar os dados da compra
void atualizarCompra() {

    if (totalCompras == 0) {
        formatarPrompt("NENHUMA COMPRA CADASTRADA. CADASTRE UMA COMPRA PRIMEIRO.");
        setbuf(stdin, NULL);
        getchar();
        return;
    }

    int id;
    listarCompra();
    formatarPrompt("DIGITE O ID DA COMPRA A SER ATUALIZADA:");
    scanf("%d", &id);

    for (int i = 0; i < totalCompras; i++) {
        if (compras[i].id == id) {
            int opcao;
            do {
                system("cls");
                exibirCabecalho();
                printf("      \033[4mATUALIZAR COMPRA DE ID %d \033[0m\n\n", id);
                printf("  [1] OBJETO: %s\n", compras[i].linhaFornecimento);
                printf("  [2] MARCA DE REFERENCIA: %s\n", compras[i].marca);
                printf("  [3] MODELO DE REFERENCIA: %s\n", compras[i].modelo);
                printf("  [4] QUANTIDADE: %d\n", compras[i].quantidade);
                printf("  [5] STATUS: %s\n", compras[i].status == 1 ? "Aberta" : "Fechada");
                printf("  [6] DEMANDANTE COM CONTATO: %s\n", compras[i].demandante);

                formatarPrompt("ESCOLHA O CAMPO PARA ATUALIZAR OU [0] PARA SAIR:");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        printf("  NOVO MATERIAL (OBJETO DA COMPRA):");
                        scanf(" %[^\n]", compras[i].linhaFornecimento);
                        break;

                    case 2:
                        printf("  NOVA MARCA DE REFERENCIA:");
                        scanf(" %[^\n]", compras[i].marca);
                        break;
                    case 3:
                        printf("  NOVA MODELO DE REFERENCIA:");
                        scanf(" %[^\n]", compras[i].modelo);
                        break;
                    case 4:
                        printf("  NOVA QUANTIDADE:");
                        scanf("%d", &compras[i].quantidade);
                        break;
                    case 5:
                        do {
                            printf("  NOVO STATUS (1-ABERTA / 2-FECHADA):");
                            scanf("%d", &compras[i].status);
                            if (compras[i].status != 1 && compras[i].status != 2) {
                                formatarPrompt("OPCAO INVALIDA! ESCOLHA 1 OU 2.");
                                setbuf(stdin, NULL);
                                getchar();
                            }
                        } while (compras[i].status != 1 && compras[i].status != 2);
                        break;
                    case 6 :
                        printf("  NOVO DEMANDANTE / CONTATO:");
                        scanf(" %[^\n]", compras[i].demandante);
                        break;
                    case 0:
                        formatarPrompt("SAINDO SEM ALTERACOES! PRESSIONE ENTER.");
                        break;
                    default:
                        formatarPrompt("OPCAO INVALIDA!");
                }

                if (opcao != 0) {
                    formatarPrompt("DESEJA ALTERAR OUTRO CAMPO? (1-SIM / 0-NAO):");
                    int continuar;
                    scanf("%d", &continuar);
                    if (!continuar) {
                        salvarCompra();
                        formatarPrompt("ALTERACOES SALVAS COM SUCESSO! PRESSIONE ENTER.");
                        setbuf(stdin, NULL);
                        getchar();
                        break;
                    }
                }

            } while (opcao != 0);

            return;
        }
    }

}

// Função para excluir uma compra
void excluirCompra() {

    if (totalCompras == 0) {
        formatarPrompt("NENHUMA COMPRA CADASTRADA. CADASTRE UMA COMPRA PRIMEIRO.");
        setbuf(stdin, NULL);
        getchar();
        return;
    }

    int id;
    listarCompra();
    formatarPrompt("DIGITE O ID DA COMPRA A SER EXCLUIDA:");
    setbuf(stdin, NULL);
    scanf("%d", &id);

    for (int i = 0; i < totalCompras; i++) {
        if (compras[i].id == id) {
            // Deslocar as compras para preencher o espaço da compra excluída
            for (int j = i; j < totalCompras - 1; j++) {
                compras[j] = compras[j + 1];
            }
            totalCompras--;
            compras = realloc(compras, sizeof(Compra) * totalCompras);

            salvarCompra();
            formatarPrompt("COMPRA EXCLUIDA COM SUCESSO! PRESSIONE ENTER.");
            setbuf(stdin, NULL);
            getchar();
            return;
        }
    }

}

// Função para verificar se duas strings têm pelo menos 4 letras consecutivas iguais (case-insensitive)
int filtrar(const char *str1, const char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    for (int i = 0; i <= len1 - 4; i++) {
        for (int j = 0; j <= len2 - 4; j++) {
            int match = 1;
            for (int k = 0; k < 4; k++) {
                if (tolower(str1[i + k]) != tolower(str2[j + k])) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                return 1; // Encontrou uma subsequência de 4 letras consecutivas iguais
            }
        }
    }
    return 0; // Não encontrou
}

// Função para associar fornecedores a uma compra - match
void match() {
    if (totalCompras == 0) {
        formatarPrompt("NENHUMA COMPRA CADASTRADA. CADASTRE UMA COMPRA PRIMEIRO.");
        setbuf(stdin, NULL);
        getchar();
        return;
    }

    listarCompra();
    int id;
    formatarPrompt("DIGITE O ID DA COMPRA PARA BUSCAR FORNECEDORES EM POTENCIAL:");
    scanf("%d", &id);

    system("cls");
    exibirCabecalho();


    // Procurar a compra pelo ID e exibir os detalhes
    for (int i = 0; i < totalCompras; i++) {
        if (compras[i].id == id) {
            Compra c = compras[i];
            printf("      \033[4mCOMPRA \033[100;97m[ID: %d]\033[0m ABAIXO:\033[0m\n\n", id);
            printf("  OBJETO: %s\n", c.linhaFornecimento);
            printf("  MARCA DE REFERENCIA: %s\n", c.marca);
            printf("  MODELO DE REFERENCIA: %s\n", c.modelo);
            printf("  QUANTIDADE: %d\n", c.quantidade);
            printf("  STATUS: %s\n", c.status == 1 ? "Aberta" : "Fechada");
            printf("  DEMANDANTE COM CONTATO: %s\n", c.demandante);

            // Listar fornecedores associados ao objeto da compra
            printf("\n\n      \033[4mFORNECEDORES COM MATCH PARA A OPORTUNIDADE DE COMPRA (SOLICITAR COTACOES):\033[0m\n\n");
            int encontrou = 0;
            for (int j = 0; j < totalFornecedores; j++) {
                if (filtrar(fornecedores[j].linhaFornecimento, c.linhaFornecimento)) {
                    printf("\033[100;97m[ID: %d]\033[0m\n Nome: %s | Cidade: %s | UF: %s | CNPJ: %s | Telefone: %s | Email: %s\n",
                           fornecedores[j].id, fornecedores[j].nome, fornecedores[j].cidade,
                           fornecedores[j].uf, fornecedores[j].cnpj, fornecedores[j].telefone,
                           fornecedores[j].email);
                    encontrou = 1;
                }
            }

            if (!encontrou) {
                printf("  NENHUM FORNECEDOR EM POTENCIAL ENCONTRADO PARA ESTA COMPRA.\n");
            }

            formatarPrompt("PRESSIONE ENTER PARA VOLTAR AO MENU.");
            setbuf(stdin, NULL);
            getchar();
            return;
        }
    }

}

// Função para exibir o menu principal
// e chamar as funções correspondentes
void menu() {
    int op;
    do {
        system("cls");
        exibirCabecalho();

        printf("      \033[4mENCONTRE UM FORNECEDOR POTENCIAL PARA SUA COMPRA!\033[0m\n\n");
        printf("  [1] MATCH  \n\n");
        printf("      \033[4mCRIE OU GERENCIE SUAS COMPRAS:\033[0m\n\n");
        printf("  [2] CADASTRAR COMPRA\n");
        printf("  [3] LISTAR COMPRAS\n");
        printf("  [4] ATUALIZAR COMPRA\n");
        printf("  [5] EXCLUIR COMPRA\n\n");
        printf("      \033[4mGERENCIE SEUS FORNECEDORES:\033[0m\n\n");
        printf("  [6] CADASTRAR FORNECEDOR\n");
        printf("  [7] LISTAR FORNECEDORES\n");
        printf("  [8] ATUALIZAR FORNECEDOR\n");
        printf("  [9] EXCLUIR FORNECEDOR\n\n");
        formatarPrompt("ESCOLHA A OPCAO DESEJADA OU [0] P/ SAIR:");

        scanf("%d", &op);
        system("cls");
        exibirCabecalho();

        switch (op) {
            case 1: match(); break;
            case 2: cadastrarCompra(); break;
            case 3: listarCompra(); break;
            case 4: atualizarCompra(); break;
            case 5: excluirCompra(); break;
            case 6: cadastrarFornecedor(); break;
            case 7: listarFornecedor(); break;
            case 8: atualizarFornecedor(); break;
            case 9: excluirFornecedor(); break;
            case 0:
            formatarPrompt("ENCERRANDO O SISTEMA...");
            Sleep(2000);
            break;
            default: formatarPrompt("OPCAO INVALIDA!\n");
        }
    } while (op != 0);
}

// Função principal - main
// Carrega os fornecedores e compras do arquivo, chama o menu e salva os dados ao sair
int main() {
    carregarFornecedor();
    carregarCompra();
    menu();
    salvarFornecedor();
    salvarCompra();
    free(fornecedores);
    free(compras);
    return 0;
}
