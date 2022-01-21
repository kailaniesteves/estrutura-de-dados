/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   <turma> - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP 1 - Lista Ligada de Produtos                               **/
/**                                                                 **/
/**   Kailani Esteves Barboza                NUSP:12543818          **/
/**                                                                 **/
/*********************************************************************/
#include "listadeprodutos.h"

PLISTA criarLista(){
  PLISTA res = (PLISTA) malloc(sizeof(LISTADEPRODUTOS));
  int x;
  for (x=0;x<NUMTIPOS;x++){
    res->LISTADELISTAS[x]=(PONT) malloc(sizeof(REGISTRO));
    res->LISTADELISTAS[x]->id=-1;
    res->LISTADELISTAS[x]->quantidade=0;
    res->LISTADELISTAS[x]->valorUnitario=0;
    res->LISTADELISTAS[x]->proxProd=NULL;
  }
  return res;
}


int tamanho(PLISTA l){
  int tam = 0;
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      atual = atual->proxProd;
      tam++;
    }
  }
  return tam;
}

PONT buscarID(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) return atual;
      atual = atual->proxProd;
    }
  }
  return NULL;
}

PONT buscarIDTipo(PLISTA l, int id, int tipo){
  if (tipo<0 || tipo>=NUMTIPOS) return NULL;
  PONT atual = l->LISTADELISTAS[tipo]->proxProd;
  while (atual) {
    if (atual->id == id) return atual;
    atual = atual->proxProd;
  }
  return NULL;
}

void exibirLog(PLISTA f){
  int numElementos = tamanho(f);
  printf("Log lista [elementos: %i]\n", numElementos);
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    printf("  #TIPO: %i -> ", x);
    atual = f->LISTADELISTAS[x]->proxProd;
    while (atual){
      printf(" [%i;%i;%i;$%i]", atual->id, atual->quantidade, atual->valorUnitario, atual->quantidade*atual->valorUnitario);
      atual = atual->proxProd;
    }
    printf("\n");
  }
  printf("\n");
}

int consultarValorUnitario(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) return atual->valorUnitario;
      atual = atual->proxProd;
    }
  }
  return 0;
}

// Função auxiliar que retorna o endereço do produto procurado e do seu antecessor 
PONT buscaSequencialExc(PLISTA l, int id, PONT* ant){
	*ant = NULL;
	PONT atual;
		int x;
  		for (x=0;x<NUMTIPOS;x++){
		    *ant = NULL;
  			atual = l->LISTADELISTAS[x]->proxProd;
		    while (atual) {
			    if (atual->id == id) return atual;
		      *ant = atual;
		      atual = atual->proxProd;
		    }
		}
	return NULL;	
}

bool inserirNovoProduto(PLISTA l, int id, int tipo, int quantidade, int valor){
  
  // Consições as quais a inserção não pode ser realizada
  if ((buscarID(l, id) != NULL) || (id < 0) || (quantidade < 0) || (valor < 0) || ((tipo < 0) || (tipo > NUMTIPOS-1))) return false;
  
  
  // Alocando memória para o novo produto e atribuindo os valores de id, quantidade e valorUnitário
  REGISTRO* novo = (PONT) malloc(sizeof(REGISTRO));
  novo->id = id;
  novo->quantidade = quantidade;
  novo->valorUnitario = valor;
  
  // Ordenando o novo elemento da lista conforme o seu valor total (quantidade * valorUnitário)
  if (l->LISTADELISTAS[tipo]->proxProd != NULL){
  	PONT atual = l->LISTADELISTAS[tipo]->proxProd;
  	
  	if((atual->quantidade*atual->valorUnitario) > (valor*quantidade)){
  		novo->proxProd = l->LISTADELISTAS[tipo]->proxProd;
		l->LISTADELISTAS[tipo]->proxProd = novo;
		return true;
	  }
  	
  	while ((valor*quantidade) > (atual->quantidade*atual->valorUnitario)) {
  		if (atual->proxProd == NULL){
			atual->proxProd = novo;
			novo->proxProd = NULL;
			return true;
		}
		if((atual->proxProd->quantidade*atual->proxProd->valorUnitario) >= (valor*quantidade)){
			novo->proxProd = atual->proxProd;
			atual->proxProd = novo;
			return true;
		}
		
		atual = atual->proxProd;
	}

  }else{
		l->LISTADELISTAS[tipo]->proxProd = novo;
		novo->proxProd = NULL;
		return true;
  }

  
}

// Função auxiliar de exclusão um produto do sistema, através do seu id
bool excluirProduto(PLISTA l, int id){
	PONT atual = buscarID(l, id);
	PONT i, ant;
	if((atual == NULL)) return false;
	i = buscaSequencialExc(l, id, &ant);
	if (ant == NULL){
		PONT atual;
		int x;
  		for (x=0;x<NUMTIPOS;x++){
  			atual = l->LISTADELISTAS[x]->proxProd;
  			while(atual){
				if (atual->id == id){
			    	l->LISTADELISTAS[x]->proxProd = i->proxProd;
				}
				atual = atual->proxProd;
			}
		}
		free(i);
	}else{
		ant->proxProd = i->proxProd;
		free(i);
	}
	
	return true;
}

bool removerItensDeUmProduto(PLISTA l, int id, int quantidade){
	
	PONT atual = buscarID(l, id);
	int tipo;
	// Consições as quais a remoção não pode ser realizada
	if ((atual == NULL) || (quantidade <= 0) || (quantidade > atual->quantidade)) return false;
	
	// Calculando a nova quantidade do produto
	int valor = atual->quantidade - quantidade;
	
	if(valor == 0){ // caso a nova quantidade seja = 0, o produto é excluído do sistema
		bool exc = excluirProduto(l, id);
		return true;
	}else{ // caso contrário, encontra-se o tipo desse produto, exclui-se ele do sistema e o inserimos novamente com a nova quantidade
		PONT teste;
		int x;
  		for (x=0;x<NUMTIPOS;x++){
  			teste = l->LISTADELISTAS[x]->proxProd;
  			while (teste) {
			    if (teste->id == id){
			    	tipo = x;
				}
				teste = teste->proxProd;
			}
		}
		x = atual->valorUnitario;
		bool exc =  excluirProduto(l, id);
		bool in = inserirNovoProduto(l, id, tipo, valor, x);
		return true;
	}	
}
bool atualizarValorDoProduto(PLISTA l, int id, int valor){

	PONT atual = buscarID(l, id);
	// Consições as quais a atualização não pode ser realizada
	if ((atual == NULL) || (valor <= 0)) return false;
	int quantidade = atual->quantidade;
	// Encontrando o tipo do produto que será atualizado
	PONT teste;
	int x, tipo;
  	for (x=0;x<NUMTIPOS;x++){
  		teste = l->LISTADELISTAS[x]->proxProd;
  		while (teste) {
			if (teste->id == id){
			    tipo = x;
			}
			teste = teste->proxProd;
		}
	}
	// Realizando a exclusão e reinserção do produto no sistema com o novo valorUnitário
	bool exc = excluirProduto(l, id);
	bool in = inserirNovoProduto(l, id, tipo, quantidade, valor);
	return true;


  return false;
}