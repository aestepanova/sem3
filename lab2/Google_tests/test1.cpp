#include "gtest/gtest.h"
#include "Lemniscate.h"

const double error = 0.0001;
TEST(LemniscateConstructor, DefaultConstructor) {
    Prog2::Lemniscate a;
    ASSERT_EQ(1, a.getFocus());
}
TEST(LemniscateConstructor, InitConstructor) {
    Prog2::Lemniscate f(3);
    Prog2::Lemniscate f1(-3);
    ASSERT_EQ(3, f.getFocus());
    ASSERT_EQ(3, f1.getFocus());
    ASSERT_ANY_THROW(Prog2::Lemniscate f(0));
}
TEST(LemniscateMethods, Setters) {
    Prog2::Lemniscate f;
    f.setFocus(5);
    ASSERT_EQ(5, f.getFocus());
    ASSERT_ANY_THROW(f.setFocus(0));
}
TEST(LemniscateMethods, Getters) {
    Prog2::Lemniscate f(5);
    ASSERT_EQ(10, f.focusDist());
    ASSERT_NEAR(5 * sqrt(2), f.rad(), error);
}
TEST(LemniscateMethods, Curvature) {
    Prog2::Lemniscate f(5);
    ASSERT_NEAR(4.0303, f.radAngle(35), error);
    ASSERT_ANY_THROW(f.radAngle(112));
    ASSERT_NEAR(5.55556, f.radRad(3), error);
    ASSERT_ANY_THROW(f.radRad(35));
    ASSERT_ANY_THROW(f.radRad(-3));
}
TEST(LemniscateMethods, SectorArea) {
    Prog2::Lemniscate f(5);
    ASSERT_NEAR(11.74616, f.sectorArea(35), error);
    ASSERT_NEAR(13.25384, f.sectorArea(145), error);
    ASSERT_NEAR(25, f.sectorArea(180), error);
    ASSERT_ANY_THROW(f.sectorArea(-70));
}
TEST(LemniscateMethods, Polardist) {
    Prog2::Lemniscate f(4);
    ASSERT_ANY_THROW(f.polarDist(-1));
    ASSERT_ANY_THROW(f.polarDist(60));
    ASSERT_ANY_THROW(f.polarDist(270));
    ASSERT_NEAR(5.6568542494, f.polarDist(180), error);
    ASSERT_NEAR(5.48363, f.polarDist(10), error);
}
TEST(LemniscateMethods, S) {
    Prog2::Lemniscate f(3);
    ASSERT_NEAR(18, f.area(), error);
}
TEST(LemniscateMethods, formula) {
    Prog2::Lemniscate f(5);
    ASSERT_STRCASEEQ("(x^2 + y^2)^2 = 2*5^2 * (x^2 - y^2)", f.formula().c_str());
    f.setFocus(-5);
    ASSERT_STRCASEEQ("(x^2 + y^2)^2 = 2*5^2 * (x^2 - y^2)", f.formula().c_str());
}

int _tmain(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
