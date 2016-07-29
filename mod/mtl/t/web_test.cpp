#include "mtl.h"

#include <gtest/gtest.h>

std::string const text{"ハジメ達が転移した"};
std::string const sl{"ja"};
std::string const tl{"en"};

TEST(mtl, apertium) {
    ASSERT_EQ(0, apertium("siempre que eres", "es", tl));
}

TEST(mtl, baidu) {
    ASSERT_EQ(0, baidu(text, sl, tl));
}
