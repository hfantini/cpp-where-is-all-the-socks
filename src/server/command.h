#include "command_list.h" //INCLUI AS LISTAS DE FUNÇÃO;
#include "command_sv.h" //INCLUI O CORPO DAS FUNÇÕES DE SERVIDOR (TERMINAL);
#include "command_os.h" //INCLUDE O CORPO DAS FUNÇÕES DE SISTEMA OPERACIONAL


//DEFINES
#define COMMAND_MAX_LEN 20
#define PARAM_MAX_LEN 100

//BIBLIOTECA PARA A INTERPRETAÇÃO DE COMANDOS DO CLIENTE

char executeCommand(char command[COMMAND_MAX_LEN], char parametro[][PARAM_MAX_LEN], SOCKET client_sock) //FUNÇÃO QUE RECEBE A MENSAGEM INTERPRETADA E EXECUTA A FUNÇÃO SE EXISTIR
{     
     int cont = 0;
     
     for( cont ; cont < MAX_FUNC_LIST ; cont ++ )
     {
          if( strcmp(command, func_list[cont] ) == 0 )
          {

               switch(cont)
               {
                    //SV FUNCTIONS       
                           
                    case 0: //SV_SHUTDOWN
                         sv_shutdown(client_sock);
                         break;
                         
                    case 1: //SV_IP
                         sv_ip(client_sock,parametro);
                         break;
                      
                    case 20: //OS_MESSAGE
                         os_message(client_sock,parametro);
                         break;   
                         
                    case 21: //OS_USERNAME
                         os_username(client_sock);
                         break;  
                    
                    case 22: //OS_SHUTDOWN
                         os_shutdown();
                         break;
                    
                    case 23: //OS_HARDWARE      
                         os_hardware(client_sock);
                         break;
               }

          }
     }
}

char readCommand(char mensagem[200], SOCKET client_sock)
{
     char command[COMMAND_MAX_LEN] = ""; //COMMAND É A STRING QUE ARMAZENA UM COMANDO.
     char param[][PARAM_MAX_LEN] = {"","","","","","","","","",""}; //INICIA O ARRAY DE PARAMETROS (até 10 parametros por comando).
     int command_len = strlen(mensagem); //COMMAND_LEN É O NUMERO DE CARACTERES DO COMANDO DIGITADO.
     int param_cont = 0; //PARAN_CONT REPRENSETA O NUMERO DE PARAMETROS TOTAIS LIDOS
     int cont = 0; //CONT REPRESTA O CONTADOR DOS LAÇOS <FOR>
      
     for( cont ; cont < command_len ; cont++ )
     {
          if( mensagem[cont] != '/') //O CHAR '/' REPRESENTA O FIM DO COMANDO. O QUE ESTIVER DEPOIS É IGNORADO
          {
              if( mensagem[cont] != '-') //O CHAR '-' REPRESENTA O FIM DO COMANDO E O INICIO DA LEITURA DE PARAMETROS CASO ELES EXISTAM.
              {
                  if(mensagem[cont] != ' ')
                  {
                       command[cont] = toupper(mensagem[cont]);
                  }
                  
              }
              else //CASO O ELSE SEJA ATIVADO SABEREMOS QUE O COMANDO FOI LIDO E O QUE VEM A SEGUIR SÃO SEUS PARAMETROS
              {
                   cont++;
                   int char_param = cont; //CHAR_PARAN ARMAZENA O ESTADO INICIAL DO CONTADOR DO FOR
                   int char_real; //CHAR_REAL REPRESENTA A SUBTRAÇÃO DE CHAR_PARAN DO CONTADOR PARA INDICE DE ALOCAÇÃO DO VETOR DE PARAMETRO
                   
                   for( cont ; cont < command_len ; cont++ )
                   {
                       if( mensagem[cont] != '/' ) //O CHAR '/' REPRESENTA O FIM DO COMANDO. O QUE ESTIVER DEPOIS É IGNORADO
                       {
                        
                            if( mensagem[cont] != '-') //O CHAR '-' REPRESENTA O FIM DO ATUAL PARAMETRO E O INÍCIO DO PROXIMO.
                            {
                               char_real = cont - char_param; //CALCULO DO INDICE DO VETOR DE PARAMETROS
                               param[param_cont][char_real] = toupper(mensagem[cont]);
                            } 
                            else
                            {
                                param_cont += 1; //NOVO PARAMETRO
                                char_param = cont + 1;
                            }
                       }
                       else
                       {
                           break; 
                       }
                   }
                   
                  break; 
              }
          }
          else
          {
              break;
          }
     }
     
     executeCommand(command, param, client_sock);
}


