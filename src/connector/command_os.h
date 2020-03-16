#include "define.h";

int os_message(SOCKET server_sock, char param[][PARAM_MAX_LEN])
{
     if( (strcmp(param[0], "")) != 0 )
     {
         char command[DEFAULT_BUFFLEN] = "os_message";
         
         strcat(command, " -");
         strcat(command, param[0]);
         
         if( strcmp(param[1], "") != 0 )
         {
             strcat(command, " -");
             strcat(command, param[1]); 
         }
               
         if( send(server_sock, command, DEFAULT_BUFFLEN, 0 ) == SOCKET_ERROR )
         {
            printf("\n\t<CLIENTE>Falha no envio de bytes ao servidor remoto.");
            return 0;
         }
         printf("\n\t<SERVIDOR> Mensagem recebida com sucesso.");
     }
}

int os_username(SOCKET server_socket)
{
         char command[DEFAULT_BUFFLEN] = "os_username";
     
         if( send(server_socket, command, DEFAULT_BUFFLEN, 0 ) == SOCKET_ERROR )
         {
            printf("\n\t<CLIENTE>Falha no envio de bytes ao servidor remoto.");
         }
         else
         {
             char resposta[DEFAULT_BUFFLEN];
             
             if ( recv(server_socket, resposta, DEFAULT_BUFFLEN, 0) == SOCKET_ERROR)
             {
                printf("\n\t<CLIENTE>O servidor remoto não respondeu o comando. Erro: %s", WSAGetLastError());
                return 0;                                  
             }
             printf("\t%s\n", resposta);
         }
}

int os_shutdown(SOCKET server_socket)
{
    char command[DEFAULT_BUFFLEN] = "os_shutdown";
    
    if( send(server_socket, command, DEFAULT_BUFFLEN, 0 ) == SOCKET_ERROR )
    {
         printf("\n\t<CLIENTE>Falha no envio de bytes ao servidor remoto.");
    }    
    
    return 0;
}

int os_hardware(SOCKET server_socket)
{
    char command[DEFAULT_BUFFLEN] = "os_hardware";
    
    if( send(server_socket, command, DEFAULT_BUFFLEN, 0 ) == SOCKET_ERROR )
    {
         printf("\n\t<CLIENTE>Falha no envio de bytes ao servidor remoto.");
         _getch();
         return 0;  
    }    
    
     
}
