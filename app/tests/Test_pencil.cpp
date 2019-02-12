#include "CppUTest/TestHarness.h"
#include "pencil.h"

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
  uint16_t textCost = testPencil.getTextCost(testString);

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
  uint16_t textCost = testPencil.getTextCost(testString);
  CHECK_EQUAL(defaultPointDurability - textCost, testPencil.pointDurability());

  CHECK_EQUAL(defaultGraphiteDurability - 1, testPencil.sharpen());
}

TEST(pencil, trySharpenOnceAtEnd_ExpectNoPointDurabilityChange_GraphiteDurability0) {
  uint16_t defaultPointDurability = 1000;
  uint16_t defaultGraphiteDurability = 1;

  Pencil testPencil(defaultPointDurability, defaultGraphiteDurability);
  Paper testPaper;
  string testString = "Sharpen Test";

  uint16_t expectedDurability = (uint16_t)(testPencil.pointDurability() - testPencil.getTextCost(testString));
  testPencil.write(testPaper, testString);
  CHECK_EQUAL(expectedDurability, testPencil.pointDurability());
  
  CHECK_EQUAL(0, testPencil.sharpen());
  CHECK_EQUAL(defaultPointDurability, testPencil.pointDurability());

  expectedDurability = (uint16_t)(testPencil.pointDurability() - testPencil.getTextCost(testString));
  testPencil.write(testPaper, testString);
  CHECK_EQUAL(expectedDurability, testPencil.pointDurability());

  CHECK_EQUAL(0, testPencil.sharpen());
  CHECK_EQUAL(expectedDurability, testPencil.pointDurability());
}

TEST(pencil, tryEraseOneWord_ExpectWordErased) {
  Pencil testPencil;
  string testString = "How much wood would a woodchuck chuck if a woodchuck could chuck wood?";
  Paper testPaper(testString);

  testPencil.erase(testPaper, "chuck");
  CHECK("How much wood would a woodchuck chuck if a woodchuck could       wood?" == testPaper.text);
}

TEST(pencil, tryEraseTwoWords_ExpectTwoWordsErased) {
  Pencil testPencil;
  string testString = "How much wood would a woodchuck chuck if a woodchuck could chuck wood?";
  Paper testPaper(testString);

  testPencil.erase(testPaper, "chuck");
  testPencil.erase(testPaper, "chuck");
  CHECK("How much wood would a woodchuck chuck if a wood      could       wood?" == testPaper.text);
}

TEST(pencil, tryEraseOneWordWithNotEnoughDurability_ExpectPartialWordErased) {
  Pencil testPencil(1000, 100, 3);
  string testString = "Buffalo Bill";
  Paper testPaper(testString);

  testPencil.erase(testPaper, "Bill");
  CHECK("Buffalo B   " == testPaper.text);
}

TEST(pencil, tryToEditEmptySpace_ExpectOverwrittenWord) {
  Pencil testPencil;
  Paper testPaper("An       a day keeps the doctor away");

  testPencil.edit(testPaper, "onion", 3);
  CHECK("An onion a day keeps the doctor away" == testPaper.text);
}

TEST(pencil, tryToEditOverText_ExpectOverwrittenWordAndConflictSymbol) {
  Pencil testPencil;
  Paper testPaper("An       a day keeps the doctor away");

  testPencil.edit(testPaper, "artichoke", 3);
  CHECK("An artich@k@ay keeps the doctor away" == testPaper.text);
}
