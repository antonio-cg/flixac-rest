#include <iostream>
#include "resources/check_stream_resource.hpp"
#include "dist/nlohmann/json.hpp"
#include "database/db_controller.hpp"

using json = nlohmann::json;
using namespace httpserver;
 
 
const std::shared_ptr<http_response> check_stream_resource::render_GET(const http_request& req){
        string_response* response;
        response = new string_response ("todo bien" ,400, "application/json");
        db_controller* db = db_controller::getInstance(); 
        json response_json;
        std::cout << "check_stream_GET" << "\n";
        std::string stream_id = req.get_arg("stream-id");
        using namespace sqlite_orm;
        try{
            auto query = db->stor->get_all<Stream>(where( c(&Stream::stream_id) == stream_id ));
            if(query.size() == 0 ){
                response_json["error"] = "stream doesn't exist";
                response = new string_response (response_json.dump() ,400, "application/json");
            }else{
                Stream stream = (Stream)query[0];
                response_json["created_by"] = stream.created_by;
                response_json["ffmpeg_command"] = stream.ffmpeg_command;
                if (0 == kill(stream.pid, 0))
                {
                    response_json["is_running"] = true;
                }else{
                    response_json["is_running"] = false;
                }
                response_json["url"] = stream.url;
                response = new string_response (response_json.dump() ,400, "application/json");
            }
        }catch(std::system_error e){
            std::cout<< e.what() << std::endl;
            response_json["error"] = e.what();
            response = new string_response (response_json.dump() ,400, "application/json");
        } catch (json::out_of_range ){
            std::cout << "out of range" << '\n';
            response = new string_response ("Json out of range" ,400, "application/json");
        }
        
        return std::shared_ptr<http_response>(response);
        
}

const std::shared_ptr<http_response> check_stream_resource::render(const http_request& req){

    string_response* response;
    json j_response;
    j_response["error"] = "Method not implemented";
    response = new string_response (j_response.dump(),400, "application/json");
    return std::shared_ptr<http_response>(response);
        

}

