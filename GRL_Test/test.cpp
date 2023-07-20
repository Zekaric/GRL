#include "pch.h"

TEST(GRL, LibraryStart)
{
  EXPECT_TRUE(grlStart());
  
  grlStop();
}
