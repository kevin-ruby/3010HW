#include "Counter.h"
#include "TestTypes.h"

int main()
{
    //Counter<int> int_counter;
    // Counter<string> words;

    //To Test functions
    map<string, int> test_map;
    test_map["A"] = 0;
    test_map["B"] = 1;
    test_map["C"] = 2;
    test_map["D"] = 3;
    test_map["E"] = 4;

    //To test functions
    vector<string> vec;
    vec.push_back("A");
    vec.push_back("B");
    vec.push_back("C");

    // Counter<ClassTest> cls;
    // Counter<StructTest> stct;
    // Counter<TestType> enm;


    //Creates object called test
    Counter<string> test(test_map);

    map<string, float> map2 = test.NormalizedWeights();

    for (auto it = map2.begin(); it != map2.end(); it++)
    {
        cout << it->first << ", " << it->second;
        cout << endl;
    }

}

    //For testing IncValue and DecValue
    // test.DecValue("A");
    // map<string, int> test_map2 = test.CounterToMap();

    // //Loops through test_map2 and prints key, value
    // for (auto it = test_map2.begin(); it != test_map2.end(); it++)
    // {
    //     cout << it->first << ", " << it->second;
    //     cout << endl;
    // }

    // //Test for function NormalizedWeights()
    // map<string, float> test_map2 = test.NormalizedWeights();

    //Loops through test_map2 and prints key, value
    // for (auto it = test_map2.begin(); it != test_map2.end(); it++)
    // {
    //     cout << it->first << ", " << it->second;
    //     cout << endl;
    // }
