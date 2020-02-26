#include <httpserver.hpp>


using namespace httpserver;
class start_stream_resource : public http_resource {
    public:
            const std::shared_ptr<http_response> render_GET(const http_request&);
            const std::shared_ptr<http_response> render(const http_request&);
};