/* request.c: Make HTTP Requests */

#include "request.h"

#include "macros.h"
#include "socket.h"

#include <stdlib.h>
#include <string.h>

#include <errno.h>

/* Constants */

#define HOST_DELIMITER  "://"
#define PATH_DELIMITER  '/'
#define PORT_DELIMITER  ':'

/* Functions */

/**
 * Construct Request structure by parsing URL string into separate host, port,
 * and path components.
 *
 * @param   url         URL string to parse.
 *
 * @return  Request structure.
 **/
Request *   request_create(const char *url) {
    /* TODO: Copy data to local buffer */
    char *buffer = strdup(url);
    if (!buffer) {
        fprintf(stderr, "strdup: %s\n", strerror(errno));
        return NULL;
    }

    /* TODO: Skip scheme to host */
    char *host = strstr(buffer, HOST_DELIMITER);
    if (host) {
        host += 3;
        if (!host) return NULL;
    } else {
        host = buffer;
    }
    
    /* TODO: Split host:port from path */
    char *path = strchr(host, PATH_DELIMITER);
    if (path) {
        *path = '\0';
        path++;
    } else path = "";

    /* TODO: Split host and port */
    char *port = strchr(host, PORT_DELIMITER);
    if (port) {
        *port = '\0';
        port++;
    }

    if (!port) port = "80";

    /* TODO: Allocate Request structure */
    Request *req = (Request *)malloc(sizeof(Request));

    /* TODO: Copy components to URL structure */
    req->host = strdup(host);
    if (!(req->host)) {
        fprintf(stderr, "strdup: %s\n", strerror(errno));
        free(req);
        return NULL;
    }

    req->port = strdup(port);
    if (!(req->port)) {
        fprintf(stderr, "strdup: %s\n", strerror(errno));
        free(req->host);
        free(req);
        return NULL;
    }

    req->path = strdup(path);
    if (!(req->path)) {
        fprintf(stderr, "strdup: %s\n", strerror(errno));
        free(req->host);
        free(req->port);
        free(req);
        return NULL;
    }

    /* Deallocate buffer */
    free(buffer);

    return req;
}

/**
 * Deallocate Request structure.
 *
 * @param   request     Request structure to deallocate.
 **/
void	    request_delete(Request *request) {
    if (!request) return;
    free(request->host);
    free(request->port);
    free(request->path);
    free(request);
}

/**
 * Make a HTTP request and write the contents of the response to the specified
 * stream.
 *
 * @param   url         Make a HTTP request to this URL.
 * @param   stream      Write the contents of response to this stream.
 *
 * @return  -1 on error, otherwise the number of bytes written.
 **/
ssize_t     request_stream(Request *request, FILE *stream) {
    /* TODO: Connect to remote host and port */
    FILE *client_file = socket_dial(request->host, request->port);
    if (!client_file) return -1;

    /* TODO: Send request to server */
    fprintf(client_file, "GET /%s HTTP/1.0\r\n", request->path);
    fprintf(client_file, "Host: %s\r\n", request->host);
    fprintf(client_file, "\r\n");

    /* TODO: Read response status from server */
    char buffer[BUFSIZ];
    if (fgets(buffer, BUFSIZ, client_file)) {
        if (!strstr(buffer, "200 OK")) {
            fclose(client_file);
            return -1;
        }
    } else {
        fclose(client_file);
        return -1;
    }

    /* TODO: Read response headers from server */
    size_t expected_length = -1;
    while (fgets(buffer, BUFSIZ, client_file) && (strlen(buffer) > 2)) {
        sscanf(buffer, "Content-Length: %lu", &expected_length);
    }

    /* TODO: Read response body from server */
    size_t actual_length = 0;
    while (!feof(client_file)) {
        size_t bytes_read = fread(buffer, 1, BUFSIZ, client_file);
        if (ferror(client_file)) {
            fclose(client_file);
            return -1;
        }

        actual_length += fwrite(buffer, 1, bytes_read, stream);
        if (ferror(client_file)) {
            fclose(client_file);
            return -1;
        }
    }

    /* TODO: Close connection */
    if (fclose(client_file) == EOF) return -1;

    /* TODO: Return number of bytes written and check if it matches Content-Length */
    if (expected_length != -1) {
        if (expected_length == actual_length) return actual_length;
        else return -1;
    }

    return actual_length;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
