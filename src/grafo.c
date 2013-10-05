/***************************************************************************
*
*  M�dulo de implementa��o: <abrevia��o>  <estrutura manipulada pelo m�dulo>
*
*  Arquivo gerado:              <nome-do-arquivo>.c
*  Letras identificadoras:      <abrevia��o>
*
*	Autores:
*     - <nick>: <nome>
*     - <nick>: <nome>
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data        Observa��es
*     1       <nick>   <data>      <observa��es>
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "lista.h"

#define GRAFO_OWN
#include "grafo.h"
#undef GRAFO_OWN

/***********************************************************************
*  Tipo de dados: GRA Vertice do grafo
***********************************************************************/

typedef struct stVerticeGrafo {

	char *nome;
	/* Nome do v�rtice */

	LIS_tppLista pSucessores;
	/* Ponteiros para as arestas originadas neste v�rtice */

	LIS_tppLista pAntecessores;
	/* Ponteiro para os v�rtices que t�m arestas 
	direcionadas para este v�rtice */

	void (*destruirConteudo)(void *pConteudo);
	/* L�gica respons�vel por destruir o valor do v�rtice do grafo */

	void * pValor;
	/* valor contido no v�rtice */

} tpVertice;

/***********************************************************************
*  Tipo de dados: GRA Aresta do grafo
***********************************************************************/

typedef struct stArestaGrafo {

	char *nome;
	/* Nome da aresta */

	tpVertice * pVertice;
	/* Ponteiro para o v�rtice destino da aresta */

} tpAresta;


/***********************************************************************
*  Tipo de dados: GRA Grafo
***********************************************************************/

typedef struct stGrafo {

	LIS_tppLista pOrigens;
	/* V�rtices que s�o origens do grafo */

	LIS_tppLista pVertices;
	/* Todos os v�rtices do grafo */

	tpVertice * pCorrente;
	/* V�rtice corrente */

	void (*destruirConteudo)(void *pConteudo);
	/* L�gica respons�vel por destruir o valor do v�rtice do grafo */

} tpGrafo;


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static void NaoFazNada(void *pVazio);
static void DestruirVertice(void *pVazio);
static void DestruirAresta(void *pVazio);
static int CompararVerticeENome (void *pVazio1, void *pVazio2);
static int CompararArestaENome (void *pVazio1, void *pVazio2);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

GRA_tpCondRet GRA_CriarGrafo(GRA_tppGrafo *ppGrafo,
	void (*destruirConteudo)(void *pConteudo))
{
	tpGrafo *pGrafo = (tpGrafo *) malloc(sizeof(tpGrafo));

	pGrafo->pCorrente = NULL;
	pGrafo->destruirConteudo = destruirConteudo;

	LIS_CriarLista(&pGrafo->pOrigens, NaoFazNada, CompararVerticeENome);
	LIS_CriarLista(&pGrafo->pVertices, DestruirVertice, CompararVerticeENome);

	*ppGrafo = (GRA_tppGrafo) pGrafo;

	return GRA_CondRetOK;
}


GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo *ppGrafo)
{
	tpGrafo *pGrafo = (tpGrafo*) *ppGrafo;

	if (pGrafo == NULL)
	{
		return GRA_CondRetOK;
	}
	LIS_DestruirLista(pGrafo->pVertices);
	LIS_DestruirLista(pGrafo->pOrigens);
	free(pGrafo);


	return GRA_CondRetOK;
}


GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafoParm, char *pNomeVertice, void *pValor)
{
	tpGrafo *pGrafo = (tpGrafo*) pGrafoParm;
	tpVertice *pVertice;

	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoNaoFoiCriado;
	}

	pVertice = (tpVertice*) malloc(sizeof(tpVertice));
	if (pVertice == NULL)
	{
		return GRA_CondRetFaltouMemoria;
	}

	pVertice->nome = pNomeVertice;
	pVertice->pValor = pValor;
	pVertice->destruirConteudo = pGrafo->destruirConteudo;

	LIS_CriarLista(&pVertice->pAntecessores, NaoFazNada, CompararVerticeENome);
	LIS_CriarLista(&pVertice->pSucessores, DestruirAresta, CompararArestaENome);

	pGrafo->pCorrente = pVertice;
	LIS_InserirElementoApos(pGrafo->pVertices, pVertice);

	return GRA_CondRetOK;
}



GRA_tpCondRet GRA_InserirArestaDoCorrentePara(GRA_tppGrafo pGrafoParm,
	char *nomeAresta, char *nomeVerticeDestino)
{
	tpGrafo *pGrafo = (tpGrafo*) pGrafoParm;
	tpAresta *pAresta;
	LIS_tpCondRet lisCondRet;

	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoNaoFoiCriado;
	}

	pAresta = (tpAresta*) malloc(sizeof(tpAresta));
	if (pAresta == NULL)
	{
		return GRA_CondRetFaltouMemoria;
	}

	LIS_IrInicioLista(pGrafo->pVertices);
	lisCondRet = LIS_ProcurarValor(pGrafo->pVertices, nomeVerticeDestino);
	if (lisCondRet == LIS_CondRetFaltouMemoria)
	{
		return GRA_CondRetFaltouMemoria;
	}
	else
	{
		void * pVazio;
		LIS_ObterValor(pGrafo->pVertices, &pVazio);
		pAresta->pVertice = (tpVertice*) pVazio;
		lisCondRet = LIS_InserirElementoApos(pAresta->pVertice->pAntecessores, pGrafo->pCorrente);
		if (lisCondRet == LIS_CondRetFaltouMemoria)
		{
			return GRA_CondRetFaltouMemoria;
		}
	}

	lisCondRet = LIS_InserirElementoApos(pGrafo->pCorrente->pSucessores, pAresta);
	if (lisCondRet == LIS_CondRetFaltouMemoria)
	{
		return GRA_CondRetFaltouMemoria;
	}

	pAresta->nome = nomeAresta;

	return GRA_CondRetOK;
}



GRA_tpCondRet GRA_ObterConteudoCorrente(GRA_tppGrafo pGrafoParm, void **ppValor)
{
	tpGrafo *pGrafo = (tpGrafo*) pGrafoParm;

	if (pGrafo == NULL)
	{
		*ppValor = NULL;
		return GRA_CondRetGrafoNaoFoiCriado;
	}

	if (pGrafo->pCorrente == NULL)
	{
		*ppValor = NULL;
		return GRA_CondRetGrafoVazio; 
	}

	*ppValor = pGrafo->pCorrente->pValor;
	return GRA_CondRetOK;
}



GRA_tpCondRet GRA_AlterarConteudoCorrente(GRA_tppGrafo pGrafoParm, void *pValor)
{
	tpGrafo *pGrafo = (tpGrafo*) pGrafoParm;

	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoNaoFoiCriado;
	}

	if (pGrafo->pCorrente == NULL)
	{
		return GRA_CondRetGrafoVazio;
	}

	pGrafo->pCorrente->pValor = pValor;
	return GRA_CondRetOK;
}



GRA_tpCondRet GRA_TornarCorrenteUmaOrigem(GRA_tppGrafo pGrafoParm)
{
	tpGrafo *pGrafo = (tpGrafo*) pGrafoParm;

	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoNaoFoiCriado;
	}

	if (pGrafo->pCorrente == NULL)
	{
		return GRA_CondRetGrafoVazio;
	}

	LIS_InserirElementoApos(pGrafo->pOrigens, pGrafo->pCorrente);
	return GRA_CondRetOK;
}



GRA_tpCondRet GRA_DestruirVerticeCorrente(GRA_tppGrafo pGrafoParm)
{
	tpGrafo *pGrafo = (tpGrafo*) pGrafoParm;
	return GRA_CondRetGrafoVazio;
}



GRA_tpCondRet GRA_DestruirArestaAdjacente(GRA_tppGrafo pGrafoParm, char *pNomeAresta)
{
	tpGrafo *pGrafo = (tpGrafo*) pGrafoParm;
	return GRA_CondRetGrafoVazio;
}



GRA_tpCondRet GRA_IrParaVerticeAdjacente(GRA_tppGrafo pGrafoParm, char *nomeDaAresta)
{
	tpGrafo *pGrafo = (tpGrafo*) pGrafoParm;
	return GRA_CondRetGrafoVazio;
}



GRA_tpCondRet GRA_SeguirPelaAresta(GRA_tppGrafo pGrafoParm, char *nomeAresta)
{
	tpGrafo *pGrafo = NULL;
	tpAresta *pAresta = NULL;
	LIS_tpCondRet lisCondRet;

	if(pGrafoParm == NULL)
	{
		return GRA_CondRetGrafoNaoFoiCriado;
	}

	pGrafo = (tpGrafo*) pGrafoParm;

	if(pGrafo->pCorrente == NULL)
	{
		return GRA_CondRetGrafoVazio;
	}

	LIS_IrInicioLista(pGrafo->pCorrente->pSucessores);

	lisCondRet = LIS_ProcurarValor(pGrafo->pCorrente->pSucessores, nomeAresta);

	if(lisCondRet != LIS_CondRetOK)
	{
		return GRA_CondRetNaoAchou;
	}

	LIS_ObterValor(pGrafo->pCorrente->pSucessores, (void**)&pAresta);

	pGrafo->pCorrente = pAresta->pVertice;

	return GRA_CondRetOK;
}



GRA_tpCondRet GRA_IrParaAOrigem(GRA_tppGrafo pGrafoParm, char *nomeVertice)
{
	tpGrafo *pGrafo = (tpGrafo*) pGrafoParm;
	return GRA_CondRetGrafoVazio;
}


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  Fun��o: <abreviacao> <nome da funcao por extenso>
*
*  Descri��o:
*    <descri��o da fun��o>
*
***********************************************************************/

void DestruirVertice(void *pVazio)
{
	tpVertice *pVertice = (tpVertice*) pVazio;

	LIS_DestruirLista(pVertice->pAntecessores);
	LIS_DestruirLista(pVertice->pSucessores);

	pVertice->destruirConteudo(pVertice->pValor);
	free(pVertice->nome);
	free(pVertice);
}

void DestruirAresta(void *pVazio)
{
	tpAresta *pAresta = (tpAresta*) pVazio;

	free(pAresta->nome);
	free(pAresta);
}

// A lista de origens n�o deve destruir os vertices, pois
// estes j� ser�o destruidos na pela lista de vertices mesmo
// Provavelmente ser� melhor preparar o m�dulo lista para receber NULL
void NaoFazNada(void *pVazio) {}

// usado para fazer a busca na lista de vertices
int CompararVerticeENome( void *pVazio1, void *pVazio2 )
{
	tpVertice *pVertice1 = (tpVertice*) pVazio1;
	char *nomeBuscado = (char*) pVazio2;

	return strcmp(pVertice1->nome, nomeBuscado);
}

// usado para fazer a busca na lista de arestas
int CompararArestaENome( void *pVazio1, void *pVazio2 )
{
	tpAresta *pAresta1 = (tpAresta*) pVazio1;
	char *nomeBuscado = (char*) pVazio2;

	return strcmp(pAresta1->nome, nomeBuscado);
}

/********** Fim do m�dulo de implementa��o: GRA Grafo direcionado **********/