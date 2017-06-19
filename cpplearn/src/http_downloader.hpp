#ifndef HTTP_DOWNLOADER_HPP
#define HTTP_DOWNLOADER_HPP

#include <string>

namespace cpplearn {

    class http_downloader {
        private:
            void* curl;
            static auto write_data(void*, size_t, size_t, void*) -> size_t;
        public:
            http_downloader();
            ~http_downloader();

            auto download(const std::string&) -> std::string;
    };

} // namespace cpplearn

#endif
