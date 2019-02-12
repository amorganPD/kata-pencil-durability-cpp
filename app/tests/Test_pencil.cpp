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

TEST(pencil, tryAllUppercase_ExpectLenghtTimes2DurabilityLoss) {
  Pencil testPencil(9001);
  Paper testPaper;
  string testString = "TEST";
  
  testPencil.write(testPaper, testString);

  CHECK_EQUAL(9001 - testString.length()*(uint8_t)COST_UPPERCASE, testPencil.pointDurability());
}

TEST(pencil, tryAllLowercase_ExpectLenghtTimes1DurabilityLoss) {
  Pencil testPencil(9001);
  Paper testPaper;
  string testString = "test";
  
  testPencil.write(testPaper, testString);

  CHECK_EQUAL(9001 - testString.length()*(uint8_t)COST_LOWERCASE, testPencil.pointDurability());
}

TEST(pencil, tryWriteWhenNotEnoughDurability_ExpectSpaceAtEnd) {
  Pencil testPencil(4);
  Paper testPaper;
  string testString = "Text";
  
  testPencil.write(testPaper, testString);
  uint16_t textCost = testPencil.getStringCost(testString);

  CHECK_EQUAL(5, textCost);
  CHECK("Tex " == testPaper.text);
  CHECK_EQUAL(0, testPencil.pointDurability());
}

TEST(pencil, trySharpenOnce_ExpectFullPointDurability_Lose1GraphiteDurability) {
  Pencil testPencil;
  Paper testPaper;
  string testString = "Sharpen Test";

  uint16_t defaultPointDurability = testPencil.pointDurability();
  uint16_t defaultGraphiteDurability = testPencil.graphiteDurability();
  
  testPencil.write(testPaper, testString);
  uint16_t textCost = testPencil.getStringCost(testString);
  CHECK_EQUAL(defaultPointDurability - textCost, testPencil.pointDurability());

  CHECK_EQUAL(defaultGraphiteDurability - 1, testPencil.sharpen());
}

TEST(pencil, trySharpenOnceAtEnd_ExpectNoPointDurabilityChange_GraphiteDurability0) {
  uint16_t defaultPointDurability = 1000;
  uint16_t defaultGraphiteDurability = 1;

  Pencil testPencil(defaultPointDurability, defaultGraphiteDurability);
  Paper testPaper;
  string testString = "Sharpen Test";

  uint16_t expectedDurability = (uint16_t)(testPencil.pointDurability() - testPencil.getStringCost(testString));
  testPencil.write(testPaper, testString);
  CHECK_EQUAL(expectedDurability, testPencil.pointDurability());
  
  CHECK_EQUAL(0, testPencil.sharpen());
  CHECK_EQUAL(defaultPointDurability, testPencil.pointDurability());

  expectedDurability = (uint16_t)(testPencil.pointDurability() - testPencil.getStringCost(testString));
  testPencil.write(testPaper, testString);
  CHECK_EQUAL(expectedDurability, testPencil.pointDurability());

  CHECK_EQUAL(0, testPencil.sharpen());
  CHECK_EQUAL(expectedDurability, testPencil.pointDurability());
}
