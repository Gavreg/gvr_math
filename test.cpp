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
        for (int i=0; i<9; ++i)
            EXPECT_EQ(v1[i], 0);
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

    }
}


