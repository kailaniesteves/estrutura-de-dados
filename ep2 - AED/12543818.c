/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   <turma> - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP 2 - Fila Preferencial                                      **/
/**                                                                 **/
/**   Kailani Esteves Barboza                   12543818            **/
/**                                                                 **/
/*********************************************************************/

#include "filapreferencial.h"

PFILA criarFila(){
    PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
    res->cabeca = (PONT) malloc(sizeof(ELEMENTO));
    res->inicioNaoPref = res->cabeca;
    res->cabeca->id = -1;
    res->cabeca->ehPreferencial = false;
    res->cabeca->ant = res->cabeca;
    res->cabeca->prox = res->cabeca;
    return res;
}

int tamanho(PFILA f){
	PONT atual = f->cabeca->prox;
	int tam = 0;
	while (atual != f->cabeca) {
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual;
		atual = atual->prox;
	}
	return NULL;
}

void exibirLog(PFILA f){
	int numElementos = tamanho(f);
	printf("\nLog fila [elementos: %i]\t- Inicio:", numElementos);
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->prox;
	}
	printf("\n                       \t-    Fim:");
	atual = f->cabeca->ant;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->ant;
	}
	printf("\n\n");
}


bool consultarPreferencial(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual->ehPreferencial;
		atual = atual->prox;
	}
	return -1;
}


bool inserirPessoaNaFila(PFILA f, int id, bool ehPreferencial){
	
	if (id < 0) return false;
	if (buscarID(f, id)) return false;
	PONT aux;
		
	PONT novo = (PONT) malloc(sizeof(ELEMENTO));
	
	novo->id = id;
	novo->ehPreferencial = ehPreferencial;
	
	if(f->cabeca->prox == f->cabeca){
		f->cabeca->prox = novo;
		f->cabeca->ant = novo;
		novo->ant = f->cabeca;
		novo->prox = f->cabeca;
		if (ehPreferencial == false)
			if (f->inicioNaoPref == f->cabeca)
				f->inicioNaoPref = novo;
		return true;
	}
	
	if (ehPreferencial == true){
		novo->prox = f->inicioNaoPref;
		aux = f->inicioNaoPref->ant;
		f->inicioNaoPref->ant->prox = novo;
		f->inicioNaoPref->ant = novo;
		novo->ant= aux;
	}else{
		if (f->inicioNaoPref == f->cabeca)
			f->inicioNaoPref = novo;
		novo->prox = f->cabeca;
		aux = f->cabeca->ant;
		f->cabeca->ant = novo;
		novo->ant = aux;
		novo->ant->prox = novo;
	}
	
	return true;
}

bool atenderPrimeiraDaFila(PFILA f, int* id){

	if (f->cabeca->prox == f->cabeca && f->cabeca->ant == f->cabeca) return false;
	PONT aux;
	
	*id = f->cabeca->prox->id;
	
	if (f->cabeca->prox->ehPreferencial == false)
		f->inicioNaoPref = f->cabeca->prox->prox;
	
	aux = f->cabeca->prox->prox;
	aux->ant = f->cabeca;
	free(f->cabeca->prox);
	f->cabeca->prox = aux;
		
	return true;
}


bool desistirDaFila(PFILA f, int id){
	
	PONT aux, exc;
	exc = buscarID(f, id);
	if(exc == NULL) return false;
	
	if(exc == f->inicioNaoPref)
		f->inicioNaoPref = exc->prox;
	
	aux = exc->ant;
	aux->prox = exc->prox;
	exc->prox->ant = aux;
	free(exc);

	return true;
}
