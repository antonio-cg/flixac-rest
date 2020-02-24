#include "dist/sqlite_orm/sqlite_orm.h"
#include <iostream>
#include "models.hpp"


inline auto initStorage(const std::string &path) {
    using namespace sqlite_orm;
    return make_storage(path,
                        make_table("streams",
                                   make_column("id", &Stream::id, autoincrement(), primary_key()),
                                   make_column("pid", &Stream::pid),
                                   make_column("created_by", &Stream::created_by),
                                   make_column("stream_id", &Stream::stream_id),
                                   make_column("url", &Stream::url),
                                   make_column("ffmpeg_command", &Stream::ffmpeg_command),
                                   make_column("added", &Stream::added),
                                   make_column("last_start", &Stream::last_start)));
}

using Storage = decltype(initStorage(""));
