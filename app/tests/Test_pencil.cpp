#include "CppUTest/TestHarness.h"
#include "pencil.h"

#include <iostream>

using namespace std;

TEST_GROUP(pencil) {
};
 
TEST(pencil, trySimpleWrite_ExpectedSame) {
  Pencil testPencil;
  Paper testPaper;
  string testString = "This is a test";

  testPencil.write(testPaper, testString);
  CHECK(testString == testPaper.text);
}
