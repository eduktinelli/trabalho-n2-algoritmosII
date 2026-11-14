/*
 * Alunos: 
 *  João Paulo Fagundes, 
 *  Eduardo Kauã Tinelli, 
 *  João Eduardo de Oliveira Nascimento
 */

#include <stdio.h>
#include <string.h>

// Definições de variáveis padrões
int pneus[3][4];
int tipo;              
int qtdEixos;          
int pneusPorEixo[3];   

/*
 * Tela de login
 *
 * Usuário: uniavan
 * Senha: 123
 */
void fazerLogin() {
    char login[20];
    char senha[20];

    do {
        printf("===== ACESSO GERENCIAMENTO DE PNEUS =====\n");
        printf("Usuario: ");
        scanf("%s", login);
        printf("Senha: ");
        scanf("%s", senha);

        /*
         * strcmp serve pois caso a gente tente comparar [login == "uniavan"] 
         * vai dar false por conta do endereço na memória ser diferente
         */
        if (strcmp(login, "uniavan") != 0 || strcmp(senha, "123") != 0) {
            printf("Usuario ou senha incorretos!\n\n");
        }
    } while (strcmp(login, "uniavan") != 0 || strcmp(senha, "123") != 0);

    printf("Acesso liberado!\n\n");
}

void escolherTipo() {
    printf("Escolha o tipo de eixo:\n");
    printf("1 - Toco\n");
    printf("2 - Truck\n");
    printf("3 - Carreta 3 eixos\n");
    printf("Opcao: ");
    scanf("%d", &tipo);

    // validação de escolha (precisa ser uma das opções)
    while (tipo < 1 || tipo > 3) {
        printf("Opcao invalida! Digite de novo: ");
        scanf("%d", &tipo);
    }

    if (tipo == 1) {
        qtdEixos = 2;
        pneusPorEixo[0] = 2;
        pneusPorEixo[1] = 4;
    } else if (tipo == 2) {
        qtdEixos = 3;
        pneusPorEixo[0] = 2;
        pneusPorEixo[1] = 4;
        pneusPorEixo[2] = 4;
    } else {
        qtdEixos = 3;
        pneusPorEixo[0] = 4;
        pneusPorEixo[1] = 4;
        pneusPorEixo[2] = 4;
    }
    printf("\n");
}

// validação de se o pneu já existe
int pneuExiste(int numero) {
    int i, j;

    for (i = 0; i < qtdEixos; i++) {
        for (j = 0; j < pneusPorEixo[i]; j++) {
            if (pneus[i][j] == numero) {
                return 1;
            }
        }
    }
    return 0;
}

// função para o cadastro dos pneus
void cadastrarPneus() {
    int i, j;
    int numero;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            pneus[i][j] = 0;
        }
    }

    printf("=== VINCULAR PNEUS AOS EIXOS ===\n");
    printf("Digite o numero de fogo de cada pneu (nao pode repetir).\n\n");

    for (i = 0; i < qtdEixos; i++) {
        for (j = 0; j < pneusPorEixo[i]; j++) {
            printf("Eixo %d - pneu %d: ", i + 1, j + 1);
            scanf("%d", &numero);

            // Validação se o numero já foi utilizado
            while (numero <= 0 || pneuExiste(numero) == 1) {
                if (numero <= 0) {
                    printf("Numero invalido! Digite um numero maior que zero: ");
                } else {
                    printf("Esse numero de fogo ja foi usado! Digite outro: ");
                }
                scanf("%d", &numero);
            }

            pneus[i][j] = numero;
        }
    }
    printf("\nPneus vinculados com sucesso!\n");
}

void mostrarPneus() {
    int i, j;

    printf("\n===== DISPOSICAO DOS PNEUS =====\n");
    printf("            (FRENTE)\n");

    for (i = 0; i < qtdEixos; i++) {
        printf("Eixo %d: ", i + 1);
        for (j = 0; j < pneusPorEixo[i]; j++) {
            printf("[%3d] ", pneus[i][j]);
        }
        printf("\n");
    }
    printf("================================\n");
}

// função para realizar o rodizio dos pneus
void fazerRodizio() {
    int pneuA, pneuB;
    int i, j;
    int linhaA = -1, colunaA = -1;
    int linhaB = -1, colunaB = -1;
    int aux;

    mostrarPneus();

    printf("\nDigite o numero do primeiro pneu: ");
    scanf("%d", &pneuA);
    printf("Digite o numero do segundo pneu: ");
    scanf("%d", &pneuB);

    for (i = 0; i < qtdEixos; i++) {
        for (j = 0; j < pneusPorEixo[i]; j++) {
            if (pneus[i][j] == pneuA) {
                linhaA = i;
                colunaA = j;
            }
            if (pneus[i][j] == pneuB) {
                linhaB = i;
                colunaB = j;
            }
        }
    }

    // validações para se o pneu é encontrado
    if (linhaA == -1 || linhaB == -1) {
        printf("\nPneu nao encontrado! Rodizio cancelado.\n");
    } else if (pneuA == pneuB) {
        printf("\nVoce digitou o mesmo pneu duas vezes!\n");
    } else {

        /*
         * a variável aux serve para guardar o valor inicial temporariamente
         * pois quando é feito [pneus[linhaA][colunaA] = pneus[linhaB][colunaB]]
         * se "perde" o valor do pneu A
         */

        aux = pneus[linhaA][colunaA];
        pneus[linhaA][colunaA] = pneus[linhaB][colunaB];
        pneus[linhaB][colunaB] = aux;

        printf("\nRodizio feito! Nova disposicao:\n");
        mostrarPneus();
    }
}

// função que mostra as legendas
void mostrarLegenda() {
    printf("\n===== LEGENDA =====\n");

    if (tipo == 1) {
        printf("Tipo: Toco\n");
        printf("Eixo 1 (dianteiro): DE  DD\n");
        printf("Eixo 2 (traseiro) : TEE1 TEI1 TDI1 TDE1\n");
    } else if (tipo == 2) {
        printf("Tipo: Truck\n");
        printf("Eixo 1 (dianteiro): DE  DD\n");
        printf("Eixo 2 (traseiro) : TEE1 TEI1 TDI1 TDE1\n");
        printf("Eixo 3 (traseiro) : TEE2 TEI2 TDI2 TDE2\n");
    } else {
        printf("Tipo: Carreta 3 eixos\n");
        printf("Eixo 1: TEE1 TEI1 TDI1 TDE1\n");
        printf("Eixo 2: TEE2 TEI2 TDI2 TDE2\n");
        printf("Eixo 3: TEE3 TEI3 TDI3 TDE3\n");
    }

    printf("\nSignificado:\n");
    printf("DE   : Dianteiro esquerdo\n");
    printf("DD   : Dianteiro direito\n");
    printf("TEE1 : Traseiro externo esquerdo um\n");
    printf("TEI1 : Traseiro interno esquerdo um\n");
    printf("TDI1 : Traseiro direito interno um\n");
    printf("TDE1 : Traseiro direito externo um\n");
    printf("(o numero final indica o eixo: 1, 2 ou 3)\n");
    printf("===================\n");
}

// função base: menu
int main() {
    int opcao;

    fazerLogin();
    escolherTipo();

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Vincular pneus aos eixos\n");
        printf("2 - Rodizio de pneus\n");
        printf("3 - Listar pneus\n");
        printf("4 - Legenda\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPneus();
                break;
            case 2:
                fazerRodizio();
                break;
            case 3:
                mostrarPneus();
                break;
            case 4:
                mostrarLegenda();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                // precisa selecionar uma das opções acima.
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}