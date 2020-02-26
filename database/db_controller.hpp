#ifndef db_controller_h
#define db_controller_h

#include <iostream>
#include "models.hpp"
#include "storage.hpp"


class db_controller {
    public:
        static db_controller *getInstance();
        static std::unique_ptr<Storage> stor; 
    protected:
        db_controller();
        virtual ~db_controller()=default;
        db_controller(db_controller const&)=delete;
        db_controller& operator=(db_controller const&) = delete;

    private:
        static db_controller *instance;
        

};
#endif
