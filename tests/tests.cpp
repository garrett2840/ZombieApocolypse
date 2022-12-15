#include "gtest/gtest.h"
#include "denizen.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Denizen, CopyConstructor) {
    Denizen* oldDen = new Ignorant("Jake Smith");
    Denizen* newDen = new Alarmed(oldDen);
    EXPECT_EQ(newDen->getName(), "Jake Smith");
    EXPECT_EQ(newDen->getInfectionProb(), 25);
}