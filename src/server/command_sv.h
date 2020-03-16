#include "define.h";

//DEFINE COMANDOS REFERENTES AO SERVIDOR (TERMINAL)

char sv_shutdown(SOCKET client_sock)
{
     printf("\n\t<CLIENT>Solicitou O COMANDO SV_SHUTDOWN");
     
     char mensagem[DEFAULT_BUFFLEN] = "SV_SHUTDOWN_OK";        
     send(client_sock, mensagem, DEFAULT_BUFFLEN, 0);       
          
     printf("\n\n\tSERVIDOR DESLIGANDO-SE EM 5 SEGUNDOS...");
     Sleep(1000);
     printf("\n\tSERVIDOR DESLIGANDO-SE EM 4 SEGUNDOS...");
     Sleep(1000);
     printf("\n\tSERVIDOR DESLIGANDO-SE EM 3 SEGUNDOS...");
     Sleep(1000);
     printf("\n\tSERVIDOR DESLIGANDO-SE EM 2 SEGUNDOS...");
     Sleep(1000);
     printf("\n\tSERVIDOR DESLIGANDO-SE EM 1 SEGUNDOS...");
     Sleep(1000);
   
     exit(0);
}

char sv_ip(char client_sock, char paran [][PARAM_MAX_LEN])
{
     
     char mensagem[DEFAULT_BUFFLEN] = "null";
     printf("\n\t<CLIENT>Solicitou O COMANDO SV_IP");
     
     if(strcmp(paran[0], "") == 0)
     {
        strcpy(mensagem, SERVER_IP);
     }
     else
     {
        if(strcmp(paran[0], "P") == 0)
        {                        
           char buf[5];               
                                    
           strcpy(mensagem, SERVER_IP);
           strcat(mensagem, ":");
           strcat(mensagem, _itoa(SERVER_PORT, buf, 10));
        }

     }
     
     send(client_sock, mensagem, DEFAULT_BUFFLEN, 0); 
}
