#include "web.h"

#include <curl_exception.h>
#include <curl/curl.h>

#include <memory>

using mtl::Web;
using curl::curl_easy_exception;
using std::string;

string
Web::escape(string const& s) const
{
    std::unique_ptr<char, void (*)(void*)> t(
        curl_easy_escape(this->session_.get_curl(), s.c_str(),
                         static_cast<int>(s.length())),
        curl_free);  // ALT: [](char *p) { curl_free(p); });
    if (!t) {
        throw curl_easy_exception("Failed curl_easy_escape (nullptr)",
                                  __FUNCTION__);
    }
    // ALT: std::move whole pointer to outside
    return string(t.get());
}

string
Web::composeParams(std::vector<std::pair<const string, const string>> const& params) const
{
    string s;
    for (const auto& p : params) {
        if (!s.empty()) {
            s += "&";
        }
        s += escape(p.first);
        if (!p.second.empty()) {
            s += "=" + escape(p.second);
        }
    }
    return std::move(s);
}

string
Web::perform(string const& query)
{
    this->stream_.str(string());
    this->stream_.clear();

    this->session_.add<CURLOPT_URL>(query.c_str());

    // DEV:(exceptions) bad_request, bad_network
    try {
        this->session_.perform();
    } catch (curl_easy_exception const& e) {
        e.print_traceback();
        // DEV: re-throw my own exceptions
    }

    // DEV:(exceptions) process ret code: 403, etc
    auto ret = this->session_.get_info<CURLINFO_RESPONSE_CODE>();
    std::cout << ret.get() << std::endl;

    return this->stream_.str();
}
