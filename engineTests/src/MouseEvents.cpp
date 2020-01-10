#include "MouseEvents.h"

TEST(MouseMovedEvents, getX)
{
	EXPECT_EQ(mousemove.GetX(), x);
}
TEST(MouseMovedEvents, getY)
{
	EXPECT_EQ(mousemove.GetY(), y);
}
TEST(MouseScrolledEvents, getXOffset)
{
	EXPECT_EQ(mousescroll.GetXOffset(), xoffset);
}
TEST(MouseScrolledEvents, getYOffset)
{
	EXPECT_EQ(mousescroll.GetYOffset(), yoffset);
}
TEST(MouseButtonEvents, buttonpress)
{
	EXPECT_EQ(mousepress.GetMouseButton(), button);
}
TEST(MouseButtonEvents, buttonrelease)
{
	EXPECT_EQ(mouserelease.GetMouseButton(), button);
}
TEST(MouseMovedEvents, getcategory)
{
	EXPECT_EQ(mousemove.isInCategory(EventCategoryMouse), true);
}
TEST(MouseMovedEvents, getType)
{
	EXPECT_EQ(mousemove.getEventType(), EventType::MouseMoved);
}
TEST(MouseButtonEvents, getCategory)
{
	EXPECT_EQ(mousepress.isInCategory(EventCategoryMouse), true);
}
TEST(MouseButtonEvents, getCategory2)
{
	EXPECT_EQ(mousepress.isInCategory(EventCategoryInput), true);
}
TEST(MouseButtonEvents, getCategory3)
{
	EXPECT_EQ(mouserelease.isInCategory(EventCategoryMouse), true);
}
TEST(MouseButtonEvents, getCategory4)
{
	EXPECT_EQ(mouserelease.isInCategory(EventCategoryInput), true);
}