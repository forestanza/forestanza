#include "mtl/api.h"

using mtl::Mtl;
using std::string;

void
Mtl::setLang(string const& sl, string const& tl)
{
    // DEV: exception if impossible lang pair
    this->sl_ = sl;
    this->tl_ = tl;
}

string
Mtl::translate(string const& text)
{
    auto query = this->prepare(text);
    auto response = this->perform(query);
    auto data = this->parse(response);
    return std::move(data);
}
