#ifndef FORESTANZA_MTL_WEB_GOOGLE_H
#define FORESTANZA_MTL_WEB_GOOGLE_H

#include "web.h"

#include <regex>

namespace mtl {

class Google : public Web
{
public:
    using regex = std::regex;

    Google();
    virtual ~Google() noexcept = default;
    // explicit Google(int){};

protected:
    virtual void init() override;
    virtual string prepare(string const& text) const override;
    virtual string parse(string const& response) const override;

private:
    string const url_ = "http://translate.googleapis.com/translate_a/single";
    // ALT:(prev) "https://translate.google.com/translate_a/single";
    // ALT:(old)  "translate.google.com/translate_a/t";

    regex re_skipped_null_ = regex(R"((,|\[)(?=,|\]))", regex::nosubs|regex::optimize);
};

} // namespace mtl

#endif // FORESTANZA_MTL_WEB_GOOGLE_H
