#ifndef _DS_HTTP_REQUEST_H_
#define _DS_HTTP_REQUEST_H_


typedef enum{
    HTTP_GET_WEATHER = 0,
    HTTP_GET_CITY,
}HTTP_REQUEST_TYPE_E;

void ds_http_request_init(void);
void ds_http_request_type(HTTP_REQUEST_TYPE_E type);
void ds_http_request_all(void);

#endif

