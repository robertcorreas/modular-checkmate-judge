/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTTAB.C
*  Letras identificadoras:      TTAB
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor     Data     Observa��es
*       1.00   hg e nf  15/09/2013 Adapta��o do m�dulo para manipular matrizes
*
*  $ED Descri��o do m�dulo
*     Este m�odulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo matriz. Ilustra como redigir um interpretador de comandos
*     de teste espec�ficos utilizando o arcabou�o de teste para C.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo matriz:
*
*
*     "=criar"           - chama a fun��o TAB_CriarMatriz( )
*     "=irPara"         - chama a fun��o TAB_IrPara( )
*     "=atribuir" <Char> - chama a fun��o TAB_AtribuirValorCorr(  )
*     "=destroi"         - chama a fun��o TAB_DestruirMatriz( )
*     "=obter" <Char>    - chama a fun��o TAB_ObterValorCorr( ) e compara
*                          o valor retornado com o valor <Char>
*=alterarPeca  nomeAtual   novoNome   novosPassos   novoTipoMovimento   condRet
*
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>

#include    "TST_ESPC.H"
#include    "lista.h"

#include    "generico.h"
#include    "lerparm.h"

#include    "tabuleiro.h"
#include    "mem_manager.h"
#include    "input_string_parser.h"

/* Tabela dos nomes dos comandos de teste relacionados ao m�dulo */

#define     CRIAR_TAB_CMD       "=criar"
#define     OBTER_VAL_CMD       "=obter"
#define     ATRIBUIR_VAL_CMD    "=atribuir"
#define     DESTROI_CMD         "=destruir"

#define     COPIAR_TAB_CMD     "=copiarTabuleiro"
#define     IR_PARA_CMD        "=irPara"
#define     IR_CASA_CMD        "=ircasa"
#define     CRIAR_PECA_CMD     "=criarPeca"
#define     ALTERAR_PECA_CMD   "=alterarPeca"
#define     INSERIR_PECA_CMD   "=inserirPeca"
#define     REMOVER_PECA_CMD   "=removerPeca"
#define     INSERIR_REI_CMD    "=inserirRei"
#define     REMOVER_REI_CMD    "=removerRei"
#define     IR_REI_CMD         "=ircasarei"
#define     PEGADA_INIMIGA_CMD "=pegadaInimiga?"
#define     EH_CHECKMATE_CMD "=ehCheckmate?"

#define     FIM_CMD         "=fim"

/* Tabela dos nomes dos comandos de teste espec�ficos do teste */
#define     VALIDAR_EST_TAB_CMD "=validarEstrutura"
#define     SELECIONAR_CMD       "=selecionar"


#define     VALORES_SIZE     9
#define     TABULEIROES_SIZE 10
#define     MAX_PASSOS_STR   50
#define     MAX_NOME_PECA    30
/*****  C�digo das fun��es exportadas pelo m�dulo  *****/
int IndiceDoValor( LIS_tppLista Valor );
void PreencherArrayDeValores();

static TAB_tpMatriz * Matrizes[TABULEIROES_SIZE] ;
static LIS_tppLista VALORES[VALORES_SIZE] ;

static int iMat = 0 ;

/***********************************************************************
*
*  $FC Fun��o: TTAB Efetuar opera��es de teste espec�ficas para matriz
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     matriz sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      TAB_tpCondRet CondRetObtido   = TAB_CondRetOK ;
      TAB_tpCondRet CondRetEsperada = TAB_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      int IndiceValorEsperado = -1;
	  int IndiceValorObtido = -1;
	  int IndiceValorDado = -1;
	  
	  LIS_tppLista ValorObtido = NULL;

	  int Linhas = 0 ;
	  int Colunas = 0 ;

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;


	  PreencherArrayDeValores();

      /* Testar TAB Criar matriz */

         if ( strcmp( ComandoTeste , CRIAR_TAB_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = TAB_CriarTabuleiro( Matrizes + iMat ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar matriz." ) ;

         }


      /* Testar TAB Destruir matriz */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = TAB_DestruirMatriz( Matrizes + iMat ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o � poss�vel destruir uma matriz que n�o existe.") ;

         } /* fim ativa: Testar TAB Destruir matriz */

		 
      /* Testar TAB Ir para */

		 else if ( strcmp( ComandoTeste , IR_PARA_CMD ) == 0 )
         {
            int iDirecao;
			   NumLidos = LER_LerParametros("ii" , &iDirecao, &CondRetEsperada);
            if (NumLidos != 2)
            {
               return TST_CondRetParm ;
            }

			   CondRetObtido = TAB_IrPara(Matrizes[iMat], (TAB_tpDirecao) iDirecao);

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para essa direcao.") ;

         }


		/* Testar TAB Ir casa */

		 else if ( strcmp( ComandoTeste , IR_CASA_CMD ) == 0 )
       {

         char *nome;
         MEM_Alloc(sizeof(char)*3, (void**) &nome);

			NumLidos = LER_LerParametros( "si", nome, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            }

			CondRetObtido = TAB_IrCasa(Matrizes[iMat], nome) ;

         return TST_CompararInt( CondRetEsperada , CondRetObtido ,
								"N�o foi poss�vel ir para a casa.") ;

         }


		/* Testar TAB Ir casa rei */

		 else if (strcmp(ComandoTeste, IR_REI_CMD) == 0)
       {
           NumLidos = LER_LerParametros("i", &CondRetEsperada);
           if (NumLidos != 1)
           {
              return TST_CondRetParm ;
           }
           
           CondRetObtido = TAB_IrCasaRei(Matrizes[iMat]) ;
           
           return TST_CompararInt( CondRetEsperada , CondRetObtido ,
               "N�o foi poss�vel ir para a casa do rei.") ;

       }


		/* Testar TAB Criar peca*/

		 else if ( strcmp( ComandoTeste , CRIAR_PECA_CMD ) == 0 )
       {

         char *nome, *passosStr;
         int iTipoMovimento;
         TAB_tpTipoMovimento tipo;
         LIS_tppLista pPassos;
         MEM_Alloc(sizeof(char)*MAX_NOME_PECA, (void**) &nome);
         MEM_Alloc(sizeof(char)*MAX_PASSOS_STR, (void**) &passosStr);

			NumLidos = LER_LerParametros("ssii", nome, passosStr, &iTipoMovimento, &CondRetEsperada) ;
         if (NumLidos != 4)
         {
            return TST_CondRetParm ;
         }

         ISP_LerPassos(passosStr, &pPassos);

         tipo = (TAB_tpTipoMovimento) iTipoMovimento;
			CondRetObtido = TAB_CriarPeca(Matrizes[iMat], nome, pPassos, tipo);

         return TST_CompararInt(CondRetEsperada, CondRetObtido,
								"N�o foi poss�vel criar a casa.");

       }

       /* Testar TAB Alterar peca*/

       else if ( strcmp( ComandoTeste , ALTERAR_PECA_CMD ) == 0 )
       {

          char *nomeAtual, *passosStr, *novoNome;
          int iTipoMovimento;
          TAB_tpTipoMovimento tipo;
          LIS_tppLista pPassos;
          MEM_Alloc(sizeof(char)*MAX_NOME_PECA, (void**) &nomeAtual);
          MEM_Alloc(sizeof(char)*MAX_NOME_PECA, (void**) &novoNome);
          MEM_Alloc(sizeof(char)*MAX_PASSOS_STR, (void**) &passosStr);

          NumLidos = LER_LerParametros("sssii", nomeAtual, novoNome, passosStr, &iTipoMovimento, &CondRetEsperada) ;
          if (NumLidos != 5)
          {
             return TST_CondRetParm ;
          }

          ISP_LerPassos(passosStr, &pPassos);

          tipo = (TAB_tpTipoMovimento) iTipoMovimento;
          CondRetObtido = TAB_AlterarPeca(Matrizes[iMat], nomeAtual, novoNome, pPassos, tipo);

          return TST_CompararInt(CondRetEsperada, CondRetObtido,
             "N�o foi poss�vel criar a casa.");

       }


       
		/* Testar TAB Inserir peca*/

		 else if (strcmp( ComandoTeste, INSERIR_PECA_CMD) == 0 )
       {
         char *nome;
         int iTime;
         TAB_tpTimePeca time;
         LIS_tppLista pPassos;
         MEM_Alloc(sizeof(char)*MAX_NOME_PECA, (void**) &nome);

			NumLidos = LER_LerParametros("sii", nome, &iTime, &CondRetEsperada) ;
         if (NumLidos != 3)
         {
            return TST_CondRetParm ;
         }

         time = (TAB_tpTimePeca) iTime;
         CondRetObtido = TAB_InserirPeca(Matrizes[iMat], nome, time);

         return TST_CompararInt(CondRetEsperada, CondRetObtido,
								"N�o foi poss�vel inserir a pe�a.");

       }
       
       
		/* Testar TAB Remover peca*/

		 else if (strcmp( ComandoTeste, REMOVER_PECA_CMD) == 0 )
       {
			NumLidos = LER_LerParametros("i", &CondRetEsperada) ;
         if (NumLidos != 1)
         {
            return TST_CondRetParm ;
         }

         CondRetObtido = TAB_RemoverPeca(Matrizes[iMat]);

         return TST_CompararInt(CondRetEsperada, CondRetObtido,
								"N�o foi poss�vel remover a pe�a.");

       }
       
       
		/* Testar TAB Remover rei*/

		 else if (strcmp( ComandoTeste, REMOVER_REI_CMD) == 0 )
       {
			NumLidos = LER_LerParametros("i", &CondRetEsperada) ;
         if (NumLidos != 1)
         {
            return TST_CondRetParm ;
         }

         CondRetObtido = TAB_RemoverRei(Matrizes[iMat]);

         return TST_CompararInt(CondRetEsperada, CondRetObtido,
								"N�o foi poss�vel remover o rei.");

       }
       
       
		/* Testar TAB Copiar tabuleiro */

		 else if (strcmp( ComandoTeste, COPIAR_TAB_CMD) == 0 )
       {
          int iCopia;
			 NumLidos = LER_LerParametros("ii", &iCopia, &CondRetEsperada) ;
          if (NumLidos != 2)
          {
             return TST_CondRetParm ;
          }
          
          CondRetObtido = TAB_CopiarTabuleiro(Matrizes[iMat], &Matrizes[iCopia]);
          
          return TST_CompararInt(CondRetEsperada, CondRetObtido,
								"N�o foi poss�vel copiar o tabuleiro.");

       }
       

		/* Testar TAB Inserir rei */

		 else if (strcmp( ComandoTeste, INSERIR_REI_CMD) == 0 )
       {
			 NumLidos = LER_LerParametros("i", &CondRetEsperada) ;
          
          if (NumLidos != 1)
          {
             return TST_CondRetParm ;
          }
          
          CondRetObtido = TAB_InserirRei(Matrizes[iMat]);
          
          return TST_CompararInt(CondRetEsperada, CondRetObtido,
								"N�o foi poss�vel inserir o rei.");

       }


		/* Testar TAB Alguma pegada inimiga*/

		 else if (strcmp( ComandoTeste, PEGADA_INIMIGA_CMD) == 0 )
       {
          int respostaEsperada, respostaObtida;
          TST_tpCondRet condRet;
			 NumLidos = LER_LerParametros("ii", &respostaEsperada, &CondRetEsperada) ;
          
          if (NumLidos != 2)
          {
             return TST_CondRetParm ;
          }
          
          CondRetObtido = TAB_AlgumaPegadaInimiga(Matrizes[iMat], &respostaObtida);
          
          condRet = TST_CompararInt(CondRetEsperada, CondRetObtido,
                     "N�o foi poss�vel verificar se existe alguma pegada inimiga.");

          if (condRet != TST_CondRetOK)
          {
             return condRet;
          }

          return TST_CompararInt(respostaEsperada, respostaObtida,
                     "Foi obtida uma resposta diferente da esperada");

       }
       

		/* Testar TAB Eh checkmate*/

		 else if (strcmp( ComandoTeste, EH_CHECKMATE_CMD) == 0 )
       {
          int respostaEsperada, respostaObtida;
          TST_tpCondRet condRet;
			 NumLidos = LER_LerParametros("ii", &respostaEsperada, &CondRetEsperada) ;
          
          if (NumLidos != 2)
          {
             return TST_CondRetParm ;
          }
          
          CondRetObtido = TAB_EhCheckmate(Matrizes[iMat], &respostaObtida);
          
          condRet = TST_CompararInt(CondRetEsperada, CondRetObtido,
                     "N�o foi poss�vel verificar se eh checkmate.");

          if (condRet != TST_CondRetOK)
          {
             return condRet;
          }

          return TST_CompararInt(respostaEsperada, respostaObtida,
                     "Foi obtida uma resposta diferente da esperada para a verifica��o de checkmate");

       }



      /* Testar Selecionar indice na array de matrizes */

         else if ( strcmp( ComandoTeste , SELECIONAR_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" ,
                               &iMat ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			if ( iMat < 0 || iMat > TABULEIROES_SIZE - 1 )
			{
				TST_NotificarFalha("S� � poss�vel fazer sele��o nos indices de 0 � 9") ;
				return TST_CondRetErro ;
			} /* if */

			return TST_CondRetOK ;

         }


      /* Testar Finalizar teste */

         else if ( strcmp( ComandoTeste , FIM_CMD ) == 0 )
         {
            MEM_LiberarTodaMemoriaAlocada();
            return TST_CondRetOK;
         }

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TTAB Efetuar opera��es de teste espec�ficas para matriz */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/

int IndiceDoValor( LIS_tppLista Valor )
{
	int i;

	if ( Valor == NULL )
	{
		return -1;
	}

	for ( i = 0 ; i < VALORES_SIZE ; i++ )
	{
		if ( VALORES[i] == Valor )
		{
			return i;
		}
	}

	return -1;
}

void PreencherArrayDeValores()
{
	int i;

	if ( VALORES[0] != NULL )
	{
		return;
	}

	for ( i = 0 ; i < VALORES_SIZE ; i++ )
	{
		LIS_CriarLista( &VALORES[i], NULL, NULL );
	}
}