#include "eventTests.h"

TEST(Events, ResizeConstructor) {
	int gotWidth = re.getWidth();
	int gotHeight = re.getHeight();
	Engine::EventType type = re.getEventType();

	EXPECT_EQ(gotWidth, width);
	EXPECT_EQ(gotHeight, height);
}