#include <cpr/cpr.h>
#include <json.hpp>

#include <iostream>
#include <regex>

using json = nlohmann::json;

static int
parse(std::string const& text)
{
    auto json_dom = json::parse(text);
    std::cout << json_dom.dump(2) << std::endl;
    return 0;
}

static cpr::Cookies
getCookies()
{
    auto const kAgent = "Mozilla/5.0 (X11; Linux x86_64) ";
    auto const kUrl = "http://www.bing.com/translator";
    auto header = cpr::Header({{"Host", "www.bing.com"},
                               {"Connection", "close"},
                               {"User-Agent", kAgent}});

    auto rsp = cpr::Get(cpr::Url{kUrl}, header);
    return rsp.cookies;
}


int bing(std::string const& text, std::string const& sl, std::string const& tl)
{
    auto const kAgent = "Mozilla/5.0 (X11; Linux x86_64) ";
    auto const kUrl = "http://www.bing.com/translator/api/Translate/TranslateArray";

    auto const cookies = getCookies();

    auto header = cpr::Header({{"Host", "www.bing.com"},
                               {"Connection", "close"},
                               {"User-Agent", kAgent},
                               {"Content-Type", "application/json"}});

    auto params = cpr::Parameters{{"from", sl}, {"to", tl}};

    json body;
    body[0]["text"] = text;

    cpr::Session session;
    session.SetUrl(kUrl);
    session.SetHeader(header);
    session.SetParameters(params);
    // session.SetBody(cpr::Body{R"([{"text": "kumo desu ka"}])"});
    session.SetBody(cpr::Body{body.dump()});
    session.SetCookies(cookies);

    // // DEV:(exceptions) bad_request, bad_network
    auto response = session.Post();

    // // DEV:(exceptions) process ret code: 403, etc
    // std::cout << response.text << std::endl;

    // DEV:(exceptions) std::invalid_argument -- wrong format
    parse(response.text);

    return 0;
}
