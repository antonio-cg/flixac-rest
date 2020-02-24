#include <httpserver.hpp>

    using namespace httpserver;
class check_stream_resource : public http_resource {
    public:
            const std::shared_ptr<http_response> render_POST(const http_request&);
};