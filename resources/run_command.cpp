#include "run_command.hpp"

int run_command::runffmpeg(char **command){
    INIReader reader("flixac.ini");

    if (reader.ParseError() != 0) {
        std::cout << "Can't load configuration file\n";
        return -1;
    }
    int pid = fork();
    if(pid == 0){
        //hacer las cosas del hijo
        std::cout<< "Desde el hijo" << std::endl;
        char  *env[] = { (char *)"FFREPORT=file=/var/log/flixac/ffreport.log:level=10",  (char *)0 };
        //execvp("/usr/bin/ffmpeg",command);
        execve ("/usr/bin/ffmpeg", command, env);
        perror("Error PId");
        std::cout << "se termino el proceso " << std::endl;
    }else{
        return pid;
    } 
    return -1;
}

run_command::run_command(){

}