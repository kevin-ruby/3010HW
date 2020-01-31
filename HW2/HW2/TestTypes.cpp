#include "TestTypes.h"

//Implementation file for TestTypes.h. Basic custom data types but should sufficiently prove the code works.

StructTest::StructTest(bool d)
{
    data = d;

}
bool operator<(const StructTest& other, const StructTest& other2)
{
  return other.data < other2.data;
}


ClassTest::ClassTest(double d)
{
    data = d;

}
bool operator<(const ClassTest& other, const ClassTest& other2)
{
   return other.data < other2.data;
}
