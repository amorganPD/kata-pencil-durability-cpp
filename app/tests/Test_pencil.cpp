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

TEST(pencil, tryTwoSentences_ExpectAppended) {
  Pencil testPencil;
  Paper testPaper("She sells sea shells");

  testPencil.write(testPaper, " down by the sea shore");
  CHECK("She sells sea shells down by the sea shore" == testPaper.text);
}

TEST(pencil, tryDefaultPointDurability_Expect1000) {
  Pencil testPencil;
  CHECK_EQUAL(1000, testPencil.pointDurability());
}

TEST(pencil, tryPointDurabilityOver9000_ExpectOver9000) {
  Pencil testPencil(9001);
  CHECK_EQUAL(9001, testPencil.pointDurability());
}
