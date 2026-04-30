#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include <fcntl.h>


#define WIFI_SUPPORTED

#include "server_utils.h"


#include "server.h"
#include "index_page.h"

#define PORT 1337
#define MAX_CONNECTIONS 4
#define REQUEST_BUFFER_SIZE 1024
#define NOT_FOUND_RESPONSE  "HTTP/1.1 404 Not Found\r\n\n"


//TODO - don't duplicate
static const char *ProgramNames[] = {"Spinning Rainbow", "Stars", "Blocks", "Text", "Gradient", "Bouncing Ring", "Tempus Fulvum", "Frogger"};

const char **GetProgramNames()
{
    return ProgramNames;
}


static uint32_t selectedProgram = 1;
static band_settings_t bandSettings;


int main()
{
    index_page_init(&selectedProgram, &bandSettings);

    static int connections[MAX_CONNECTIONS];
    static char HttpRequestBuffer[REQUEST_BUFFER_SIZE];
    static TCP_RESPONSE_T response;
   
    for (int i = 0; i < MAX_CONNECTIONS; i++)
    {
        connections[i] = -1;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    int flags = fcntl(serverSocket, F_GETFL, 0);
    fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK);

    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
    printf("Error: The server is not bound to the address.\n");
    return 1;
    }

    if (listen(serverSocket, MAX_CONNECTIONS) < 0)
    {
    printf("Error: The server is not listening.\n");
    return 1;
    }

    printf("server started on port %u\n", PORT);


    while (true) {
        int const clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket >= 0) {
            printf("new connection on fd %i\n", clientSocket);
            int i = 0;
            for (; i < MAX_CONNECTIONS; i++)
            {
                if (connections[i] == -1) {
                    connections[i] = clientSocket;
                    break;
                }
            }
            if (i == MAX_CONNECTIONS)
            {
                printf("Too many connections");
                close(clientSocket);
            }
        }

        for (int i = 0; i < MAX_CONNECTIONS; i++)
        {
            int const clientSocket = connections[i];
            if (clientSocket != -1)
            {
                int result = read(clientSocket, HttpRequestBuffer, REQUEST_BUFFER_SIZE);
                if (result < 0)
                {
                    continue; // TODO should handle errors properly
                }
                if (result == 0)
                {
                    close(clientSocket);
                    connections[i] = -1;
                }
                else
                {
                    printf("Got this http request\n%s", HttpRequestBuffer);
                    handle_http_request(HttpRequestBuffer, &response, handle_server_request, handle_post_request);
                    
                    send(clientSocket, response.headers, response.header_len, 0);
                    if (response.result_len)
                    {
                        send(clientSocket, response.result, response.result_len, 0);
                    }
                }
            }
        }
    }
}
