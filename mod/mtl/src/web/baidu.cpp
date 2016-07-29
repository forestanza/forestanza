#include "mtl.h"

#include <cpr/cpr.h>
#include <json.hpp>

#include <iostream>
#include <regex>

static int
parse(std::string const& text)
{
    auto json_dom = nlohmann::json::parse(text);
    std::cout << json_dom.dump(2) << std::endl;
    return 0;
}

int baidu(std::string const& text, std::string const& sl, std::string const& tl)
{
    auto const kAgent = "Mozilla/5.0 (X11; Linux x86_64) ";
    auto const kUrl = "http://translate.baidu.com/transcontent";
    auto params = cpr::Parameters{{"from", sl},
                                  {"to", tl},
                                  {"ie", "utf-8"},
                                  {"source", "txt"},
                                  {"query", text}};

    cpr::Session session;
    session.SetUrl(kUrl);
    session.SetHeader({{"User-Agent", kAgent}});
    session.SetParameters(params);

    // DEV:(exceptions) bad_request, bad_network
    auto response = session.Get();

    // DEV:(exceptions) process ret code: 403, etc
    // std::cout << response.text << std::endl;

    // DEV:(exceptions) std::invalid_argument -- wrong format
    parse(response.text);

    return 0;
}
