/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   <turma> - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP3 - Fila de Prioridade (utilizando heap)                    **/
/**                                                                 **/
/**   Kailani Esteves Barboza                   12543818            **/
/**                                                                 **/
/*********************************************************************/

#include "filaDePrioridade.h"
#define MAX 5

PFILA criarFila(){
  PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
  res->referencias = (PONT*) malloc(sizeof(PONT)*MAX);
  res->heap = (PONT*) malloc(sizeof(PONT)*MAX);
  int i;
  for (i=0;i<MAX;i++) {
    res->referencias[i] = NULL;
    res->heap[i] = NULL;
  }
  res->elementosNoHeap = 0;
  return res;
}


bool exibirLog(PFILA f){
  printf("Log [elementos: %i]\n", f->elementosNoHeap);
  PONT atual;
  int i;
  for (i=0;i<f->elementosNoHeap;i++){
    atual = f->heap[i];
    printf("[%i;%f;%i] ", atual->id, atual->prioridade, atual->posicao);
  }
  printf("\n\n");
}

int tamanho(PFILA f){
  int tam = 0;
  while(f->heap[tam+1] != NULL){
    tam = tam + 1;
  }
  return tam;
}

void maxHeapify(PFILA f, int i){
	int maior, pos;
	int e = 2 * i + 1; 
	int d = 2 * i + 2;
	
	if ((e <= f->elementosNoHeap) && (f->heap[e]->prioridade > f->heap[i]->prioridade)){
		maior = e;
	}else{
		maior = i;
	}
	if ((d <= f->elementosNoHeap) && (f->heap[d]->prioridade > f->heap[maior]->prioridade)){
		maior = d;
	}
	if (maior != i){
		PONT aux = f->heap[i];
		pos = f->heap[i]->posicao;
		int pos2 = f->heap[maior]->posicao;
		f->heap[i] = f->heap[maior];
		f->heap[maior] = aux;
		f->heap[i]->posicao = pos;
		f->heap[maior]->posicao = pos2;
		int pai = (i-1)/2; 

		maxHeapify(f, pai);
	}
	return;
}

void maxHeapify2(PFILA f, int i){
	int maior, pos;
	int e = 2 * i + 1; 
	int d = 2 * i + 2;
	
	if ((e < f->elementosNoHeap) && (f->heap[e]->prioridade > f->heap[i]->prioridade)){
		maior = e;
	}else{
		maior = i;
	}
	if ((d < f->elementosNoHeap) && (f->heap[d]->prioridade > f->heap[maior]->prioridade)){
		maior = d;
	}
	if (maior != i){
		PONT aux = f->heap[i];
		pos = f->heap[i]->posicao;
		int pos2 = f->heap[maior]->posicao;
		f->heap[i] = f->heap[maior];
		f->heap[maior] = aux;
		f->heap[i]->posicao = pos;
		f->heap[maior]->posicao = pos2;
		int pai = (i-1)/2; 

		maxHeapify(f, pai);
	}
	return;
}

void excHeapify(PFILA f, int i){
	int maior, pos;
	int e = 2 * i + 1; 
	int d = 2 * i + 2;
	
	if ((e <= f->elementosNoHeap) && (f->heap[e]->prioridade > f->heap[i]->prioridade)){
		maior = e;
	}else{
		maior = i;
	}
	if ((d <= f->elementosNoHeap) && (f->heap[d]->prioridade > f->heap[maior]->prioridade)){
		maior = d;
	}
	if (maior != i){
		PONT aux = f->heap[i];
		pos = f->heap[i]->posicao;
		int pos2 = f->heap[maior]->posicao;
		f->heap[i] = f->heap[maior];
		f->heap[maior] = aux;
		f->heap[i]->posicao = pos;
		f->heap[maior]->posicao = pos2;

		maxHeapify(f, i);
	}
	return;
}

bool inserirElemento(PFILA f, int id, float prioridade){
  
  if ((id < 0) || (id >= MAX) || (f->referencias[id] != NULL)) return false;
  
  
  PONT novo = (PONT*) malloc(sizeof(PONT));
  novo->id = id;
  novo->prioridade = prioridade;
  f->heap[f->elementosNoHeap] = novo;
  novo->posicao = f->elementosNoHeap;
  int i = (novo->posicao - 1)/2;
  maxHeapify(f, i); 
  f->referencias[id] = novo;
  f->elementosNoHeap = f->elementosNoHeap + 1;
  
  return true;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
  
  if((id < 0) || (id >= MAX) || (f->referencias[id] == NULL) || (f->referencias[id]->prioridade >= novaPrioridade)) return false;
  
  f->referencias[id]->prioridade = novaPrioridade;
  int i = (f->referencias[id]->posicao)/2;
  maxHeapify2(f, i);
  
  return true;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
  
  if((id < 0) || (id >= MAX) || (f->referencias[id] == NULL) || (f->referencias[id]->prioridade <= novaPrioridade)) return false;
  
  f->referencias[id]->prioridade = novaPrioridade;
  excHeapify(f, f->referencias[id]->posicao);
  
  return true;
}

PONT removerElemento(PFILA f){
  
  if (f->heap[1] == NULL) return NULL;
  
  PONT res = f->heap[0];
  
  f->referencias[res->id] = NULL;
  
  for(int i = 0; i < f->elementosNoHeap; i++){
  	f->heap[i-1] = f->heap[i];
  	f->heap[i]->posicao = f->heap[i]->posicao - 1;
  }
  
  excHeapify(f, 0);
  f->heap[f->elementosNoHeap] = NULL;
  f->elementosNoHeap = f->elementosNoHeap - 1;
  
  return res;
}

bool consultarPrioridade(PFILA f, int id, float* resposta){
  if((id < 0) || (id >= MAX) || (f->referencias[id] == NULL)) return false;
  
  *resposta = f->referencias[id]->prioridade;
  
  return true;
}
