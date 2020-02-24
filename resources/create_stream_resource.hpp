#include <httpserver.hpp>
#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include "dist/nlohmann/json.hpp"
#include "database/db_controller.hpp"
#include "database/models.hpp"
#include <time.h>

using namespace httpserver;

class create_stream_resource : public http_resource {
    public:
            const std::shared_ptr<http_response> render_POST(const http_request& req);
};