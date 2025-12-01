#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

typedef struct 
{
    char nome;
    int id;
} Peca;

typedef struct 
{
    Peca v[TAM_FILA];
    int frente, tras, qtd;
} Fila;

typedef struct 
{
    Peca v[TAM_PILHA];
    int topo;
} Pilha;

char tipos[] = {'I','O','T','L'};
int idGlobal = 0;

Peca gerarPeca(){
    Peca p;
    p.nome = tipos[rand()% 4];
    p.id = idGlobal++;
    return p;
}

void iniciarFila(Fila *f) {
    f->frente = f->tras = f->qtd = 0;
    for (int i = 0; i < TAM_FILA; i++)
    f->v[f->tras = (f->tras + i)% TAM_FILA] = gerarPeca(), f->qtd++;
}

void iniciarPilha(Pilha *p){
    p->topo = -1;
}



int filaVazia(Fila *f) {return f->qtd == 0;}
int filaCheia(Fila *f) {return f->qtd == TAM_FILA;}
int pilhaVazia(Pilha *p) {return p->topo == -1;}
int pilhaCheia(Pilha *p) {return p->topo == TAM_PILHA - 1;}

Peca desenfileirar(Fila *f) {
    Peca p = f->v[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->qtd--;
    return p;
}

void enfileirar(Fila *f, Peca p) {
    if (!filaCheia(f)){
        f->tras = (f->tras + 1) % TAM_FILA;
        f->qtd++;
    }
}

void empilhar(Pilha *p, Peca x) {
    if (!pilhaCheia(p)) p->v[++p->topo] = x;
}

Peca desempilhar(Pilha *p) {
    return p->v[p->topo--];
}

void mostrar(Fila *f, Pilha *p) {
    printf("\nFila: ");
    for (int i = 0, pos = f->frente; i < f->qtd; i++, pos = (pos + 1) % TAM_FILA)
        printf("[%c %d]" , f->v[pos].nome, f->v[pos].id);

    printf("\nPilha (Topo -> Base): ");
    for (int i = p->topo; i >= 0; i--)
        printf("[%c %d]", p->v[i].nome, p->v[i].id);
    printf("\n");
}

int main() {
    srand(time(NULL));
    Fila fila; Pilha pilha;
    iniciarFila(&fila);
    iniciarPilha(&pilha);

    int op;
    do {
        mostrar(&fila, &pilha);
        printf("\n1-Jogar   2-Reservar  3-Usar reserva\n");
        printf("4-Trocar topo/frente    5-Troca múltipla\n0-Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        if (op == 1 && !filaVazia(&fila)){
            desenfileirar(&fila);
            enfileirar(&fila, gerarPeca());
        }

        else if (op == 2 && !filaVazia(&fila) && !pilhaCheia(&pilha)) {
            empilhar(&pilha, desenfileirar(&fila));
            enfileirar(&fila, gerarPeca());
        }

        else if (op == 3 && !pilhaVazia(&pilha))
            desempilhar(&pilha);
            
        else if (op == 4 && !pilhaVazia(&pilha) && !filaVazia(&fila)){
            int f = fila.frente;
            Peca tmp = fila.v[f];
            fila.v[f] = pilha.v[pilha.topo];
            pilha.v[pilha.topo] = tmp;
        }

        else if (op == 5 && fila.qtd >= 3 && pilha.topo == 2) {
            for (int i = 0; i < 3; i++) {
                int idx = (fila.frente + i) % TAM_FILA;
                Peca tmp = fila.v[idx];
                fila.v[idx] = pilha.v[i];
                pilha.v[i] = tmp;

            }
        }

    } while (op != 0);

    return 0;
}