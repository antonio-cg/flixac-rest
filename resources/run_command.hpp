#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
#include <vector>
#include <iterator>
#include "dist/inih/INIReader.h"

class run_command {
    private: 
        std::string stream_id;
        std::string url ; 
        std::string ffmpeg_command;
        public:
        int runffmpeg(std::string url, std::string stream_id, std::string ffmpeg_command);
        run_command();
};