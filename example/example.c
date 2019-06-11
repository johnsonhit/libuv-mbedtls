#include <uv_tls.h>

void _uv_tcp_connect_established_cb(uv_connect_t* req, int status);
void _uv_write_cb(uv_write_t* req, int status);
void _uv_tls_rd_cb(uv_tls_t* h, int nrd, uv_buf_t* dcrypted);

int main(int argc, const char *argv[]) {
    uv_loop_t *loop = malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);

    uv_connect_t *connect = (uv_connect_t *) calloc(1, sizeof(uv_connect_t));
    uv_tls_t *socket = (uv_tls_t*)calloc(1, sizeof(uv_tls_t));
    uv_tls_init(loop, socket);
    connect->data = socket;
    uv_tls_connect(connect, socket, "www.csdn.net", 443, _uv_tcp_connect_established_cb);

    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    free(loop);
    return 0;
}

void _uv_tcp_connect_established_cb(uv_connect_t* req, int status) {
    uv_tls_t *socket = (uv_tls_t *) req->data;
    uv_write_t *wreq = (uv_write_t *) calloc(1, sizeof(uv_write_t));
    wreq->data = socket;

#define HTTP_REQUEST            \
    "GET / HTTP/1.1\r\n"        \
    "Host: www.csdn.net\r\n"    \
    "\r\n"

    uv_buf_t buf = uv_buf_init(HTTP_REQUEST, (unsigned int)strlen(HTTP_REQUEST));

    uv_tls_write(wreq, socket, &buf, _uv_write_cb);

    free(req);
}

void _uv_write_cb(uv_write_t* req, int status) {
    uv_tls_t *socket = (uv_tls_t *) req->data;
    uv_tls_read(socket, _uv_tls_rd_cb);
    free(req);
}

void _uv_tls_rd_cb(uv_tls_t* h, int nrd, uv_buf_t* dcrypted) {
    if (nrd > 0) {
        printf("%s", dcrypted->base);
    } else {
        // assert(0);
    }
}
