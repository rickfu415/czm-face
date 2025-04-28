#include <gtest/gtest.h>
#include "core.hpp"

TEST(CoreTest, VersionCheck) {
    corecode::Core core;
    EXPECT_EQ(core.getVersion(), "0.1.0");
} 