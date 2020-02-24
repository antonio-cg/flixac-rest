#include <iostream>
#include "resources/check_stream_resource.hpp"
#include "dist/nlohmann/json.hpp"


using json = nlohmann::json;
using namespace httpserver;
 
 
const std::shared_ptr<http_response> check_stream_resource::render_POST(const http_request& req){
        std::cout << req.get_content()<< "\n";
        json data;
        auto req_string = req.get_content();
        if(json::accept(req_string)){
            std::cout << "json valido" << "\n";
        }else{
            std::cout << "error json" << "\n";
            string_response* res = new string_response ("Json Parse Error" ,400, "application/json");
            return std::shared_ptr<http_response>(res);
        }
        auto stream_name = req.get_arg("stream_name");
        data["prueba"] = stream_name;
        data["cmd"] = "prueba de json";
        auto stringjson = data.dump();
        std::cout << "respondiendo" << "\n";
        string_response* res = new string_response (stringjson ,200, "application/json");
        return std::shared_ptr<http_response>(res);
}