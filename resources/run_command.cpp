#include "run_command.hpp"

int run_command::runffmpeg(std::string url, std::string stream_id, std::string ffmpeg_command ){
    this->stream_id = stream_id;
    this->url = url;
    this->ffmpeg_command = ffmpeg_command;
    int pid = fork();
    if(pid == 0){
        std::cout<< "Desde el hijo" << std::endl;
        INIReader reader("flixac.ini");
        if (reader.ParseError() != 0) {
            std::cout << "Can't load configuration file\n";
            return -1;
        }
        std::string ffmpeg_bin = reader.Get("ffmpeg", "bin", "");
        if(ffmpeg_bin.empty()){
            std::cout << "error Ffmpeg path not found \n";
            return -1;
        }
        std::string ffmpeg_log_path = reader.Get("ffmpeg","log","");
        if(ffmpeg_log_path.empty()){
            std::cout << "error log path not found \n";
            return -1;
        }
        std::string rtmp_server = reader.Get("ffmpeg","rtmp_server","");
        if(ffmpeg_log_path.empty()){
            std::cout << "error rtmp server adress not found \n";
            return -1;
        }
        std::string log_path_string = "FFREPORT=file="+ffmpeg_log_path + this->stream_id +".log:level=16";
        std::istringstream iss(this->ffmpeg_command);
        std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                        std::istream_iterator<std::string>());
        int size = results.size() + 9;
        char* commands[size];
        commands[0] = (char *)"ffmpeg";
        commands[1] = (char *)"-loglevel";
        commands[2] = (char *)"error";
        commands[3] = (char *)"-report";
        commands[4] = (char *)"-i";
        commands[5] = (char *)this->url.c_str();
        for (int x = 0 ; x < results.size(); x++) {
            commands[x + 6] = (char *)results[x].c_str();
        }
        
        rtmp_server.append(this->stream_id);
        commands[size-3] = (char *)"-f";
        commands[size-2] = (char *)"flv";
        commands[size-1] = (char *)live_url.c_str();
        commands[size] = NULL; 
        char  *env[] = { (char *)log_path_string.c_str(),  (char *)0 };
        execve (ffmpeg_bin.c_str(), commands, env);
        perror("Error pid");
        
    }else{
        return pid;
    } 
    return -1;
}

run_command::run_command(){

}