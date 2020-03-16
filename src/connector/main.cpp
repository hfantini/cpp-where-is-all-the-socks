#include <winsock.h>
#include <stdio.h>
#include <conio.h>
#include "command.h";
#include "define.h";

#define EXIT_SUCESS 0
#define EXIT_FAIL 1
#define DEFAULT_BUFFLEN 512


int main()
{
    //VAR AND STRUCTS
    WSAData wsaData;
    sockaddr_in destino;
    SOCKET sock;
    int connect_status = 0;
    
	printf("\n\t********************************************\n");
	printf("\t********************************************\n");
	printf("\t********** WHERE'S ALL THE SOCKS? **********\n");
	printf("\t**********  BY: Henrique Fantini  **********\n");
	printf("\t**********     CLIENT VERSION     **********\n");
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
    destino.sin_family = AF_INET;
    destino.sin_port = htons(SERVER_PORT);
    destino.sin_addr.s_addr = inet_addr(SERVER_IP);
    
    printf("\tCRIANDO O SOCKET: ");
    //CRIANDO UM SOCK
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
    {
             
        printf("ERROR \n");
        WSACleanup();
        _getch();
        return EXIT_FAIL;            
             
    } printf("OK\n");
    
    printf("\tCONECTANDO AO DESTINO %s:%d: ", inet_ntoa(destino.sin_addr), ntohs(destino.sin_port));
    if( connect(sock, (SOCKADDR *)&destino, sizeof(destino)) == SOCKET_ERROR)
    {
        printf("ERROR \n");
        WSACleanup();
        _getch();
        return EXIT_FAIL;   
        
    } printf("OK\n");
    
    connect_status = 1;
    printf("\n\t:: CONEXAO ESTABELECIDA NO DESTINO ::\n");
    
    do
    {
         //AQUI TODA A COMUNICAÇÃO COM O SERVIDOR É REALIZADA.       
         char mensagem[DEFAULT_BUFFLEN] = "";
         
         printf("\n\tCOMMAND: ");
		 gets_s(mensagem, sizeof(mensagem) );
         
         readCommand(mensagem, sock);
         
         free(mensagem);

    }while(connect_status == 1);
    
    
    _getch();
    return EXIT_SUCESS;
}
