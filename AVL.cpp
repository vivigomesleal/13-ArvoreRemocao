﻿#include <iostream>
using namespace std;

/* -----------------------------------------------------------
   Estrutura do nó da Árvore AVL
----------------------------------------------------------- */
struct NO {
    int valor;
    NO* esq;
    NO* dir;
    int altura;       // usado para o balanceamento
};

/* Raiz da árvore */
NO* raiz = NULL;

/* ----------------- Protótipos ----------------------------- */
// Interface principal
void menu();
void inicializar();
void inserir();
void exibir();
void exibirQuantidade();
void buscar();
void remover();

// Funções auxiliares da árvore
NO* insereArvore(NO* no, int valor);
NO* criaNO(int valor);
int   elementosArvore(NO* no);
void  exibirElementosArvore(NO* no, int espaco, bool direita);
void  buscarElementoArvore(NO* no, int valor);
NO* removerArvore(NO* no, int valor);

// Funções auxiliares de balanceamento
int   alturaNo(NO* no);
int   fatorBalanceamento(NO* no);
NO* girarDireita(NO* no);
NO* girarEsquerda(NO* no);
int   maior(int a, int b);
NO* balancearNo(NO* no);

/* ================= IMPLEMENTAÇÃO ========================= */
// ---------- Funções de interface ---------
int main() {
    menu();
}

void menu() {
    int op = 0;
    while (op != 7) {
        system("cls");                // Limpa console (Windows)
        cout << "========== Menu Arvore AVL ==========\n\n";
        cout << "1 - Inicializar Arvore\n";
        cout << "2 - Exibir quantidade de elementos\n";
        cout << "3 - Inserir elemento\n";
		cout << "4 - Remover elemento\n";
        cout << "5 - Exibir arvore\n";
        cout << "6 - Buscar elemento\n";
        cout << "7 - Sair\n\n";
        cout << "Opcao: ";
        cin >> op;

        switch (op) {
                   case 1:
                       inicializar();
                       break;
                   case 2:
                       exibirQuantidade();
                       break;
                   case 3:
                       inserir();
                       break;
				   case 4:
                       remover();
					   break;
                   case 5:
                       exibir();
                       break;
                   case 6:
                       buscar();
                       break;
               }

		cout << endl; 
        if (op != 7) system("pause"); // Aguarda tecla (Windows)
    }
}

void inicializar() {
    raiz = NULL;
    cout << "Arvore inicializada!\n";
}

void inserir() {
    int v;
    cout << "Digite o elemento: ";
    cin >> v;
    raiz = insereArvore(raiz, v);
}

void remover() {
    int v;
    cout << "Digite o elemento: ";
    cin >> v;
    raiz = removerArvore(raiz, v);
}

void exibirQuantidade() {
    cout << "Quantidade de elementos: "
        << elementosArvore(raiz) << "\n";
}

void exibir() {
    if (raiz == NULL) {
        cout << "Arvore vazia!\n";
        return;
    }
    cout << "\n===== Estrutura da Arvore (raiz no topo) =====\n\n";
    exibirElementosArvore(raiz, 0, false);
}

void buscar() {
    int v;
    cout << "Digite o elemento: ";
    cin >> v;
    buscarElementoArvore(raiz, v);
}

// ---------- Criação e inserção ----------
NO* criaNO(int valor) {
    NO* novo = (NO*)malloc(sizeof(NO));
    if (novo == NULL) return NULL;      // Falha de alocação

    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->altura = 0;
    return novo;
}

int alturaNo(NO* no) {
    if (no == NULL) return -1;
    return no->altura;
}

int maior(int a, int b) {
    if (a > b) return a;
    return b;
}

int fatorBalanceamento(NO* no) {
    if (no == NULL) return 0;
    return alturaNo(no->esq) - alturaNo(no->dir);
}

NO* girarDireita(NO* y) {  
   /* Rotação simples à direita  
             y                x  
            / \              / \  
           x   T3   =>      T1  y  
          / \                  / \  
        T1  T2               T2  T3  
   */  

   // Passo 1: Armazene o filho esquerdo de 'y' em uma variável temporária 'x'.  
   // Passo 2: Transfira a subárvore direita de 'x' para a subárvore esquerda de 'y'.  
   // Passo 3: Atualize 'x' para ser o novo nó raiz da subárvore.  
   // Passo 4: Recalcule as alturas dos nós afetados.  
   // Passo 5: Retorne o novo nó raiz ('x').  

    NO* x = y->esq;  
    NO* T2 = x->dir; 

    // Realiza a rotação  
    x->dir = y;  
    y->esq = T2;  

    // Atualiza as alturas  
    y->altura = maior(alturaNo(y->esq), alturaNo(y->dir)) + 1;  
    x->altura = maior(alturaNo(x->esq), alturaNo(x->dir)) + 1;  

	// Retorna o novo nó raiz
	return x;


}  

NO* girarEsquerda(NO* x) 
{  
   /* Rotação simples à esquerda  
           x                    y  
          / \                  / \  
         T1  y      =>        x  T3  
            / \              / \  
           T2 T3            T1 T2  
   */  

    NO* y = x->dir;      // Passo 1: filho direito de x
    NO* T2 = y->esq;     // Subárvore esquerda de y

    // Passo 2: Transfere T2 para a direita de x
    x->dir = T2;

    // Passo 3: y vira nova raiz da subárvore
    y->esq = x;

    // Passo 4: Atualiza alturas
    x->altura = maior(alturaNo(x->esq), alturaNo(x->dir)) + 1;
    y->altura = maior(alturaNo(y->esq), alturaNo(y->dir)) + 1;

    // Passo 5: Retorna nova raiz
    return y;
}

// Função auxiliar para balancear um nó AVL
NO* balancearNo(NO* no) {
    if (no == NULL) return no;
    int fb = fatorBalanceamento(no);
    // Caso Esquerda-Esquerda
    if (fb > 1 && fatorBalanceamento(no->esq) >= 0)
        return girarDireita(no);
    // Caso Esquerda-Direita
    if (fb > 1 && fatorBalanceamento(no->esq) < 0) {
        no->esq = girarEsquerda(no->esq);
        return girarDireita(no);
    }
    // Caso Direita-Direita
    if (fb < -1 && fatorBalanceamento(no->dir) <= 0)
        return girarEsquerda(no);
    // Caso Direita-Esquerda
    if (fb < -1 && fatorBalanceamento(no->dir) > 0) {
        no->dir = girarDireita(no->dir);
        return girarEsquerda(no);
    }
    return no;
}

NO* insereArvore(NO* no, int valor) {
    /* Inserção binária normal ----------------------------- */
    if (no == NULL) {
        return criaNO(valor);
    }
    if (valor < no->valor) {
        no->esq = insereArvore(no->esq, valor);
    }
    else if (valor > no->valor) {
        no->dir = insereArvore(no->dir, valor);
    }
    else {
        /* Valor já existe – não insere duplicado */
        return no;
    }
    /* Atualiza altura do nó */
    no->altura = maior(alturaNo(no->esq), alturaNo(no->dir)) + 1;
    /* Balanceamento AVL usando função auxiliar */
    return balancearNo(no);
}

NO* removerArvore(NO* no, int valor) {
    if (no == NULL) {
        cout << "Elemento NAO encontrado.\n";
        return no;
    }
    if (valor < no->valor) {
        no->esq = removerArvore(no->esq, valor);
    }
    else if (valor > no->valor) {
        no->dir = removerArvore(no->dir, valor);
    }
    else {
        if (no->esq == NULL && no->dir == NULL) {
            delete no;
            return NULL;
        }

        // Caso 1: Nó sem filhos
        // Se o nó não possui filhos (esquerda e direita são NULL), basta removê-lo e retornar NULL para o pai.
        else if (no->esq == NULL) {
            NO* temp = no->dir;
            delete no;
            return temp;
        }
        // Caso 2: Nó com apenas um filho
        // Se o nó possui apenas um filho (esquerda ou direita), retorna o ponteiro para esse filho, liberando o nó atual.
        else if (no->dir == NULL) {
            NO* temp = no->esq;
            delete no;
            return temp;
        }
        // Caso 3: Nó com dois filhos
        // Se o nó possui dois filhos, encontra o sucessor (menor valor da subárvore direita),
        // copia o valor do sucessor para o nó atual e remove recursivamente o sucessor.
        else {
            NO* sucessor = no->dir;
            while (sucessor->esq != NULL) {
                sucessor = sucessor->esq;
            }
            no->valor = sucessor->valor;
            no->dir = removerArvore(no->dir, sucessor->valor);
        }
    }
                
    // Atualiza altura e balanceia

    no->altura = maior(alturaNo(no->esq), alturaNo(no->dir)) + 1;

    return balancearNo(no);
}

// ---------- Utilidades ----------
int elementosArvore(NO* no) {
    if (no == NULL) return 0;
    return 1 + elementosArvore(no->esq) + elementosArvore(no->dir);
}

void exibirElementosArvore(NO* no, int espaco, bool direita) {
    /* Impressão recursiva “deitada”:
       └── valor
          ├── ...
          └── ...
    */
    if (no == NULL) return;

    const int DIST = 6; // deslocamento entre níveis
    espaco += DIST;

    // Exibe primeiro a subárvore direita (fica “em cima” no console)
    exibirElementosArvore(no->dir, espaco, true);

    // Impressão do nó atual
    cout << endl;
    for (int i = DIST; i < espaco; i++) cout << " ";

    if (direita)
        cout << "/-- ";
    else
        cout << "\\-- ";

    cout << no->valor << endl;

    // Exibe subárvore esquerda
    exibirElementosArvore(no->esq, espaco, false);
}

void buscarElementoArvore(NO* no, int valor) {
    if (no == NULL) {
        cout << "Elemento NAO encontrado.\n";
        return;
    }

    if (valor == no->valor) {
        cout << "Elemento encontrado!\n";
        return;
    }

    if (valor < no->valor)
        buscarElementoArvore(no->esq, valor);
    else
        buscarElementoArvore(no->dir, valor);
}
