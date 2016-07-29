#ifndef FORESTANZA_MTL_API_H
#define FORESTANZA_MTL_API_H

#include <string>

namespace mtl {

class Mtl
{
public:
    using string = std::string;

    Mtl() = default;
    Mtl(Mtl const&) = default;
    Mtl(Mtl&&) = default;
    virtual ~Mtl() = default;

    Mtl& operator=(const Mtl&) = default;
    Mtl& operator=(Mtl&&) = default;
    // explicit Mtl(string){};

    virtual void setLang(string const& sl, string const& tl);
    virtual string translate(string const& text);

protected:
    virtual void init() = 0;
    virtual string prepare(string const& text) const = 0;
    virtual string perform(string const& query) = 0;
    virtual string parse(string const& response) const = 0;

    string sl_ = "ja";
    string tl_ = "en";
};

} // namespace mtl

#endif // FORESTANZA_MTL_API_H
