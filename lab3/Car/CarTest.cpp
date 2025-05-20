#include "Car.h"
#include <gtest/gtest.h>

std::ostringstream oss;

TEST(CarTest, InitialState)
{
    Car car(oss);
    ASSERT_FALSE(car.IsTurnedOn());
    ASSERT_EQ(car.GetGear(), 0);
    ASSERT_EQ(car.GetSpeed(), 0);
}

TEST(CarTest, EngineOnOff)
{
    Car car(oss);

    ASSERT_TRUE(car.TurnOnEngine());
    ASSERT_TRUE(car.IsTurnedOn());

    ASSERT_TRUE(car.TurnOffEngine());
    ASSERT_FALSE(car.IsTurnedOn());
}

TEST(CarTest, EngineTurnOffWhileMoving)
{
    Car car(oss);
    car.TurnOnEngine();

    ASSERT_TRUE(car.SetGear(1));
    ASSERT_TRUE(car.SetSpeed(20));
    ASSERT_EQ(car.GetSpeed(), 20);

    ASSERT_FALSE(car.TurnOffEngine());
    ASSERT_TRUE(car.IsTurnedOn());

    ASSERT_TRUE(car.SetSpeed(0));

    ASSERT_FALSE(car.TurnOffEngine());
    ASSERT_TRUE(car.IsTurnedOn());

    ASSERT_TRUE(car.SetGear(1));
    ASSERT_TRUE(car.SetSpeed(20));
    ASSERT_EQ(car.GetSpeed(), 20);
    ASSERT_TRUE(car.SetSpeed(0));
    ASSERT_EQ(car.GetSpeed(), 0);

    ASSERT_FALSE(car.TurnOffEngine());
    ASSERT_TRUE(car.IsTurnedOn());

    ASSERT_TRUE(car.SetGear(0));
    ASSERT_TRUE(car.SetSpeed(0));

    ASSERT_TRUE(car.TurnOffEngine());
    ASSERT_FALSE(car.IsTurnedOn());
}

TEST(CarTest, ReverseGearSpeedChange)
{
    Car car(oss);
    car.TurnOnEngine();

    ASSERT_TRUE(car.SetGear(-1));
    ASSERT_TRUE(car.SetSpeed(0));
    ASSERT_EQ(car.GetSpeed(), 0);
    ASSERT_TRUE(car.SetSpeed(1));
    ASSERT_EQ(car.GetSpeed(), 1);
    ASSERT_FALSE(car.SetSpeed(-1));
    ASSERT_EQ(car.GetSpeed(), 1);
    ASSERT_TRUE(car.SetSpeed(20));
    ASSERT_EQ(car.GetSpeed(), 20);
    ASSERT_TRUE(car.SetSpeed(19));
    ASSERT_EQ(car.GetSpeed(), 19);
    ASSERT_FALSE(car.SetSpeed(21));
}

TEST(CarTest, FirstGearSpeedChange)
{
    Car car(oss);
    car.TurnOnEngine();

    ASSERT_TRUE(car.SetGear(1));
    ASSERT_TRUE(car.SetSpeed(0));
    ASSERT_EQ(car.GetSpeed(), 0);
    ASSERT_TRUE(car.SetSpeed(1));
    ASSERT_EQ(car.GetSpeed(), 1);
    ASSERT_FALSE(car.SetSpeed(-1));
    ASSERT_TRUE(car.SetSpeed(30));
    ASSERT_EQ(car.GetSpeed(), 30);
    ASSERT_TRUE(car.SetSpeed(29));
    ASSERT_EQ(car.GetSpeed(), 29);
    ASSERT_FALSE(car.SetSpeed(31));
    ASSERT_EQ(car.GetSpeed(), 29);
}

TEST(CarTest, SecondGearSpeedChange)
{
    Car car(oss);
    car.TurnOnEngine();
    car.SetGear(1);
    car.SetSpeed(20);

    ASSERT_TRUE(car.SetGear(2));
    ASSERT_TRUE(car.SetSpeed(20));
    ASSERT_EQ(car.GetSpeed(), 20);
    ASSERT_TRUE(car.SetSpeed(21));
    ASSERT_EQ(car.GetSpeed(), 21);
    ASSERT_FALSE(car.SetSpeed(19));
    ASSERT_EQ(car.GetSpeed(), 21);
    ASSERT_TRUE(car.SetSpeed(50));
    ASSERT_EQ(car.GetSpeed(), 50);
    ASSERT_TRUE(car.SetSpeed(49));
    ASSERT_EQ(car.GetSpeed(), 49);
    ASSERT_FALSE(car.SetSpeed(51));
    ASSERT_EQ(car.GetSpeed(), 49);
}

TEST(CarTest, ThirdGearSpeedChange)
{
    Car car(oss);
    car.TurnOnEngine();
    car.SetGear(1);
    car.SetSpeed(20);
    car.SetGear(2);
    car.SetSpeed(50);

    ASSERT_TRUE(car.SetGear(3));
    ASSERT_TRUE(car.SetSpeed(30));
    ASSERT_EQ(car.GetSpeed(), 30);
    ASSERT_TRUE(car.SetSpeed(31));
    ASSERT_EQ(car.GetSpeed(), 31);
    ASSERT_FALSE(car.SetSpeed(29));
    ASSERT_EQ(car.GetSpeed(), 31);
    ASSERT_TRUE(car.SetSpeed(60));
    ASSERT_EQ(car.GetSpeed(), 60);
    ASSERT_TRUE(car.SetSpeed(59));
    ASSERT_EQ(car.GetSpeed(), 59);
    ASSERT_FALSE(car.SetSpeed(61));
    ASSERT_EQ(car.GetSpeed(), 59);
}

TEST(CarTest, FourthGearSpeedChange)
{
    Car car(oss);
    car.TurnOnEngine();
    car.SetGear(1);
    car.SetSpeed(20);
    car.SetGear(2);
    car.SetSpeed(50);
    car.SetGear(3);
    car.SetSpeed(60);

    ASSERT_TRUE(car.SetGear(4));
    ASSERT_TRUE(car.SetSpeed(40));
    ASSERT_EQ(car.GetSpeed(), 40);
    ASSERT_TRUE(car.SetSpeed(41));
    ASSERT_EQ(car.GetSpeed(), 41);
    ASSERT_FALSE(car.SetSpeed(39));
    ASSERT_EQ(car.GetSpeed(), 41);
    ASSERT_TRUE(car.SetSpeed(90));
    ASSERT_EQ(car.GetSpeed(), 90);
    ASSERT_TRUE(car.SetSpeed(89));
    ASSERT_EQ(car.GetSpeed(), 89);
    ASSERT_FALSE(car.SetSpeed(91));
    ASSERT_EQ(car.GetSpeed(), 89);
}

TEST(CarTest, FifthGearSpeedChange)
{
    Car car(oss);
    car.TurnOnEngine();
    car.SetGear(1);
    car.SetSpeed(20);
    car.SetGear(2);
    car.SetSpeed(50);
    car.SetGear(3);
    car.SetSpeed(60);
    car.SetGear(4);
    car.SetSpeed(90);

    ASSERT_TRUE(car.SetGear(5));
    ASSERT_TRUE(car.SetSpeed(50));
    ASSERT_EQ(car.GetSpeed(), 50);
    ASSERT_TRUE(car.SetSpeed(51));
    ASSERT_EQ(car.GetSpeed(), 51);
    ASSERT_FALSE(car.SetSpeed(49));
    ASSERT_EQ(car.GetSpeed(), 51);
    ASSERT_TRUE(car.SetSpeed(150));
    ASSERT_EQ(car.GetSpeed(), 150);
    ASSERT_TRUE(car.SetSpeed(149));
    ASSERT_EQ(car.GetSpeed(), 149);
    ASSERT_FALSE(car.SetSpeed(151));
    ASSERT_EQ(car.GetSpeed(), 149);
}

TEST(CarTest, ReverseDirection)
{
    Car car(oss);
    car.TurnOnEngine();

    ASSERT_TRUE(car.SetGear(1));
    ASSERT_TRUE(car.SetSpeed(10));
    ASSERT_FALSE(car.SetGear(-1));
    ASSERT_TRUE(car.SetGear(0));
    ASSERT_FALSE(car.SetGear(-1));
    ASSERT_TRUE(car.SetSpeed(0));
    ASSERT_TRUE(car.SetGear(-1));
    ASSERT_TRUE(car.SetSpeed(10));
    ASSERT_FALSE(car.SetGear(1));
    ASSERT_TRUE(car.SetGear(0));
}

TEST(CarTest, GearShift)
{
    Car car(oss);
    car.TurnOnEngine();

    ASSERT_FALSE(car.SetGear(-2));
    ASSERT_TRUE(car.SetGear(0));
    car.SetGear(1);
    car.SetSpeed(20);
    car.SetGear(2);
    car.SetSpeed(50);
    car.SetGear(3);
    car.SetSpeed(60);
    car.SetGear(4);
    car.SetSpeed(90);
    car.SetGear(5);
    car.SetSpeed(150);
    ASSERT_FALSE(car.SetGear(6));
}

TEST(CarTest, FirstGearShift)
{
    Car car(oss);
    car.TurnOnEngine();
    car.SetGear(1);

    ASSERT_TRUE(car.SetSpeed(29));
    ASSERT_TRUE(car.SetGear(1));
    ASSERT_EQ(car.GetGear(), 1);
    ASSERT_TRUE(car.SetSpeed(30));
    ASSERT_TRUE(car.SetGear(1));
    ASSERT_EQ(car.GetGear(), 1);
    ASSERT_TRUE(car.SetGear(2));
    ASSERT_EQ(car.GetGear(), 2);
    ASSERT_TRUE(car.SetSpeed(31));
    ASSERT_FALSE(car.SetGear(1));
    ASSERT_EQ(car.GetGear(), 2);
}

TEST(CarTest, SecondGearShift)
{
    Car car(oss);
    car.TurnOnEngine();
    car.SetGear(1);

    ASSERT_TRUE(car.SetSpeed(19));
    ASSERT_FALSE(car.SetGear(2));
    ASSERT_EQ(car.GetGear(), 1);
    ASSERT_TRUE(car.SetSpeed(20));
    ASSERT_TRUE(car.SetGear(2));
    ASSERT_EQ(car.GetGear(), 2);
    ASSERT_TRUE(car.SetSpeed(21));
    ASSERT_TRUE(car.SetGear(2));
    ASSERT_EQ(car.GetGear(), 2);

    ASSERT_TRUE(car.SetSpeed(49));
    ASSERT_TRUE(car.SetGear(2));
    ASSERT_EQ(car.GetGear(), 2);
    ASSERT_TRUE(car.SetSpeed(50));
    ASSERT_TRUE(car.SetGear(2));
    ASSERT_EQ(car.GetGear(), 2);
    ASSERT_TRUE(car.SetGear(3));
    ASSERT_EQ(car.GetGear(), 3);
    ASSERT_TRUE(car.SetSpeed(51));
    ASSERT_FALSE(car.SetGear(2));
    ASSERT_EQ(car.GetGear(), 3);
}

TEST(CarTest, ThirdGearShift)
{
    Car car(oss);
    car.TurnOnEngine();
    car.SetGear(1);

    ASSERT_TRUE(car.SetSpeed(29));
    ASSERT_FALSE(car.SetGear(3));
    ASSERT_EQ(car.GetGear(), 1);
    ASSERT_TRUE(car.SetSpeed(30));
    ASSERT_TRUE(car.SetGear(3));
    ASSERT_EQ(car.GetGear(), 3);
    ASSERT_TRUE(car.SetGear(2));
    ASSERT_EQ(car.GetGear(), 2);
    ASSERT_TRUE(car.SetSpeed(31));
    ASSERT_TRUE(car.SetGear(3));
    ASSERT_EQ(car.GetGear(), 3);

    ASSERT_TRUE(car.SetSpeed(59));
    ASSERT_TRUE(car.SetGear(3));
    ASSERT_EQ(car.GetGear(), 3);
    ASSERT_TRUE(car.SetSpeed(60));
    ASSERT_TRUE(car.SetGear(3));
    ASSERT_EQ(car.GetGear(), 3);
    ASSERT_TRUE(car.SetGear(4));
    ASSERT_EQ(car.GetGear(), 4);
    ASSERT_TRUE(car.SetSpeed(61));
    ASSERT_FALSE(car.SetGear(3));
    ASSERT_EQ(car.GetGear(), 4);
}

TEST(CarTest, FourthGearShift)
{
    Car car(oss);
    car.TurnOnEngine();
    car.SetGear(1);
    car.SetSpeed(20);
    car.SetGear(2);
    car.SetSpeed(50);

    ASSERT_TRUE(car.SetGear(3));
    ASSERT_EQ(car.GetGear(), 3);
    ASSERT_TRUE(car.SetSpeed(39));
    ASSERT_FALSE(car.SetGear(4));
    ASSERT_EQ(car.GetGear(), 3);
    ASSERT_TRUE(car.SetSpeed(40));
    ASSERT_TRUE(car.SetGear(4));
    ASSERT_EQ(car.GetGear(), 4);
    ASSERT_TRUE(car.SetGear(3));
    ASSERT_EQ(car.GetGear(), 3);
    ASSERT_TRUE(car.SetSpeed(41));
    ASSERT_TRUE(car.SetGear(4));
    ASSERT_EQ(car.GetGear(), 4);

    car.SetGear(3);
    car.SetSpeed(60);
    car.SetGear(5);

    ASSERT_TRUE(car.SetSpeed(89));
    ASSERT_TRUE(car.SetGear(4));
    ASSERT_EQ(car.GetGear(), 4);
    ASSERT_TRUE(car.SetSpeed(90));
    ASSERT_TRUE(car.SetGear(4));
    ASSERT_EQ(car.GetGear(), 4);
    ASSERT_TRUE(car.SetGear(5));
    ASSERT_EQ(car.GetGear(), 5);
    ASSERT_TRUE(car.SetSpeed(91));
    ASSERT_FALSE(car.SetGear(4));
    ASSERT_EQ(car.GetGear(), 5);
}

TEST(CarTest, FifthGearShift)
{
    Car car(oss);
    car.TurnOnEngine();
    car.SetGear(1);
    car.SetSpeed(20);
    car.SetGear(2);
    car.SetSpeed(50);
    car.SetGear(3);
    car.SetSpeed(60);
    car.SetGear(4);
    car.SetSpeed(90);

    ASSERT_TRUE(car.SetGear(4));
    ASSERT_EQ(car.GetGear(), 4);
    ASSERT_TRUE(car.SetSpeed(49));
    ASSERT_FALSE(car.SetGear(5));
    ASSERT_EQ(car.GetGear(), 4);
    ASSERT_TRUE(car.SetSpeed(50));
    ASSERT_TRUE(car.SetGear(5));
    ASSERT_EQ(car.GetGear(), 5);
    ASSERT_TRUE(car.SetGear(4));
    ASSERT_EQ(car.GetGear(), 4);
    ASSERT_TRUE(car.SetSpeed(51));
    ASSERT_TRUE(car.SetGear(5));
    ASSERT_EQ(car.GetGear(), 5);

    ASSERT_TRUE(car.SetSpeed(149));
    ASSERT_TRUE(car.SetGear(5));
    ASSERT_EQ(car.GetGear(), 5);
    ASSERT_TRUE(car.SetSpeed(150));
    ASSERT_TRUE(car.SetGear(5));
    ASSERT_EQ(car.GetGear(), 5);
    ASSERT_FALSE(car.SetSpeed(151));
    ASSERT_FALSE(car.SetSpeed(6));
    ASSERT_EQ(car.GetGear(), 5);
}

TEST(CarTest, ChangeSpeedOnNeutralGear)
{
    Car car(oss);
    car.TurnOnEngine();

    car.SetGear(1);
    car.SetSpeed(20);
    car.SetGear(0);

    ASSERT_FALSE(car.SetSpeed(21));
    ASSERT_TRUE(car.SetSpeed(20));
    ASSERT_TRUE(car.SetSpeed(19));
}

TEST(CarTest, NegativeSpeed)
{
    Car car(oss);
    car.TurnOnEngine();

    ASSERT_FALSE(car.SetSpeed(-10));
    ASSERT_TRUE(car.SetGear(1));
    ASSERT_FALSE(car.SetSpeed(-10));
}

GTEST_API_ int main(int argc, char** argv)
{
    oss << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}