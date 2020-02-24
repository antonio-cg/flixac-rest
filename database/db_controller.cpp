#include "db_controller.hpp"

db_controller* db_controller::instance = nullptr;

std::unique_ptr<Storage> db_controller::stor = std::make_unique<Storage>(initStorage("update.sqlite")); 

db_controller* db_controller::getInstance(){
   

        if (instance == NULL)
        {
            std::cout<< "creating new instance \n";
            instance = new db_controller();
            try{
                stor->sync_schema();
            }catch(std::system_error err){
                std::cout << err.what() << std::endl;
            }
        }
        else{
            std::cout << "Getting existing instance"<<std::endl;
        }

    return instance;
}

db_controller::db_controller(){
    std::cout << "creating singleton for db "<< "\n";
}




