#include "web/google.h"

#include "mtl/api.h"
#include "common/factory.h"

#include <json.hpp>
#include <curl_easy.h>

#include <iostream>
#include <regex>
#include <chrono>

using mtl::Google;
using std::string;

static const bool gRegGoogle =
    factorySingleton<mtl::Mtl>().add("google", new_maker<Google>);

Google::Google()
{
    this->init();
}

void
Google::init()
{
    // Web::init();
    session_.add<CURLOPT_USERAGENT>(this->agent_.c_str());
    session_.add<CURLOPT_FOLLOWLOCATION>(1L);
    session_.add<CURLOPT_NOPROGRESS>(1L);
    session_.add<CURLOPT_MAXREDIRS>(50L);
    session_.add<CURLOPT_COOKIEFILE>("");
    session_.add<CURLOPT_TCP_KEEPALIVE>(1L);
    // DEV: open connection
    // this->session_.add<CURLOPT_CONNECT_ONLY>(true);
}

string
Google::parse(string const& resp) const
{
    // EXPL: fill empty array items with 'null' to obtain valid JSON.
    auto json_str = std::regex_replace(resp, this->re_skipped_null_, "$&null");
    // DEV:(exceptions) std::invalid_argument -- wrong format
    auto json_dom = nlohmann::json::parse(json_str);

    // 0 - original, translation, phonetics
    // 1 - word classes and explanations
    // 5 - alternative translations
    // 7 - autocorrection
    // 8 - identified source languages
    // 11 - (original) word classes and synonyms
    // 12 - (original) word classes and explanations
    // 13 - (original) examples
    // 14 - (original) see also
    // at: [phrase, style, [[word_postproc, score, has_preceeding_space, attach_to_next_token]...]]

    std::cout << json_dom.dump(2) << std::endl;
    return json_dom.dump(2);
}

static inline uint32_t
genXr(uint32_t const a, char const* b)
{
    auto len = strlen(b);
    auto r = a;
    for (uint32_t c=0, d=0; c < len-2; c += 3) {
        d = static_cast<uint32_t>(b[c+2]);
        d = ('a' <= d)      ? (d - 87) : (d - 48);
        d = ('+' == b[c+1]) ? (r >> d) : (r << d);
        r = ('+' == b[c])   ? (r + d)  : (r ^ d);
    }
    return r;
}

static string
genTk(string const& text)
{
    char const* s = text.c_str();
    auto const tp = std::chrono::system_clock::now().time_since_epoch();
    auto const hr = std::chrono::duration_cast<std::chrono::hours>(tp);
    auto const tkk = static_cast<uint32_t>(hr.count());
    uint32_t a = tkk;
    for (size_t i = 0; i < strlen(s); i++) {
        a = genXr(a + static_cast<uint8_t const>(s[i]), "+-a^+6");
    }
    a = genXr(a, "+-3^+b+-f") % 1'000'000;
    return std::to_string(a) + "." + std::to_string(a ^ tkk);
}


// Request:(dt=..)
// at | alternatives (examples) table
// bd | ? browser detection
// ex | ?
// ld | language detection
// md | ?
// qc | w/o autocorrecting (qca -- with)
// rm | romanization (phonetics)
// rw | ?
// ss | ?
// t  | translation + raw
// Other:
// dj=1 | annotate all fields
// client= | {t,mt}:web, gtx:ext
// source= | {btn,baf}:web, {input,ls}:ext
// rom=1,srcrom=1 | additional romanization
// ssel=3,tsel=6 | web: pressed lang buttons from list
// ie=UTF-8,oe=UTF-8 | web: encoding
// WTF: {"otf", "1"}, {"kc", "7"},

string
Google::prepare(string const& text) const
{
    Web::parameters params = {
        {"client", "gtx"},   {"ie", "UTF-8"},   {"oe", "UTF-8"},
        {"dt", "t"},         {"dt", "rm"},      {"dt", "at"},
        {"sl", this->sl_},   {"tl", this->tl_}, {"hl", this->sl_},
        {"tk", genTk(text)}, {"q", text}};
    // THINK: Make url (beside text and tk) fixed at the moment of instantiation
    return this->url_ + "?" + this->composeParams(params);
}
