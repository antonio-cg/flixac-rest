#include <iostream>

#ifndef MODELS_H
#define MODELS_H

struct Stream{
    int         id; 
    int         pid;
    int         created_by;
    std::string stream_id;
    std::string url;
    std::string ffmpeg_command;
    long int         added;
    long int         last_start;
};



#endif

