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

int apertium(std::string const& text, std::string const& sl, std::string const& tl)
{
    auto const kAgent = "Mozilla/5.0 (X11; Linux x86_64) ";
    auto const kUrl = "http://www.apertium.org/apy/translate";

    auto params = cpr::Parameters{{"langpair", sl + "|" + tl},
                                  {"q", text}};

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
