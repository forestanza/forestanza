#ifndef FORESTANZA_MTL_WEB_H
#define FORESTANZA_MTL_WEB_H

#include "mtl/api.h"

#include <curl_easy.h>

#include <sstream>
#include <vector>
#include <utility>

namespace mtl {

class Web : public Mtl
{
public:
    using parameters = std::vector<std::pair<const string, const string>> const;
    Web() = default;
    virtual ~Web() = default;

    virtual string escape(string const& s) const final;
    virtual string composeParams(parameters& params) const;
    virtual string perform(string const& query);

protected:
    std::ostringstream stream_;
    curl::curl_ios<std::ostringstream> writer_{stream_};
    curl::curl_easy session_{writer_};

    string const agent_ = "Mozilla/5.0 (X11; Linux x86_64) ";
    // ALT "Mozilla/5.0 (Windows NT 6.1; rv:38.0) Gecko/20100101 Firefox/38.0";
    // ALT "Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko"

private:

};

} // namespace mtl

#endif // FORESTANZA_MTL_WEB_H
