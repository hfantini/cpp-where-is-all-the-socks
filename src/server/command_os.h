void os_message(char client_sock, char paran [][100])
{
     printf("\n\t<CLIENT> Solicitou o comando OS_MESSAGE");
     
     HWND desktop = GetDesktopWindow();
     
     if( strcmp(paran[1], "") == 0 )
     {
        MessageBox(desktop, paran[0], "Aviso!", MB_ICONINFORMATION);
     }
     else
     {
         MessageBox(desktop, paran[0], paran[1], MB_ICONINFORMATION);
     }
}

void os_username(char client_socket)
{
     printf("\n\t<CLIENT> Solicitou o comando OS_USERNAME");
     
     char username[30] = "";
     gethostname(username, sizeof(username));
     
     char mensagem[DEFAULT_BUFFLEN] = "<SERVIDOR> Nome do Host: ";
     strcat(mensagem, username);
     
     send(client_socket, mensagem, DEFAULT_BUFFLEN, 0);
}

void os_shutdown()
{
     HANDLE hToken;
     TOKEN_PRIVILEGES tkp;
 
     if (OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
     {
 
        LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
        tkp.PrivilegeCount = 1;
        tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        if(AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0))
        {
            ExitWindowsEx(EWX_SHUTDOWN|EWX_POWEROFF|EWX_FORCE,0);
        }
     }
}

void os_hardware(SOCKET client_socket)
{
     SYSTEM_INFO siSysInfo;
     
     GetSystemInfo(&siSysInfo);
     
   printf("Hardware information: \n");  
   printf("  OEM ID: %u\n", siSysInfo.dwOemId);
   printf("  Number of processors: %u\n", 
      siSysInfo.dwNumberOfProcessors); 
   printf("  Page size: %u\n", siSysInfo.dwPageSize); 
   printf("  Processor type: %u\n", siSysInfo.dwProcessorType); 
   printf("  Minimum application address: %lx\n", 
      siSysInfo.lpMinimumApplicationAddress); 
   printf("  Maximum application address: %lx\n", 
      siSysInfo.lpMaximumApplicationAddress); 
   printf("  Active processor mask: %u\n", 
      siSysInfo.dwActiveProcessorMask);      
}
