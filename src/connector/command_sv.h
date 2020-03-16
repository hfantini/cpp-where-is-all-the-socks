#include "define.h";
#include "function.h";

//DEFINE COMANDOS REFERENTES AO SERVIDOR (TERMINAL)

char sv_shutdown(SOCKET server_sock) //CLIENT VERSION
{
    //PREPARANDO PARA ENVIAR COMANDO
    char command[] = "sv_shutdown";
    if( send(server_sock, command, DEFAULT_BUFFLEN, 0 ) == SOCKET_ERROR )
    {
        printf("\n\t<CLIENTE>Falha no envio de bytes ao servidor remoto.");
        return 0;
    }
    
    
    char resposta[DEFAULT_BUFFLEN];
    //RESPOSTA
    if( recv(server_sock, resposta, DEFAULT_BUFFLEN, 0 ) != SOCKET_ERROR )
    {
        if(strcmp(command, "SV_SHUTDOWN_OK"))
        {
            printf("\n\t<SERVIDOR> Foi desligado com sucesso. Esta aplicação será finalizada");
            _getch();
            exit(EXIT_SUCESS);
        }
    }
    else
    {
        printf("\n\t<CLIENTE>Nao houve resposta do servidor.");
        _getch();
    }
      
}

char sv_ip(SOCKET server_sock ,char param[][PARAM_MAX_LEN])
{
    
    char command[DEFAULT_BUFFLEN] = "sv_ip";
    
    if( strcmp(param[0], "P") == 0 ) //CHECAGEM DE PARAMETROS
    {
           strcat(command, " -p");
    } 
    
    if( send(server_sock, command, DEFAULT_BUFFLEN, 0 ) == SOCKET_ERROR )
    {
        printf("\n\t<CLIENTE>Falha no envio de bytes ao servidor remoto.");
        return 0;
    }
    else
    {
        char resposta[DEFAULT_BUFFLEN];
        
        if( recv(server_sock, resposta, DEFAULT_BUFFLEN, 0 ) != SOCKET_ERROR )
        {
            printf("\n\t<SERVIDOR> %s", resposta);
        }
        else
        {
            printf("\n\t<CLIENTE>Nao houve resposta do servidor.");
            _getch();
        }          
    }
    
    char resposta[DEFAULT_BUFFLEN];

}
