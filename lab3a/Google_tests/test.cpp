#include "gtest/gtest.h"
#include "bigNumber.h"

const double error = 0.0001;
using namespace Prog3a;

TEST(Constructors, Defaultconstructor) {
    bigDecNum A;
    ASSERT_EQ(0, A.ToInt());
}
TEST(Constructors, String_constructor) {
    char check1[] = "0000";
    bigDecNum A = bigDecNum(check1);
    ASSERT_EQ(0, A.ToInt());
    char check2[] = "-000";
    A = bigDecNum(check2);
    ASSERT_EQ(0, A.ToInt());
    char check3[] = "-34";
    A = bigDecNum(check3);
    ASSERT_EQ(-34, A.ToInt());
    char check4[] = "-0034";
    A = bigDecNum(check4);
    ASSERT_EQ(-34, A.ToInt());
    char check5[] = "aaa";
    ASSERT_ANY_THROW(bigDecNum C(check5));
    char check6[] = "1234567898765432345678998765434567890987654323456789098765434567898765456789";
    ASSERT_ANY_THROW(bigDecNum D(check6));
}
TEST(Constructors, Int_constructor) {
    bigDecNum A(9876);
    ASSERT_EQ(9876, A.ToInt());
    bigDecNum B(-423);
    ASSERT_EQ(-423, B.ToInt());
}
TEST(Methods, Additional_code) {
    bigDecNum A("0");
    A = A.AddCode();
    ASSERT_EQ(0, A.ToInt());
    bigDecNum B("11");
    B = B.AddCode();
    ASSERT_EQ(11,B.ToInt());
    bigDecNum C("-864");
    C = C.AddCode();
    ASSERT_EQ(-136, C.ToInt());
}
TEST(Methods, Sum) {
    bigDecNum A1("123");
    bigDecNum B1("768");
    bigDecNum Sum1 = A1.Sum(B1);
    ASSERT_EQ(891, Sum1.ToInt());
    bigDecNum A2("-123");
    bigDecNum B2("7686");
    bigDecNum Sum2 = A2.Sum(B2);
    ASSERT_EQ(7563, Sum2.ToInt());
    bigDecNum A3("123");
    bigDecNum B3("-7687686");
    bigDecNum Sum3 = A3.Sum(B3);
    ASSERT_EQ(-7687563, Sum3.ToInt());
    bigDecNum A4("999999999");
    bigDecNum B4("-7687686");
    bigDecNum Sum4 = A4.Sum(B4);
    ASSERT_EQ(992312313, Sum4.ToInt());
    bigDecNum A5("-123");
    bigDecNum B5("-7686");
    bigDecNum Sum5 = A5.Sum(B5);
    ASSERT_EQ(-7809, Sum5.ToInt());
    bigDecNum A6("0");
    bigDecNum B6("-76");
    bigDecNum Sum6 = A6.Sum(B6);
    ASSERT_EQ(-76, Sum6.ToInt());
    bigDecNum A7("1");
    bigDecNum B7("99999999999999999999999999999999999999999999999");
    ASSERT_ANY_THROW(A7.Sum(B7));
}
TEST(Methods, Subtruction) {
    bigDecNum A1("123");
    bigDecNum B1("768");
    bigDecNum Sub1 = A1.Subtraction(B1);
    ASSERT_EQ(-645, Sub1.ToInt());
    bigDecNum A2("123");
    bigDecNum B2("123");
    bigDecNum Sub2 = A2.Subtraction(B2);
    ASSERT_EQ(0, Sub2.ToInt());
    bigDecNum A3("-123");
    bigDecNum B3("7686");
    bigDecNum Sub3 = A3.Subtraction(B3);
    ASSERT_EQ(-7809, Sub3.ToInt());
    bigDecNum A4("123");
    bigDecNum B4("-7687686");
    bigDecNum Sub4 = A4.Subtraction(B4);
    ASSERT_EQ(7687809, Sub4.ToInt());
    bigDecNum A5("-999999999");
    bigDecNum B5("-7687686");
    bigDecNum Sub5 = A5.Subtraction(B5);
    ASSERT_EQ(-992312313, Sub5.ToInt());
    bigDecNum A6("-123");
    bigDecNum B6("-7686");
    bigDecNum Sub6 = A6.Subtraction(B6);
    ASSERT_EQ(7563, Sub6.ToInt());
    bigDecNum A7("0");
    bigDecNum B7("-76");
    bigDecNum Sub7 = A7.Subtraction(B7);
    ASSERT_EQ(76, Sub7.ToInt());
    bigDecNum A8("1");
    bigDecNum B8("-99999999999999999999999999999999999999999999999");
    ASSERT_ANY_THROW(A8.Subtraction(B8));
}
TEST(Methods, Increase) {
bigDecNum A("0");
A = A.Inc10();
ASSERT_EQ(0, A.ToInt());
bigDecNum B("11");
B = B.Inc10();
ASSERT_EQ(110, B.ToInt());
bigDecNum C("-864");
C = C.Inc10();
ASSERT_EQ(-8640, C.ToInt());
bigDecNum D("11111111111111111111111111111111111111111111111");
ASSERT_ANY_THROW(D.Inc10());
}
TEST(Methods, Decrease) {
    bigDecNum A("0");
    A = A.Dec10();
    ASSERT_EQ(0, A.ToInt());
    bigDecNum B("1");
    B = B.Dec10();
    ASSERT_EQ(0, B.ToInt());
    bigDecNum C("-864");
    C = C.Dec10();
    ASSERT_EQ(-86, C.ToInt());
    bigDecNum D("111");
    D = D.Dec10();
    ASSERT_EQ(11, D.ToInt());
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}