#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>
//json parser


#include "google_drive.h"



int main(int argc, char *argv[]) {
    const char *filename = "details.json";
    // GTK Initialization
    gtk_init(&argc, &argv);
    
    // Read JSON file and extract values
    OAuthInfo oauth_info = read_json_file(filename);
    //test extracted values
    //printf("Client ID: %s\n", oauth_info.client_id);
    //printf("Auth URI: %s\n", oauth_info.auth_uri);

    // Open Google authorization URL when the app starts
    //segmantation fault here
    open_google_auth_url(oauth_info.client_id);

    // Open the named pipe for reading
    int authPipe = open(AUTH_PIPE_PATH, O_RDONLY);
    // Check if the pipe was opened successfully
    if (authPipe == -1) {
        perror("Error opening named pipe");
        exit(EXIT_FAILURE);
    }

    // Read the authorization code from the pipe
    char authorizationCode[1024];
    ssize_t bytesRead = read(authPipe, authorizationCode, sizeof(authorizationCode));
    if (bytesRead == -1) {
        perror("Error reading from named pipe");
        close(authPipe);
        exit(EXIT_FAILURE);
    }

    // Null-terminate the string
    authorizationCode[bytesRead] = '\0';

    // Close the named pipe
    close(authPipe);

    // Continue with the rest of your application logic, using the received authorization code
    printf("Received Authorization Code: %s\n", authorizationCode);


    return 0;
}