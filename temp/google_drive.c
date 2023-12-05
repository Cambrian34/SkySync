#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <curl/curl.h>
#include <glib.h>

#include "google_drive.h"


// Add this global variable to store the received URI

// Function to open the user's default web browser to the Google authorization URL
void open_google_auth_url( gchar* CLIENT_ID) {
    // Your OAuth parameters
    const gchar* redirect_uri = "http://localhost:8080";
    const gchar* scope = "https://www.googleapis.com/auth/drive";

    // Format the authorization URL
    const gchar* auth_url_format = "https://accounts.google.com/o/oauth2/auth?client_id=%s&redirect_uri=%s&scope=%s&response_type=code";
    gchar* auth_url = g_strdup_printf(auth_url_format, CLIENT_ID, redirect_uri, scope);

    // Allocate memory for the final URL
    gchar* final_url = g_strdup(auth_url);

    // Print the final URL for verification
    g_print("Final URL: %s\n", final_url);

    // Open the default web browser with the Google authorization URL (platform-dependent)
    gchar* cmd = g_strdup_printf("open \"%s\"", final_url); // Adjust this line for other platforms
    system(cmd);

    // Free allocated memory
    g_free(auth_url);
    g_free(final_url);
    g_free(cmd);
}

// Function to read the JSON file and extract values
OAuthInfo read_json_file(const char *filename)
{
    OAuthInfo oauth_info = {"", ""};

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_JSON_SIZE];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[bytesRead] = '\0';

    fclose(file);

    // Find "client_id"
    char *client_id_start = strstr(buffer, "\"client_id\":");
    if (client_id_start != NULL)
    {
        sscanf(client_id_start + strlen("\"client_id\":\""), "%99[^\"]", oauth_info.client_id);
    }

    // Find "auth_uri"
    char *auth_uri_start = strstr(buffer, "\"auth_uri\":");
    if (auth_uri_start != NULL)
    {
        sscanf(auth_uri_start + strlen("\"auth_uri\":\""), "%199[^\"]", oauth_info.auth_uri);
    }

    return oauth_info;
}

