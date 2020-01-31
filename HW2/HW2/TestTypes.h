#ifndef _TESTTYPES_H_
#define _TESTTYPES_H_

//Header file that will be used to test my templeted Counter class.

struct StructTest
{
    StructTest(bool d);
    bool data;
    friend bool operator<(const StructTest& other, const StructTest& other2);
};

class ClassTest
{
    public:
        ClassTest(double d);
        friend bool operator<(const ClassTest& other ,const ClassTest& other2);

    private:
        double data;
};

enum class TestType {Max = 0, Kevin = 1};

#endif
