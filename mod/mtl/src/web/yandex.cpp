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

static std::string
getSid()
{
    std::string sid;
    cpr::Session session;
    session.SetUrl("https://translate.yandex.com");
    session.SetHeader({{"User-Agent", "Mozilla/5.0 (X11; Linux x86_64) "}});
    auto response = session.Get();
    // Get: TRANSLATOR_LANGS: {...} for available list
    std::regex rgx_sid(R"(SID:\s*'([^.']+)\.([^.']+)\.([^.']+)')",
            std::regex::optimize);
    std::smatch m;
    if (std::regex_search(response.text, m, rgx_sid)) {
        for (size_t i = 1; i < m.size(); ++i) {
            std::string s = m[i].str();
            std::reverse(s.begin(), s.end());
            sid += s + ".";
        }
    } else {
        throw std::runtime_error("Can't find SID on page");
    }
    (void)sid.pop_back();
    return sid;
}


int yandex(std::string const& text, std::string const& sl, std::string const& tl)
{
    // DEV: inherit DFL agent from config on obj creation
    auto const kAgent = "Mozilla/5.0 (X11; Linux x86_64) ";
    auto const kUrl = "http://translate.yandex.net/api/v1/tr.json/translate";
    std::string sid;

    try {
        sid = getSid();
    } catch (std::exception &ex) {
        std::cout << "Error: " << ex.what() << std::endl;
        return 1;
    }

    auto params = cpr::Parameters{{"id", sid + "-0-0"},
                                  {"srv", "tr-text"},
                                  {"lang", sl + "-" + tl},
                                  {"text", text}};

    // std::cout << params.content << std::endl;

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

    // try {
    //     // ...
    // } catch(const bad_alloc& b) {
    //     MessageUser("all is bad");
    //     throw;
    // }

    return 0;
}
