#include <json.hpp>

#include <curl_easy.h>
#include <curl_form.h>
#include <curl_ios.h>
#include <curl_exception.h>

#include <iostream>
#include <ostream>

int main(int /* argc */, char** /* argv */)
{
    std::ostringstream oss;
    curl::curl_ios<std::ostringstream> writer(oss);
    curl::curl_easy req(writer);

    req.add<CURLOPT_URL>("https://httpbin.org/get");
    req.add<CURLOPT_FOLLOWLOCATION>(1L);
    req.add<CURLOPT_SSL_VERIFYPEER>(0L);

    try {
        req.perform();
    } catch (curl::curl_easy_exception error) {
        // NOTE: printing the stack will erase it
        error.print_traceback();
        // ALT: curl::curlcpp_traceback errors = error.get_traceback();
    }

    auto json = nlohmann::json::parse(oss.str());
    std::cout << json.dump(2) << std::endl;
    std::cout << "done" << std::endl;
    return 0;
}
