#include "gtest/gtest.h"
#include "Table.h"

const double error = 0.0001;
using namespace lab4;

TEST(Constructors, UnaryDefaultconstructor) {
    Unary A;
    ASSERT_EQ(A.getNumber(), 0);
    ASSERT_EQ(A.getNumGuests(), 1);
    ASSERT_EQ(A.getCost(), 5000);
    ASSERT_EQ(A.getType(), "Unary");
    ASSERT_EQ(A.isFree(), 1);

}
TEST(Constructors, LuxeDefaultconstructor) {
    Luxe A;
    ASSERT_EQ(A.getNumber(), 0);
    ASSERT_EQ(A.getNumGuests(), 1);
    ASSERT_EQ(A.getCost(), 15000);
    ASSERT_EQ(A.getType(), "Luxe");
    ASSERT_EQ(A.isFree(), 1);
    ASSERT_EQ(A.getRooms(), 2);
}
/*

TEST(Constructors, String_constructor) {
    char check1[] = "0000";
    bigNum A = bigNum(check1);
    ASSERT_EQ(0, (int)A);
    char check2[] = "-000";
    A = bigNum(check2);
    ASSERT_EQ(0, (int)A);
    char check3[] = "-21";
    A = bigNum(check3);
    ASSERT_EQ(-21, (int)A);
    char check4[] = "-0021";
    A = bigNum(check4);
    ASSERT_EQ(-21, (int)A);
    char check5[] = "aaa";
    ASSERT_ANY_THROW(bigNum C(check5));
}
TEST(Constructors, Int_constructor) {
    bigNum A(1405);
    ASSERT_EQ(1405, (int)A);
    bigNum B(-511);
    ASSERT_EQ(-511, (int)B);
}
TEST(Methods, Additional_code) {
    bigNum A("0");
    ASSERT_EQ(0, (int)~A);
    bigNum B("11");
    ASSERT_EQ(11,(int)~B);
    bigNum C("-2517");
    ASSERT_EQ(-7483, (int)~C);
}
TEST(Methods, Sum) {
    bigNum A1("123");
    bigNum B1("768");
    bigNum Sum1 = A1 + B1;
    ASSERT_EQ(891, (int)Sum1);
    bigNum A2("-123");
    bigNum B2("7686");
    bigNum Sum2 = A2 + B2;
    ASSERT_EQ(7563, (int)Sum2);
    bigNum A3("123");
    bigNum B3("-7687686");
    bigNum Sum3 = A3 + B3;
    ASSERT_EQ(-7687563, (int)Sum3);
    bigNum A4("999999999");
    bigNum B4("-7687686");
    bigNum Sum4 = A4 + B4;
    ASSERT_EQ(992312313, (int)Sum4);
    bigNum A5("-123");
    bigNum B5("-7686");
    bigNum Sum5 = A5 + B5;
    ASSERT_EQ(-7809, (int)Sum5);
    bigNum A6("0");
    bigNum B6("-76");
    bigNum Sum6 = A6 + B6;
    ASSERT_EQ(-76, (int)Sum6);
    Sum6 = bigNum(35) + A6 + B6 + bigNum("74") + bigNum(12);
    ASSERT_EQ(45, (int)Sum6);
}
TEST(Methods, Subtruction) {
    bigNum A1("123");
    bigNum B1("768");
    bigNum Sub1 = A1 - B1;
    ASSERT_EQ(-645, (int)Sub1);
    bigNum A2("123");
    bigNum B2("123");
    bigNum Sub2 = A2 - B2;
    ASSERT_EQ(0, (int)Sub2);
    bigNum A3("-123");
    bigNum B3("7686");
    bigNum Sub3 = A3 - B3;
    ASSERT_EQ(-7809, (int)Sub3);
    bigNum A4("123");
    bigNum B4("-7687686");
    bigNum Sub4 = A4 - B4;
    ASSERT_EQ(7687809, (int)Sub4);
    bigNum A5("-999999999");
    bigNum B5("-7687686");
    bigNum Sub5 = A5 - B5;
    ASSERT_EQ(-992312313, (int)Sub5);
    bigNum A6("-123");
    bigNum B6("-7686");
    bigNum Sub6 = A6 - B6;
    ASSERT_EQ(7563, (int)Sub6);
    bigNum A7("0");
    bigNum B7("-76");
    bigNum Sub7 = A7 - B7;
    ASSERT_EQ(76, (int)Sub7);
    Sub6 = bigNum(35) - A7 - B7 + bigNum("74") + bigNum(12);
    ASSERT_EQ(197, (int)Sub6);
}
TEST(Operators, Operator_minus) {
    bigNum A("0");
    ASSERT_EQ(0, (int)(-A));
    bigNum B(11);
    ASSERT_EQ(-11, (int)(-B));
    bigNum C(-1);
    ASSERT_EQ(1, (int)(-C));
}
TEST(Operators, Operator_move_left) {
    bigNum A("0");
    A <<= 2;
    ASSERT_EQ(0, (int)A);
    bigNum B("11");
    B<<=1;
    ASSERT_EQ(110, (int)B);
    bigNum C("-864");
    C<<=1;
    ASSERT_EQ(-8640, (int)C);
}
TEST(Methods, Decrease) {
    bigNum A("0");
    A>>=1;
    ASSERT_EQ(0, (int)A);
    bigNum B("1");
    B>>=1;
    ASSERT_EQ(0, (int)B);
    bigNum C("-864");
    C>>=1;
    ASSERT_EQ(-86, (int)C);
    bigNum D("111");
    D>>=1;
    ASSERT_EQ(11, (int)D);
    auto E = D >>= 1;
    ASSERT_EQ(1, (int)E);
}
TEST(Operators, Operator_compare) {
    bigNum A1("123");
    bigNum B1("141");
    ASSERT_EQ(true, A1 < B1);
    ASSERT_EQ(false, A1 > B1);
    ASSERT_EQ(false, A1 == B1);
    bigNum A2("3");
    bigNum B2("-31");
    ASSERT_EQ(true, A2 > B2);
    ASSERT_EQ(false, A2 < B2);
    ASSERT_EQ(false, A2 == B2);
    bigNum A3("-123");
    bigNum B3("-00000123");
    ASSERT_EQ(true, A3 == B3);
    ASSERT_EQ(false, A3 < B3);
    ASSERT_EQ(false, A3 > B3);
}
*/
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}