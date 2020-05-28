#include "KeyEvents.h"
TEST(KeyPressedEvents, getRepeatCount)
{
	EXPECT_EQ(pressedkey.GetRepeatCount(), repeatcount);
}
TEST(KeyPressedEvents, getKeyCode)
{
	EXPECT_EQ(pressedkey.GetKeyCode(), keycode);
}
TEST(KeyReleasedEvents, getKeyCode)
{
	EXPECT_EQ(releasedkey.GetKeyCode(), keycode);
}
TEST(KeyPressedEvents, isInput)
{
	EXPECT_EQ(pressedkey.isInCategory(EventCategoryInput), true);
}TEST(KeyPressedEvents, isKeyboard)
{
	EXPECT_EQ(pressedkey.isInCategory(EventCategoryKeyboard), true);
}
TEST(KeyPressedEvents, isMouse)
{
	EXPECT_EQ(pressedkey.isInCategory(EventCategoryMouse), false);
}
TEST(KeyReleasedEvents, isInput)
{
	EXPECT_EQ(releasedkey.isInCategory(EventCategoryInput), true);
}
TEST(KeyReleasedEvents, isKeyBoard)
{
	EXPECT_EQ(releasedkey.isInCategory(EventCategoryKeyboard), true);
}
TEST(KeyReleasedEvents, isMouse)
{
	EXPECT_EQ(releasedkey.isInCategory(EventCategoryMouse), false);
}
TEST(KeyReleasedEvents, isMouseButton)
{
	EXPECT_EQ(releasedkey.isInCategory(EventCategoryMouseButton), false);
}
TEST(KeyReleasedEvents, isWindow)
{
	EXPECT_EQ(releasedkey.isInCategory(EventCategoryWindow), false);
}
TEST(KeyPressedEvents, isMouseButton)
{
	EXPECT_EQ(pressedkey.isInCategory(EventCategoryMouseButton), false);
}
TEST(KeyPressedEvents, isWindow)
{
	EXPECT_EQ(pressedkey.isInCategory(EventCategoryWindow), false);
}
