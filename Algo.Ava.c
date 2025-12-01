#include <stdio.h>
#include <string.h>

#define MAX 50

struct Livro
{
    char titulo[50];
    char autor[50];
};

int main() {
    struct Livro livros[MAX];
    int total = 0;
    int opcao;

do {
    printf("\n1 - Cadastrar livro:");
    printf("\n2 - Listar livros:");
    printf("\n3 - Sair:");
    printf("\nEscolha: ");
    scanf("%d", &opcao);
    getchar();

    if(opcao == 1) {
        if(total < MAX) {
            printf("Título: ");
            fgets(livros[total].titulo, 50, stdin);

            printf("Autor: ");
            fgets(livros[total].autor, 50, stdin);

            total++;
            printf("Livros cadastrado!\n");
        } else {

        }
    }

    else if(opcao == 2) {
        for(int i = 0; i < total; i++){
            printf("\nLivro %d: \nTitulo: %Autor: %s, i+1, livros[i].titulo, livros[i].autor");
        }
    }
} while (opcao != 3);

    return 0;
}
