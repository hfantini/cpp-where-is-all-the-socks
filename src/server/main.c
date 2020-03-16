#include "define.h"
#include <winsock.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "command.h"
#include "function.h"

int main()
{
    HWND hWnd = GetConsoleWindow();
    //ShowWindow( hWnd, SW_HIDE );

       
    //VAR AND STRUCTS
    struct WSAData wsaData;
    struct sockaddr_in sockadress;
    int sock;
    int connect_status = 0;
    
    printf("\n\t********************************************\n");
    printf("\t********************************************\n");
    printf("\t********** WHERE'S ALL THE SOCKS? **********\n");
    printf("\t**********  BY: Henrique Fantini  **********\n");
    printf("\t**********     SERVER VERSION     **********\n");
    printf("\t********************************************\n");
    printf("\t********************************************\n\n\n\n");
    
    printf("\tINICIALIZANDO COMPONENTES WINSOCK: ");
    if(WSAStartup(MAKEWORD(2,0), &wsaData) != 0)
    {
        printf("ERROR \n");
        WSACleanup();
		_getch();
        return EXIT_FAIL;
        
    } printf("OK\n");
    
    //DEFININDO ESTRUTURA SOCKADDR_IN
    sockadress.sin_family = AF_INET;
    sockadress.sin_port = htons(SERVER_PORT);
    sockadress.sin_addr.s_addr = inet_addr(SERVER_IP);
    
    printf("\tCRIANDO O SOCKET: ");
    //CRIANDO UM SOCK
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
    {
             
        printf("ERROR \n");
        WSACleanup();
		_getch();
        return EXIT_FAIL;            
             
    } printf("OK\n");
    
    printf("\tBINDANDO A CONEXAO: ");
    if( bind(sock, (SOCKADDR *)&sockadress, sizeof(sockadress)) == SOCKET_ERROR)
    {
             
        printf("ERROR \n");
        WSACleanup();
		_getch();
        return EXIT_FAIL;            
             
    } printf("OK\n");
    
    printf("\tINCIANDO O PROCESSO DE LISTEN NA PORTA %d: ", ntohs(sockadress.sin_port));
    if( listen(sock, SOMAXCONN) == SOCKET_ERROR)
    {
             
        printf("ERROR \n");
        WSACleanup();
		_getch();
        return EXIT_FAIL;            
             
    } printf("OK\n");   
        
    SOCKET client = INVALID_SOCKET; //SOCKET QUE DEFINE O CLIENTE
    struct sockaddr_in client_stats;
    int client_stats_len = sizeof(client_stats);
      
    printf("\n\t:: AGUARDANDO CONEXOES :: ");
    client = accept(sock, (SOCKADDR *)&client_stats, &client_stats_len);
    
    printf("\n\n\tNovo cliente conectado - %s:%d", inet_ntoa(client_stats.sin_addr), ntohs(client_stats.sin_port)); 
    closesocket(sock); 
    
    char mensagem[DEFAULT_BUFFLEN] = "";
    int bytes;

    do 
    {
        bytes = recv(client, mensagem, DEFAULT_BUFFLEN, 0);
        
        if(bytes > 0 )
        {
             readCommand(mensagem, client);
        }
        
        free(bytes);
        
    } while( 1 == 1 );
    
    _getch();
    return EXIT_SUCESS;
}
