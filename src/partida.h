#if ! defined( PARTIDA_ )
#define PARTIDA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo matriz
*
*  Arquivo gerado:              PARTIDA.H
*  Letras identificadoras:      TAB
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor     Data     Observa��es
*       1.00   hg e nf  15/09/2013 Adapta��o do m�dulo para manipular matrizes
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
*     explorar matrizes.
*     A matriz possui uma cabe�a que cont�m uma refer�ncia para a ra�z da
*     matriz e outra para um n� corrente da matriz.
*     O modulo permite a manipula��o de m�ltiplas matrizes, por�m as fun��es
*     s� manipulam uma matriz de cada vez.
*     Ao iniciar a execu��o do programa n�o existe matriz.
*     A matriz poder� estar vazia. Neste caso a origem e o n� corrente
*     ser�o nulos, embora a cabe�a esteja definida.
*     O n� corrente ser� nulo se e somente se a matriz estiver vazia.
*
***************************************************************************/
 
#if defined( PARTIDA_OWN )
   #define PARTIDA_EXT
#else
   #define PARTIDA_EXT extern
#endif

#include "lista.h"
#include "direcao.h"
#include "tabuleiro.h"

typedef struct PAR_stPartida* PAR_tppPartida;

typedef enum {
   ANDA = 0,
   VOA = 1
} PAR_tpTipoMovimento;


typedef enum {
   ALIADA = 0,
   INIMIGA = 1
} PAR_tpTimePeca;

typedef struct PAR_stPasso
{
   DIR_tpDirecao direcao;
   int quantidade;
} PAR_tpPasso;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         PAR_CondRetOK = 0 ,
               /* Executou correto */

         PAR_CondRetNaoCriouOrigem = 1 ,
               /* N�o criou n� origem */

         PAR_CondRetNaoEhNo = 2 ,
               /* N�o � n� na dire��o desejada */

         PAR_CondRetMatrizNaoExiste = 3 ,
               /* Matriz n�o existe */

         PAR_CondRetNaoTemCorrente = 4 ,
               /* Matriz est� vazia */

         PAR_CondRetFaltouMemoria = 5 ,
               /* Faltou mem�ria ao alocar dados */
         PAR_CondRetPecaNaoEncontrada = 6

   } PAR_tpCondRet ;


   PAR_tpCondRet PAR_CriarPartida(PAR_tppPartida *ppPartida);

   //PAR_tpCondRet PAR_AlgumaPegadaInimiga(PAR_tpPartida *pPartida, int *pResposta);
   //
   //PAR_tpCondRet PAR_InserirRei(PAR_tpPartida *pPartida);
   //
   //PAR_tpCondRet PAR_RemoverRei(PAR_tpPartida *pPartida);
   //
   //PAR_tpCondRet PAR_IrCasaRei(PAR_tpPartida *pPartida);
   //
   //PAR_tpCondRet PAR_EhCheckmate(PAR_tpPartida *pPartida, int *pResposta);
   //
   //PAR_tpCondRet PAR_CriarPegadas(PAR_tpPartida *pPartida);

/***********************************************************************
*
*  $FC Fun��o: TAB Destruir matriz
*
*  $ED Descri��o da fun��o
*     Destr�i o corpo e a cabe�a da matriz, anulando a matriz corrente.
*     Faz nada caso a matriz corrente n�o exista.
*
*  $EP Par�metros
*     $P ppPartida - � o ponteiro para a matriz que ser� destruida.
*                    Este par�metro � passado por refer�ncia.
*
*  $FV Valor retornado
*     PAR_CondRetOK
*     PAR_CondRetMatrizNaoExiste
*
***********************************************************************/
   PAR_tpCondRet PAR_DestruirPartida(PAR_tppPartida *ppPartida);


   PAR_tpCondRet PAR_IrCasa(PAR_tppPartida pPartida, char *nomeCasa);
   
   //PAR_tpCondRet PAR_CriarPeca(PAR_tpPartida *pPartida, char *nome,
   //   LIS_tppLista pPassos, PAR_tpTipoMovimento tipoMovimento);
   //
   //PAR_tpCondRet PAR_AlterarPeca(PAR_tpPartida *pPartida, char *nomeAtual, char* nomeNovo,
   //   LIS_tppLista pNovosPassos, PAR_tpTipoMovimento novoTipoMovimento);
   //
   //PAR_tpCondRet PAR_InserirPeca(PAR_tpPartida *pPartida, char *nome, PAR_tpTimePeca time);
   //
   //PAR_tpCondRet PAR_RemoverPeca(PAR_tpPartida *pPartida);



#undef PARTIDA_EXT

/********** Fim do m�dulo de defini��o: M�dulo matriz **********/

#else
#endif
