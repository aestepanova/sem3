#include "gtest/gtest.h"
#include "bigNum.h"

const double error = 0.0001;
using namespace Prog3b;

TEST(Constructors, Defaultconstructor) {
    bigDecNum A;
    ASSERT_EQ(0, (int)A);
}
TEST(Constructors, String_constructor) {
    char check1[] = "0000";
    bigDecNum A = bigDecNum(check1);
    ASSERT_EQ(0, (int)A);
    char check2[] = "-000";
    A = bigDecNum(check2);
    ASSERT_EQ(0, (int)A);
    char check3[] = "-21";
    A = bigDecNum(check3);
    ASSERT_EQ(-21, (int)A);
    char check4[] = "-0021";
    A = bigDecNum(check4);
    ASSERT_EQ(-21, (int)A);
    char check5[] = "aaa";
    ASSERT_ANY_THROW(bigDecNum C(check5));
    char check6[] = "1234567898765432345678998765434567890987654323456789098765434567898765456789";
    ASSERT_ANY_THROW(bigDecNum D(check6));
}
TEST(Constructors, Int_constructor) {
    bigDecNum A(1405);
    ASSERT_EQ(1405, (int)A);
    bigDecNum B(-511);
    ASSERT_EQ(-511, (int)B);
}
TEST(Methods, Additional_code) {
    bigDecNum A("0");
    ASSERT_EQ(0, (int)~A);
    bigDecNum B("11");
    ASSERT_EQ(11,(int)~B);
    bigDecNum C("-2517");
    ASSERT_EQ(-7483, (int)~C);
}
TEST(Methods, Sum) {
    bigDecNum A1("123");
    bigDecNum B1("768");
    bigDecNum Sum1 = A1 + B1;
    ASSERT_EQ(891, (int)Sum1);
    bigDecNum A2("-123");
    bigDecNum B2("7686");
    bigDecNum Sum2 = A2 + B2;
    ASSERT_EQ(7563, (int)Sum2);
    bigDecNum A3("123");
    bigDecNum B3("-7687686");
    bigDecNum Sum3 = A3 + B3;
    ASSERT_EQ(-7687563, (int)Sum3);
    bigDecNum A4("999999999");
    bigDecNum B4("-7687686");
    bigDecNum Sum4 = A4 + B4;
    ASSERT_EQ(992312313, (int)Sum4);
    bigDecNum A5("-123");
    bigDecNum B5("-7686");
    bigDecNum Sum5 = A5 + B5;
    ASSERT_EQ(-7809, (int)Sum5);
    bigDecNum A6("0");
    bigDecNum B6("-76");
    bigDecNum Sum6 = A6 + B6;
    ASSERT_EQ(-76, (int)Sum6);
    bigDecNum A7("1");
    bigDecNum B7("99999999999999999999999999999999999999999999999");
    ASSERT_ANY_THROW(A7+B7);
}
TEST(Methods, Subtruction) {
    bigDecNum A1("123");
    bigDecNum B1("768");
    bigDecNum Sub1 = A1 - B1;
    ASSERT_EQ(-645, (int)Sub1);
    bigDecNum A2("123");
    bigDecNum B2("123");
    bigDecNum Sub2 = A2 - B2;
    ASSERT_EQ(0, (int)Sub2);
    bigDecNum A3("-123");
    bigDecNum B3("7686");
    bigDecNum Sub3 = A3 - B3;
    ASSERT_EQ(-7809, (int)Sub3);
    bigDecNum A4("123");
    bigDecNum B4("-7687686");
    bigDecNum Sub4 = A4 - B4;
    ASSERT_EQ(7687809, (int)Sub4);
    bigDecNum A5("-999999999");
    bigDecNum B5("-7687686");
    bigDecNum Sub5 = A5 - B5;
    ASSERT_EQ(-992312313, (int)Sub5);
    bigDecNum A6("-123");
    bigDecNum B6("-7686");
    bigDecNum Sub6 = A6 - B6;
    ASSERT_EQ(7563, (int)Sub6);
    bigDecNum A7("0");
    bigDecNum B7("-76");
    bigDecNum Sub7 = A7 - B7;
    ASSERT_EQ(76, (int)Sub7);
    bigDecNum A8("1");
    bigDecNum B8("-99999999999999999999999999999999999999999999999");
    ASSERT_ANY_THROW(A8 - B8);
}
TEST(Methods, Increase) {
    bigDecNum A("0");
    A>>=1;
    ASSERT_EQ(0, (int)A);
    bigDecNum B("11");
    B>>=1;
    ASSERT_EQ(110, (int)B);
    bigDecNum C("-864");
    C>>=1;
    ASSERT_EQ(-8640, (int)C);
    bigDecNum D("11111111111111111111111111111111111111111111111");
    ASSERT_ANY_THROW(D>>=1);
}
TEST(Methods, Decrease) {
    bigDecNum A("0");
    A<<=1;
    ASSERT_EQ(0, (int)A);
    bigDecNum B("1");
    B<<=1;
    ASSERT_EQ(0, (int)B);
    bigDecNum C("-864");
    C<<=1;
    ASSERT_EQ(-86, (int)C);
    bigDecNum D("111");
    D<<=1;
    ASSERT_EQ(11, (int)D);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}