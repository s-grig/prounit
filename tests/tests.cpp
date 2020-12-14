#include <drawer.hpp>
#include <gtest/gtest.h> 

TEST(Draw, lin) {
	std::vector<double> x_vec_, y_vec_;
	x_vec_ = { 15, 20, 25, 30 };
	y_vec_ = { 15, 20, 25, 30 };
	drawer obj;
	obj.set_linear();
	obj.set_test();
	obj.cicle(x_vec_, y_vec_);
	EXPECT_EQ(obj.get_limit_x0(), -31.5);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}