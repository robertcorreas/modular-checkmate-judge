/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo matriz
*
*  Arquivo gerado:              MODELO_PECA.C
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
#include "modelo_peca.h"
#include "mem_manager.h"


#define MODELO_PECA_OWN
#include "peca.h"
#undef MODELO_PECA_OWN

typedef struct stMovimento {
   LIS_tppLista passos;
   MPEC_tpTipoMovimento tipo;
} tpMovimento;

typedef struct MPEC_stModeloPeca {
   tpMovimento *pMovimento;
   char *nome;
} tpModeloPeca;

MPEC_tpCondRet MPEC_CriarModeloPeca(MPEC_tppModeloPeca *ppModelo, char* nome, LIS_tppLista pPassos, MPEC_tpTipoMovimento tipoMovimento)
{
   tpModeloPeca *pModeloPeca;
   tpMovimento *pTipoMovimento;
   MEM_Alloc(sizeof(tpModeloPeca),(void**)&pModeloPeca);
   MEM_Alloc(sizeof(tpMovimento),(void**)&pTipoMovimento);

   pTipoMovimento->passos = pPassos;
   pTipoMovimento->tipo = tipoMovimento;

   pModeloPeca->nome = nome;
   pModeloPeca->pMovimento = pTipoMovimento;


   *ppModelo = (MPEC_tppModeloPeca) pModeloPeca;

   return MPEC_CondRetOK;
}


MPEC_tpCondRet MPEC_DestruirModeloPeca(MPEC_tppModeloPeca *ppModelo)
{
   tpModeloPeca* pModelo = (tpModeloPeca*)*ppModelo;
   if (pModelo == NULL)
   {
      return MPEC_CondRetOK;
   }

   MEM_Free(pModelo->nome);
   LIS_DestruirLista(pModelo->pMovimento->passos);
   MEM_Free(pModelo->pMovimento);

   *ppModelo = NULL;

   return MPEC_CondRetOK;

}
// TODO [RCS] - PEC_CondRetNaoAlterou, espera que ISP_LerPassos retorne algo diferente de OK para quando n�o n�o receber argumentos v�lidos
MPEC_tpCondRet MPEC_AlterarModeloPeca(MPEC_tppModeloPeca pModeloParm, char *novoNome, LIS_tppLista pPassos, MPEC_tpTipoMovimento novoTipoMovimento)
{
   LIS_tpCondRet lisCondRet;

   tpModeloPeca *pModelo = (tpModeloPeca*) pModeloParm;
   if (pModelo == NULL)
   {
      return MPEC_CondRetModeloNaoExiste;
   }

   MEM_Free(pModelo->nome);
   pModelo->nome = novoNome;

   lisCondRet = LIS_DestruirLista(pModelo->pMovimento->passos);
   if(lisCondRet != LIS_CondRetOK)
   {
      return MPEC_CondRetNaoAlterou;
   }

   pModelo->pMovimento->passos = pPassos;
   pModelo->pMovimento->tipo = novoTipoMovimento;
   
   return MPEC_CondRetOK;
}

MPEC_tpCondRet MPEC_RecuperarNome(MPEC_tppModeloPeca pModeloParm, char **pNome)
{
   tpModeloPeca *pModelo = (tpModeloPeca*) pModeloParm;

   *pNome = pModelo->nome;

   return MPEC_CondRetOK;
}

/********** Fim do m�dulo de implementa��o: M�dulo matriz **********/