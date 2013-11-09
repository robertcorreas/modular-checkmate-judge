/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo matriz
*
*  Arquivo gerado:              PECA.C
*  Letras identificadoras:      MAT
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor     Data     Observa��es
*       1.00   hg e nf  15/09/2013 Adapta��o do m�dulo para manipular matrizes
*
***************************************************************************/

#include <stdio.h>
#include <string.h>
#include "lista.h"
#include "peca.h"
#include "mem_manager.h"
#include "input_string_parser.h"


typedef struct stMovimento {
   LIS_tppLista passos;
   PEC_tpTipoMovimento tipo;
} PEC_tpMovimento;

typedef struct stModeloPeca {
   PEC_tpMovimento *pMovimento;
   char *nome;
} PEC_tpModeloPeca;

typedef struct stPeca {
   PEC_tpModeloPeca *pModelo;
   PEC_tpTimePeca time;
} PEC_stPeca;

PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca *ppPeca, char* nome, char* passos, PEC_tpTipoMovimento tipoMovimento)
{
   PEC_stPeca *pPeca;
   PEC_tpModeloPeca *pModeloPeca;
   PEC_tpMovimento *pTipoMovimento;
   LIS_tppLista pPassos;
   MEM_Alloc(sizeof(PEC_stPeca),(void**)&pPeca);
   MEM_Alloc(sizeof(PEC_tpModeloPeca),(void**)&pModeloPeca);
   MEM_Alloc(sizeof(PEC_tpMovimento),(void**)&pTipoMovimento);

   ISP_LerPassos(passos,&pPassos);

   pTipoMovimento->passos = pPassos;
   pTipoMovimento->tipo = tipoMovimento;

   pModeloPeca->nome = nome;
   pModeloPeca->pMovimento = pTipoMovimento;

   pPeca->pModelo = pModeloPeca;

   *ppPeca = (PEC_tppPeca)pPeca;

   return PEC_CondRetOK;
}



//TODO [RCS] falta testar
PEC_tpCondRet DestruirPeca(PEC_tppPeca *ppPeca)
{
   PEC_stPeca* pPeca = (PEC_stPeca*)*ppPeca;
   if(pPeca == NULL)
      return PEC_CondRetOK;

   MEM_Free(pPeca);

   return PEC_CondRetOK;

}

#define PECA_OWN
#include "peca.h"
#undef PECA_OWN

/********** Fim do m�dulo de implementa��o: M�dulo matriz **********/