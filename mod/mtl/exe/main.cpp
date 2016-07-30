#include <cpr/cpr.h>
#include <json.hpp>

#include <iostream>

int main(int /* argc */, char** /* argv */)
{
    auto response = cpr::Get(cpr::Url{"https://httpbin.org/get"});
    auto json = nlohmann::json::parse(response.text);
    std::cout << json.dump(2) << std::endl;
    std::cout << "done" << std::endl;
    return 0;
}
