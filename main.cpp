#include <httpserver.hpp>
#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "dist/inih/INIReader.h"
#include "resources/check_stream_resource.hpp"
#include "resources/create_stream_resource.hpp"
#include "resources/start_stream_resource.hpp"
#include "resources/stop_stream_resource.hpp"
#include "resources/restart_stream_resource.hpp"

using namespace httpserver;

void sigChld(int arg){
	int pid ;
	printf("SIGCHLD caught\n") ;
	pid = wait(NULL) ;
	printf("signal's wait() caught pid %d\n", pid) ;
	signal(SIGCHLD, sigChld) ;
}

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
        INIReader reader("flixac.ini");

        if (reader.ParseError() != 0) {
            std::cout << "Can't load configuration file\n";
            return 1;
        }
        int port = reader.GetInteger("server", "port", -1);
        if(port < 0){
            std::cout << "error port \n";
            return 1;
        }
        signal(SIGCHLD, sigChld) ;
        webserver ws = create_webserver(port);
        std::cout << "Server Started port "<<port << "\n";
        check_stream_resource check_stream_resource;
        create_stream_resource create_stream_resource;
        stop_stream_resource stop_stream_resource;
        restart_stream_resource restart_stream_resource;
        start_stream_resource start_stream_resource;
        ws.register_resource("/check/{stream-id}/", &check_stream_resource);
        ws.register_resource("/create/{stream-id}", &create_stream_resource);
        ws.register_resource("/start/{stream-id}", &start_stream_resource);
        ws.register_resource("/stop/{stream-id}", &stop_stream_resource);
        ws.register_resource("/restart/{stream-id}", &restart_stream_resource);
        ws.start(true);
    return 0;
}
