#include <functional>
#include <gtest/gtest.h>
#include "Vector.h"

using namespace gvr;

TEST(Vector, EmptyInit)
{
    {
        Vector<int, 0> v1;
        EXPECT_EQ(v1.size(), 0);
    }

    {
        Vector<double, 0> v1;
        EXPECT_EQ(v1.size(), 0);
    }

    {
        Vector<float, 0> v1;
        EXPECT_EQ(v1.size(), 0);
    }
    
}

TEST(Vector, ZeroInit)
{
    {
        Vector<int, 10> v1;
        for (int i=0; i<10; ++i)
            EXPECT_EQ(v1[i], 0);
    }
}

TEST(Vector, InitFromDigits)
{
    {
        Vector<int, 5> v{1, 2, 3, 4, 5};
        EXPECT_EQ(v[0], 1);
        EXPECT_EQ(v[1], 2);
        EXPECT_EQ(v[2], 3);
        EXPECT_EQ(v[3], 4);
        EXPECT_EQ(v[4], 5);

        EXPECT_EQ(v.size(), 5);
    }
    {
        Vector<int, 6> v{ 1, 2, 3 };
        EXPECT_EQ(v[0], 1);
        EXPECT_EQ(v[1], 2);
        EXPECT_EQ(v[2], 3);
        EXPECT_EQ(v[3], 0);
        EXPECT_EQ(v[4], 0);
        EXPECT_EQ(v[5], 0);

        EXPECT_EQ(v.size(), 6);
    }
}

TEST(Vector, InitFromVectorsAndDigits)
{
    {
        Vector<int, 2> v1{ 1, 2 };
        Vector<int, 3> v2{ 3, 4 }; //  должно быть как {3, 4 , 0}

        Vector<int, 5> v3{ v1,v2 };

        EXPECT_EQ(v3.size(), 5);

        EXPECT_EQ(v3[0], 1);
        EXPECT_EQ(v3[1], 2);
        EXPECT_EQ(v3[2], 3);
        EXPECT_EQ(v3[3], 4);
        EXPECT_EQ(v3[4], 0);

    }

    {
        Vector<int, 2> v1{ 10, 12 };
        Vector<int, 3> v2{ 20, 21, 30 };

        Vector<int, 6> v3{ v1,v2, 55 };

        EXPECT_EQ(v3.size(), 6);

        EXPECT_EQ(v3[0], 10);
        EXPECT_EQ(v3[1], 12);
        EXPECT_EQ(v3[2], 20);
        EXPECT_EQ(v3[3], 21);
        EXPECT_EQ(v3[4], 30);
        EXPECT_EQ(v3[5], 55);

    }

}

TEST(Vector, Access_to_elements)
{
    {
        Vector<int, 100> v1{};
        //заполняю
        for (int i = 0; i < 100; ++i)
        {
            v1[i] = i;
        }
        //проверяю
        for (int i = 0; i < 100; ++i)
        {
            EXPECT_EQ(v1[i],  i);
        }

    }

    {
        const Vector<int, 5> v1{ 1,2,3,4,-5 };
        EXPECT_EQ(v1[0], 1);
        EXPECT_EQ(v1[1], 2);
        EXPECT_EQ(v1[2], 3);
        EXPECT_EQ(v1[3], 4);
        EXPECT_EQ(v1[4], -5);

    }
}



TEST(Vector, copy)
{
    {
        Vector<int, 5> v1 = { 1,2,30,4,5 };
        auto v2 = v1;

        EXPECT_EQ(v2[0], 1);
        EXPECT_EQ(v2[1], 2);
        EXPECT_EQ(v2[2], 30);
        EXPECT_EQ(v2[3], 4);
        EXPECT_EQ(v2[4], 5);

        EXPECT_EQ(v2.size(), 5);
    }
}

TEST(Vector, Sum)
{
    {
        Vector<int, 7> v1{ 1, 2, 3, 4, 5, 100,0 };
		Vector<int, 7> v2{ 10,11,12,13,14 , -10, 0 };
        
		auto v3 = v1 + v2;

        EXPECT_EQ(v3[0], 11);
        EXPECT_EQ(v3[1], 13);
        EXPECT_EQ(v3[2], 15);
        EXPECT_EQ(v3[3], 17);
        EXPECT_EQ(v3[4], 19);
        EXPECT_EQ(v3[5], 90);
        EXPECT_EQ(v3[6], 0);

        EXPECT_EQ(v3.size(), 7);

    }
}

TEST(Vector, Sub)
{
    {
        Vector<int, 5> v1{ 21, 0,  -10, -10, 4};
        Vector<int, 5> v2{ 7, 1000, 8,  90,  4};

        auto v3 = v1 - v2;

        EXPECT_EQ(v3[0], 14);
        EXPECT_EQ(v3[1], -1000);
        EXPECT_EQ(v3[2], -18);
        EXPECT_EQ(v3[3], -100);
        EXPECT_EQ(v3[4], 0);

        EXPECT_EQ(v3.size(), 5);
    }
}

TEST(Vector, L1Norm)
{
    {
        Vector<int, 5> v1{ 1,2,3,4,5 };
        EXPECT_EQ(v1.L1Norm(), 15);
    }

    {
        Vector<int, 6> v1{ 1,-2,3,-4,5,10 };
        EXPECT_EQ(v1.L1Norm(), 25);
    }

    {
        Vector<int, 60> v1{ -8};
        EXPECT_EQ(v1.L1Norm(), 8);
    }
}





TEST(Vector, L2Norm)
{    
    
    {
        Vector<double, 2> v{ 2,4 };
        EXPECT_DOUBLE_EQ(v.L2Norm(), sqrt(2 * 2 + 4 * 4));
    }

    {
        Vector<int, 3> v{ 0, -8, 9 };
        EXPECT_DOUBLE_EQ(v.L2Norm(), sqrt(-8*-8 + 9*9));
    }

       

}


