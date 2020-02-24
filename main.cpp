#include <httpserver.hpp>
#include <iostream>
#include <stdio.h>
#include "resources/check_stream_resource.hpp"
#include "resources/create_stream_resource.hpp"


using namespace httpserver;


int main(int argc, char** argv) {
        //gcc -o httpbuild -I ./ *.cpp resources/* database/* -lhttpserver -lsqlite3 -std=gnu++14  -lstdc++ 
        //añadir rutas para
        //revisar stream
        //añadir stream
        //reiniciar stream
        //parar stream
        //mostrar ultimos errores de stream
        //uptime de stream
        //estado del servidor (CPU, RAM, STORAGE)
    switch(getpid()){
        case 0:
            std::cout<< "hilo Hijo Creado" << "\n";
        break;
        default:
            webserver ws = create_webserver(8081);
            std::cout << "Server Started port 8081" << "\n";
            check_stream_resource check_stream_resource;
            create_stream_resource create_stream_resource;
            ws.register_resource("/check-stream/{stream-id}/", &check_stream_resource);
            ws.register_resource("/create-stream/{stream-id}", &create_stream_resource);
            ws.start(true);
    }

    return 0;
}
