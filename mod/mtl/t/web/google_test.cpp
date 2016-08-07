#include "web/google.h"
#include "mtl/api.h"

#include <gtest/gtest.h>

TEST(mtl, google) {
    mtl::Google mtl;
    mtl.setLang("ja", "en");
    auto t = mtl.translate("私");
    std::cout << t << std::endl;
}
