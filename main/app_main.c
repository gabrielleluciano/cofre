//////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                       _              //
//               _    _       _      _        _     _   _   _    _   _   _        _   _  _   _          //
//           |  | |  |_| |\| |_| |\ |_|   |\ |_|   |_| |_| | |  |   |_| |_| |\/| |_| |  |_| | |   /|    //    
//         |_|  |_|  |\  | | | | |/ | |   |/ | |   |   |\  |_|  |_| |\  | | |  | | | |_ | | |_|   _|_   //
//                                                                                       /              //
//////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
*   Programa básico para controle da placa durante a Jornada da Programação 1
*   Permite o controle das entradas e saídas digitais, entradas analógicas, display LCD e teclado. 
*   Cada biblioteca pode ser consultada na respectiva pasta em componentes
*   Existem algumas imagens e outros documentos na pasta Recursos
*   O código principal pode ser escrito a partir da linha 86
*/

// Área de inclusão das bibliotecas
//-----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "ioplaca.h"   // Controles das Entradas e Saídas digitais e do teclado
#include "lcdvia595.h" // Controles do Display LCD
#include "driver/adc.h"
#include "hcf_adc.h"   // Controles do ADC
#include "MP_hcf.h"   // Controles do ADC

// Área das macros
//-----------------------------------------------------------------------------------------------------------------------
int controle = 0;
int senha = 0;
int digito = 0;
int coluna = 0;
int interrompe = 0;
int resultado = 0;
int operador = 0;
char tecla = 0;
char mostra[40];
int senha;
int contagem;
int seguranca = 0;
int num1 = 0;
int seha = 1501;
// Área de declaração de variáveis e protótipos de funções
//-----------------------------------------------------------------------------------------------------------------------

static const char *TAG = "Placa";
static uint8_t entradas, saidas = 0; //variáveis de controle de entradas e saídas
uint32_t adc;
uint32_t valor = 0;

// Funções e ramos auxiliares
//-----------------------------------------------------------------------------------------------------------------------
void abrir()
{
  lcd595_write (1, 0, "abrindo Cofre");
  for (int i = 0; i < 1800; i = valor)
  {
    hcf_adc_ler(&valor);
    rotacionar_DRV (1, 10, saidas);
    seguranca ++;
    if (seguranca > 15)break;
  }
  seguranca = 0;
}

  void fechar()
  {
  lcd595_write (1, 0, "fechando cofre");
  hcf_adc_ler (&valor);
  for (int i = valor; i > 366 ; i = valor)
  {
     
    hcf_adc_ler(&valor);
    rotacionar_DRV (0, 10, saidas);
    seguranca ++;
    if (seguranca > 15)break;
    lcd595_clear ();
    digito = 0;
  
     
  }
  seguranca = 0; 
}
// Programa Principal
//-----------------------------------------------------------------------------------------------------------------------

void app_main(void)
{
    /////////////////////////////////////////////////////////////////////////////////////   Programa principal


    // a seguir, apenas informações de console, aquelas notas verdes no início da execução
    ESP_LOGI(TAG, "Iniciando...");
    ESP_LOGI(TAG, "Versão do IDF: %s", esp_get_idf_version());

    /////////////////////////////////////////////////////////////////////////////////////   Inicializações de periféricos (manter assim)
    
    // inicializar os IOs e teclado da placa
    ioinit();      
    entradas = io_le_escreve(saidas); // Limpa as saídas e lê o estado das entradas

    // inicializar o display LCD 
    lcd595_init();
    lcd595_write(1,1,"   cofre Gabi  ");
    
    
    // Inicializar o componente de leitura de entrada analógica
    esp_err_t init_result = hcf_adc_iniciar();
    if (init_result != ESP_OK) {
        ESP_LOGE("MAIN", "Erro ao inicializar o componente ADC personalizado");
    }

    //delay inicial
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
    lcd595_clear();
    /////////////////////////////////////////////////////////////////////////////////////   Periféricos inicializados

    DRV_init(6,7);
    
    lcd595_write(1,1, "Digite a Senha" );
    lcd595_write(2,1,"[] [] [] []");  
       
    /////////////////////////////////////////////////////////////////////////////////////   Início do ramo principal                    
    while (1)                                                                                                                         
    {                                                                                                                                 
        //_______________________________________________________________________________________________________________________________________________________ //
        //-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - -  -  -  -  -  -  -  -  -  -  Escreva seu código aqui!!! //

           

         entradas = io_le_escreve(saidas);
         hcf_adc_ler(&valor);//ler o valor adc
          
         
       // sprintf(mostra, "%"PRIu32"",valor);
       // lcd595_write(1,1, mostra);


         tecla = le_teclado(); //função para ler o teclado 
        
        if (tecla>='0' && tecla <='9')//
        {
        {num1 = num1 * 10 + tecla -'0';}
      digito = digito + 1;//funçaõ para funcionar os digitos 
        }


       if(digito==1)// mostrar o digito da primeira posição 
       {
       lcd595_write(1,1, "Digite a Senha" );//escreve no display
       lcd595_write(2,1,"[*] [] [] []");//escreve no display
       }
      if(digito==2)//mostrar o digito da segunda posição 
      {
      
       lcd595_write(1,1, "Digite a Senha ");//escreve no display
       lcd595_write(2,1,"[*] [*] [] []");//escreve no display
      }

        if(digito==3)//mostrar o digito da terceira posição 
        {
       
       lcd595_write(1,1, " Digite a Senha" );//escreve no display
       lcd595_write(2,1,"[*] [*] [*] []");//escreve no display
        }
       
        if(digito==4)//mostrar o digito da quarta posição 
        {
      
       lcd595_write(1,1, " Digite a Senha" );//escreve no display
       lcd595_write(2,1,"[*] [*] [*] [*]");//escreve no display
          
          controle ++;//aumento da sequencia, nova funçaõ sendo iniciada 
        }
          

         if (controle == 1)// cofre em funcionamento 
         {
        
         
            if(num1 == 1501)//senha para abrir o cofre
          {
            lcd595_write(1,1, "Senha correta");//senha correta 
              abrir();
              vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
              lcd595_write (1,1, " 10 segundos");//tempo de espera para bloquear cofre 
              vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
              lcd595_write (1,1, "9 segundos");//tempo de espera para bloquear cofre 
              vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
               vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
              lcd595_write (1,1, "8 segundos");//tempo de espera para bloquear cofre 
              vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
               vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
              lcd595_write (1,1, "7 segundos");//tempo de espera para bloquear cofre 
              vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
               vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
              lcd595_write (1,1, "6 segundos");//tempo de espera para bloquear cofre 
              vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
               vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
              lcd595_write (1,1, "5 segundos");//tempo de espera para bloquear cofre 
              vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
               vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
              lcd595_write (1,1, "4 segundos");//tempo de espera para bloquear cofre 
              vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
               vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
              lcd595_write (1,1, "3 segundos");//tempo de espera para bloquear cofre 
              vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
               vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
              lcd595_write (1,1, "2 segundos");//tempo de espera para bloquear cofre 
              vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
               vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
              lcd595_write (1,1, "1 segundos");//tempo de espera para bloquear cofre 
              vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
               vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
              lcd595_write (1,1, " 0 segundos" );//tempo de espera para bloquear cofre 
              vTaskDelay(1000 / portTICK_PERIOD_MS);   
              lcd595_clear ();
              fechar();
              controle = 0;// função esta sendo digitada 
               lcd595_write(1,1, " Digite a Senha " );
                lcd595_write(2,1,"[] [] [] []");  
          } 
         
             else
            {
               lcd595_write(1,1, " Senha incorreta ");// senha incorreta 
               vTaskDelay(1000 / portTICK_PERIOD_MS);   
             lcd595_write(1,1, " Digite a Senha ");
              lcd595_write(2,1," [] [] [] [] ");
               
               controle = 0;
               num1 = 0;
               digito = 0;
            }


         }
           if(le_teclado () == '/')//tecla para abrir
          {
            rotacionar_DRV(1, 10, saidas);
          }


          if(le_teclado () == 'x')// tecla para fechar
          {
            rotacionar_DRV(0, 10, saidas);
       
             }   
    
       }
    
    
        //-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - -  -  -  -  -  -  -  -  -  -  Escreva seu só até aqui!!! //
       //________________________________________________________________________________________________________________________________________________________//
        vTaskDelay(100 / portTICK_PERIOD_MS);    // delay mínimo obrigatório, se retirar, pode causar reset do ESP
    
    
  
   // caso erro no programa, desliga o módulo ADC
    hcf_adc_limpar();

    /////////////////////////////////////////////////////////////////////////////////////   Fim do ramo principal
    
}
 
