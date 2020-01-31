// Max Macaluso and Kevin Ruby
    //Max and Kevin worked together for the project and developed the code together.
    //Max did slightly more methods in Counter.h, while Kevin focused more on implementing the test cases in test.cpp

// To run:
//     make
//     ./test
// To clean:
//     make clean



#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Counter.h"
#include "TestTypes.h"

// Your tests go here
// Each TEST_CASE should test one function -One class (In this assignment)
// Each SECTION should test one aspect of that function -One method (In this assignment)

//Tests the vector
TEST_CASE("Test Counter", "[classic]")
{
    //Data type being tested is strings
    SECTION("Tests accessing a converted Counter as a regular c++ map with the CounterToMap() function.")
    {
        //Makes a string map
        map<string, int> test_map;
        test_map["A"] = 0;
        test_map["B"] = 1;
        test_map["C"] = 2;
        test_map["D"] = 3;
        test_map["E"] = 4;
        Counter<string> test(test_map);

        //Correct answer...
        map<string, int> correct_map;
        correct_map["A"] = 0;
        correct_map["B"] = 1;
        correct_map["C"] = 2;
        correct_map["D"] = 3;
        correct_map["E"] = 4;

        //Tests CounterToMap function
        REQUIRE(test.CounterToMap() == correct_map);
    }

    //Tests class with vector of strings
    SECTION("Tests using a vector to create a Counter object, also tests the TotalCount() function which returns sum of all values")
    {
        //Makes a string vector
        vector<string> vec;
        vec.push_back("A");
        vec.push_back("B");
        vec.push_back("C");
        Counter<string> test2(vec);

        REQUIRE(test2.TotalCount() == 3);
    }

    //Tests class with struct that primarily uses bool data type
    SECTION("Test Class with a user defined struct and also tests the KeyWeight() function which returns the count associated with the inputted key")
    {
        StructTest test_one(true);
        StructTest test_two(false);
        StructTest test_three(true);

        //Makes a StructTest type map
        map<StructTest, int> test_map_bool;
        test_map_bool[test_one] = 0;
        test_map_bool[test_two] = 1;
        test_map_bool[test_three] = 2;
        Counter<StructTest> test3(test_map_bool);

        REQUIRE(test3.KeyWeight(test_three) == 2);
    }

     //Tests class with primary data type of float with function DecValue() which is an overloaded function which subtracts from the value 1 (defualt) or a desired amount
    SECTION("Test subtracting 1 from custom class, classTest")
    {

        ClassTest a(12.23);
        ClassTest b(7.63);
        ClassTest c(9.93);

        map<ClassTest, int> test_map_double;
        test_map_double[a] = 0;
        test_map_double[b] = 1;
        test_map_double[c] = 2;

        Counter<ClassTest> test4(test_map_double);
        test4.DecValue(b);
        
        //Subtracts value 1 from key b since no input parameters
        REQUIRE(test4.KeyWeight(b) == 0);
    }
    //Same thing as test above but this time, user input desired amount to subtract value of corresponding key with, in this case, 3.
     SECTION("Test subtracting n from custom class, classTest")
     {

         //Makes instance of class 3 times
         ClassTest a(45.34);
         ClassTest b(23.43);
         ClassTest c(12.33);

         map<ClassTest, int> test_map_double;
         test_map_double[a] = 3;
         test_map_double[b] = 4;
         test_map_double[c] = 7;

         Counter<ClassTest> test4(test_map_double);
         test4.DecValue(b, 3);
         
         REQUIRE(test4.KeyWeight(b) == 1);
     }

    //Tests IncValue function which is simialr to DecValue but adds instead of subtracts. Also tested with an Enum data type
    SECTION("Test adding 1 to a desired key/value pair. Defualt value of 1. Tests with an enum.")
    {
      //Declares 2 instances of Enum TestType
      TestType m = TestType::Max;
      TestType k = TestType::Kevin;

      map<TestType, int> test_map_enum;
      test_map_enum[m] = 5;
      test_map_enum[k] = 7;

      Counter<TestType> test5(test_map_enum);
      test5.IncValue(m);
      
      REQUIRE(test5.KeyWeight(m) == 6);


    }

    //Tests IncValue function again but this time with a user defined amount. Enum data type again used
    SECTION("Test adding a desired value to a specificed key/valie pair. Overloaded function.")
    {
      TestType m = TestType::Max;
      TestType k = TestType::Kevin;

      map<TestType, int> test_map_enum;
      test_map_enum[m] = 4;
      test_map_enum[k] = 19;

      Counter<TestType> test5(test_map_enum);
      test5.IncValue(k,4);
      
      REQUIRE(test5.KeyWeight(k) == 23);
    }

    //Data type used is a vector of double to check the RemoveFromMap() function which removes a value/key from the map and sets the instance's map equal to the new map created
    SECTION("Tests vector with double data type and method that removes a value/key from the map")
    {
        //Makes a string vector
        vector<double> vec;
        vec.push_back(1.22);
        vec.push_back(3.14);
        vec.push_back(.679);
        Counter<double> test6(vec);

        //Removes a key/value pair
        test6.RemoveFromMap(3.14);

        //Correct vector without key and corresponding value 3.14 [3.14, 1]
        vector<double> correct_vec;
        correct_vec.push_back(1.22);
        correct_vec.push_back(.679);
        Counter<double> correct_vector(correct_vec);

        REQUIRE(test6.CounterToMap() == correct_vector.CounterToMap());
    }

    //Tests TotalGivenRange() function which sums all the values in a given range. Data type used is bool
    SECTION("Tests vector with bool data type and method that returns sum of all values in range (inclusive)")
    {
        //Makes a bool vector
        map<bool, int> bool_map;
        bool_map[true] = 0;
        bool_map[false] = 1;
        Counter<bool> test7(bool_map);

        REQUIRE(test7.TotalGivenRange(0, 1) == 1);
    }

    //Tests getValues() function which returns a vector of all the values in the map. Tests with a long data type vector
    SECTION("Tests vector with long data type and method that returns a vector of values")
    {
        //Makes a long vector
        vector<long> test_vec;
        test_vec.push_back(1.20);
        test_vec.push_back(5.679);
        Counter<long> test8(test_vec);

        //Correct value
        vector<int> correct_vec;
        correct_vec.push_back(1);
        correct_vec.push_back(1);

        REQUIRE(test8.getValues() == correct_vec);
    }

    //Tests the getKets() function which returns a vector of all the keys in the map. Tests with an empty integer map
    SECTION("Tests the defualt constructor and getKeys() function which returns all of the keys of the Counter object")
    {
        //Creates an object named int_counter. Will be a map of <int, int>
        Counter<int> int_counter;

        //Correct solution, should be empty
        vector<int> correct_vec;

        REQUIRE(int_counter.getKeys() == correct_vec);
    }

    //Tests the NMostCommon() function which returns a vector of desired number of most common values. Tests with an integer map
    SECTION("Tests map of <int, int> and NMostCommon() function which returns a vector of desired number of most common values")
    {
        //Makes a string vector
        map<int, int> test_map;
        test_map[0] = 0;
        test_map[1] = 1;
        test_map[2] = 2;
        test_map[3] = 3;
        test_map[4] = 4;
        Counter<int> test10(test_map);

        //Correct answer...
        vector<int> correct_vec;
        correct_vec.push_back(4);
        correct_vec.push_back(3);
        correct_vec.push_back(2);

        //Tests NMostCommon function
        REQUIRE(test10.NMostCommon(3) == correct_vec);
    }

    //Tests NLeastCommon() function which returns a vector of desired number of least common values. Tests with an integer map
    SECTION("Tests map of <int, int> and NMostCommon() function which returns a vector of desired number of least common values")
    {
        //Makes an int vector
        map<int, int> test_map;
        test_map[0] = 0;
        test_map[1] = 1;
        test_map[2] = 2;
        test_map[3] = 3;
        test_map[4] = 4;
        Counter<int> test11(test_map);

        //Correct answer...
        vector<int> correct_vec;
        correct_vec.push_back(0);
        correct_vec.push_back(1);

        //Tests NLeastCommon function
        REQUIRE(test11.NLeastCommon(2) == correct_vec);
    }

    //Tests the NormalizedWeights() function which returns the percentage of overall weight of each index. Tests with a string map
    SECTION("Tests map of <string, int> and NormalizedWeights() function")
    {
        //Makes a string vector
        map<string, int> test_map;
        test_map["A"] = 1;
        test_map["B"] = 3;
        test_map["C"] = 6;
    
        Counter<string> test12(test_map);
    
        //Correct answer...
        map<string, float> test_map_correct;
        test_map_correct["A"] = .1;
        test_map_correct["B"] = .3;
        test_map_correct["C"] = .6;
    
        //Tests NormalizedWeights function
        REQUIRE(test12.NormalizedWeights() == test_map_correct);
    }

}
