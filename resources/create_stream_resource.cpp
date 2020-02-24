#include "resources/create_stream_resource.hpp"

using json = nlohmann::json;
using namespace httpserver;
 
 
const std::shared_ptr<http_response> create_stream_resource::render_POST(const http_request& req){
        string_response* response;
        json response_json;
        json req_json;
        
        std::string stream_id = req.get_arg("stream-id");
        std::cout << "stream name: " << stream_id << "\n";
        using namespace sqlite_orm;
        db_controller* db = db_controller::getInstance(); 
        std::cout <<" Quering db \n";
        try{
            auto query = db->stor->get_all<Stream>(where( c(&Stream::stream_id) == stream_id ));
        
            std::cout<< "ok database \n";
            if(query.size() > 0 ){
                response_json["error"] = "stream already register";
                response = new string_response (response_json.dump() ,400, "application/json");
            }else{
                if(json::accept(req.get_content())){
                    std::cout << "json valido" << "\n";
                    std::cout << req.get_content() << std::endl;
                    req_json = json::parse( req.get_content());
                    std::string url = req_json.at("url");
                    int created_by = req_json.at("created_by");
                    std::string ffmpeg_command = req_json.at("ffmpeg_command");
 /*
                    std::istringstream iss(ffmpeg_command);
                    std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                                    std::istream_iterator<std::string>());
                    
                    char* commands[results.size()+1];
                    std::copy(results.begin(), results.end(), commands);
*/

                    int last_id = db->stor->insert(Stream{NULL, NULL, created_by, stream_id,url, ffmpeg_command, time(0), 0});
                    response_json["success"]  = last_id;
                    response = new string_response (response_json.dump(),200, "application/json");
                }else{
                    std::cout << "error json" << "\n";
                    response = new string_response ("Json Parse Error" ,400, "application/json");
                }
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
