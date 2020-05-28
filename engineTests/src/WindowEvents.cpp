#include "WindowEvents.h"

TEST(WindowResizeEvents, getWidth)
{
	EXPECT_EQ(windowresizeevent.getWidth(), width);
}
TEST(WindowResizeEvents, getHeight)
{
	EXPECT_EQ(windowresizeevent.getHeight(), height);
}
TEST(WindowResizeEvents, getcategory)
{
	EXPECT_EQ(windowresizeevent.isInCategory(EventCategoryWindow), true);
}
TEST(WindowCloseEvents, getcategory)
{
	EXPECT_EQ(closeevent.isInCategory(EventCategoryWindow), true);
}
TEST(WindowCloseEvents, getType)
{
	EXPECT_EQ(closeevent.getEventType(), EventType::WindowClose);
}
TEST(WindowResizeEvents, getType)
{
	EXPECT_EQ(windowresizeevent.getEventType(), EventType::WindowResize);
}