#include "filaDePrioridade.c"

int main() {
  PFILA f = criarFila();
  int i;
	float resposta;

  if(inserirElemento(f, 0, 5)) printf("\nI: ok -- 1\n");
  else printf("nok -- 1\n");
  exibirLog(f);

  if(inserirElemento(f, 1, 10)) printf("I: ok -- 2\n");
  else printf("nok -- 2\n");
  exibirLog(f);

  if(inserirElemento(f, 2, 15)) printf("I: ok -- 3\n");
  else printf("nok -- 3\n");
  exibirLog(f);

  if(inserirElemento(f, 3, 8)) printf("I: ok -- 4\n");
  else printf("nok -- 4\n");
  exibirLog(f);

  if(inserirElemento(f, 4, 12)) printf("I: ok -- 5\n");
  else printf("nok -- 5\n");
  exibirLog(f);

  if(aumentarPrioridade(f, 3, 14)) printf("A: ok -- 6\n");
  else printf("nok -- 6\n");
  exibirLog(f);

  if(aumentarPrioridade(f, 4, 30)) printf("A: ok -- 7\n");
  else printf("nok -- 7\n");
  exibirLog(f);

  if(tamanho(f)) printf("\nVerificando Tamanho | ok -- 8\n");
  else printf("nok -- 8\n");
  exibirLog(f);

  if(aumentarPrioridade(f, 0, 29)) printf("A: ok -- 9\n");
  else printf("nok -- 9\n");
  exibirLog(f);

  PONT prioritario;
  prioritario = removerElemento(f);
  if (prioritario) printf("Rm: ok -- 10 - Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia\n");
  exibirLog(f);

  if(inserirElemento(f, 4, 25)) printf("I: ok -- 11\n");
  else printf("nok -- 11\n");
  exibirLog(f);

  if(inserirElemento(f, 4, 12)) printf("I: ok -- 12\n");
  else printf("nok -- 12\n");
  exibirLog(f);

  printf("Consultando todas as prioridades -- 13\n");
  for (i = 0; i < MAX; i++)
		if (f->heap[i]) {
			consultarPrioridade(f, i, &resposta);
			printf("id: %d, posição no heap: %d, prioridade: %f\n", i, f->referencias[i]->posicao, resposta);
		}
  printf("\n");
  
  if(reduzirPrioridade(f, 0, 5)) printf("Rd: ok -- 14\n");
  else printf("nok -- 14\n");
  exibirLog(f);

  if(reduzirPrioridade(f, 4, 11)) printf("Rd: ok -- 15\n");
  else printf("nok -- 15\n");
  exibirLog(f);

  if(reduzirPrioridade(f, 1, 1)) printf("Rd: ok -- 16\n");
  else printf("nok -- 16\n");
  exibirLog(f);

  prioritario = removerElemento(f);
  if (prioritario) printf("Rm: ok -- 17 - Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia\n");
  exibirLog(f);

  if(aumentarPrioridade(f, 0, 20)) printf("A: ok -- 18\n");
  else printf("nok -- 18\n");
  exibirLog(f);

  if(aumentarPrioridade(f, 4, 19)) printf("A: ok -- 19\n");
  else printf("nok -- 19\n");
  exibirLog(f);

  if(inserirElemento(f, 2, 18)) printf("I: ok -- 20\n");
  else printf("nok -- 20\n");
  exibirLog(f);

  return 0;
}
