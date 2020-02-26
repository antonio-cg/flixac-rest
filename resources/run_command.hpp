#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

class run_command {
    public:
        int runffmpeg(char **command);
        run_command();
};