#ifndef GOOGLE_DRIVE_H
#define GOOGLE_DRIVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <curl/curl.h>
#include <glib.h>

#define MAX_JSON_SIZE 2048
#include <fcntl.h>



//Define the structure to store the extracted values

typedef struct{
    gchar client_id[100];
    gchar auth_uri[200];
} OAuthInfo;


struct Buffer {
    char *data;
    size_t size;
};
// Helper function to perform a generic HTTP GET request

// Function prototypes

void open_google_auth_url( gchar* CLIENT_ID);

// Google Drive API

OAuthInfo read_json_file(const char *filename);



#endif
