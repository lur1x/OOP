#include <gtest/gtest.h>
#include "..\TVSet.h"
// 1. Тесты для включения/выключения
TEST(TVSet, IsInitiallyTurnedOff) {
TVSet tv;
ASSERT_FALSE(tv.IsTurnedOn());
}

TEST(TVSet, CanTurnOn) {
TVSet tv;
tv.TurnOn();
ASSERT_TRUE(tv.IsTurnedOn());
}

TEST(TVSet, CanTurnOff) {
TVSet tv;
tv.TurnOn();
tv.TurnOff();
ASSERT_FALSE(tv.IsTurnedOn());
}

// 2. Тесты для работы с каналами
TEST(TVSet, InitiallySetToChannel1) {
TVSet tv;
tv.TurnOn();
ASSERT_EQ(tv.GetChannel(), 1);
}

TEST(TVSet, SelectChannelValidRange) {
TVSet tv;
tv.TurnOn();
ASSERT_TRUE(tv.SelectChannel(42));
ASSERT_EQ(tv.GetChannel(), 42);
}

TEST(TVSet, SelectChannelInvalidRange) {
TVSet tv;
tv.TurnOn();
ASSERT_FALSE(tv.SelectChannel(0));
ASSERT_FALSE(tv.SelectChannel(100));
ASSERT_EQ(tv.GetChannel(), 1); // Остается на текущем канале
}

TEST(TVSet, CantSelectChannelWhenTurnedOff) {
TVSet tv;
ASSERT_FALSE(tv.SelectChannel(5));
ASSERT_EQ(tv.GetChannel(), 0); // 0 означает выключенное состояние
}

// 3. Тесты для предыдущего канала
TEST(TVSet, RememberPreviousChannel) {
TVSet tv;
tv.TurnOn();
tv.SelectChannel(10);
tv.SelectChannel(20);
ASSERT_TRUE(tv.SelectPreviousChannel());
ASSERT_EQ(tv.GetChannel(), 10);
}

TEST(TVSet, CantSelectPreviousChannelWhenNoHistory) {
TVSet tv;
tv.TurnOn();
ASSERT_FALSE(tv.SelectPreviousChannel());
}

// 4. Тесты для имен каналов
TEST(TVSet, SetChannelName) {
TVSet tv;
tv.TurnOn();
ASSERT_TRUE(tv.SetChannelName(5, "Discovery"));
ASSERT_EQ(tv.GetChannelName(5), "Discovery");
ASSERT_EQ(tv.GetChannelByName("Discovery"), 5);
}

TEST(TVSet, SetChannelNameInvalid) {
TVSet tv;
tv.TurnOn();
ASSERT_FALSE(tv.SetChannelName(0, "Invalid")); // Неверный номер канала
ASSERT_FALSE(tv.SetChannelName(5, ""));       // Пустое имя
}

TEST(TVSet, SelectChannelByName) {
TVSet tv;
tv.TurnOn();
tv.SetChannelName(5, "Discovery");
ASSERT_TRUE(tv.SelectChannel("Discovery"));
ASSERT_EQ(tv.GetChannel(), 5);
}

TEST(TVSet, DeleteChannelName) {
TVSet tv;
tv.TurnOn();
tv.SetChannelName(5, "Discovery");
ASSERT_TRUE(tv.DeleteChannelName("Discovery"));
ASSERT_EQ(tv.GetChannelByName("Discovery"), 0);
}

// 5. Интеграционные тесты
TEST(TVSet, ComplexScenario) {
TVSet tv;

// Включаем и проверяем начальное состояние
tv.TurnOn();
ASSERT_TRUE(tv.IsTurnedOn());
ASSERT_EQ(tv.GetChannel(), 1);

// Устанавливаем имя канала
ASSERT_TRUE(tv.SetChannelName(3, "CNN"));

// Переключаемся по имени
ASSERT_TRUE(tv.SelectChannel("CNN"));
ASSERT_EQ(tv.GetChannel(), 3);

// Переключаемся по номеру
ASSERT_TRUE(tv.SelectChannel(5));
ASSERT_EQ(tv.GetChannel(), 5);

// Возвращаемся на предыдущий канал
ASSERT_TRUE(tv.SelectPreviousChannel());
ASSERT_EQ(tv.GetChannel(), 3);

// Выключаем
tv.TurnOff();
ASSERT_FALSE(tv.IsTurnedOn());
ASSERT_EQ(tv.GetChannel(), 0);
}

// Главная функция
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}