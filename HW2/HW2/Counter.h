#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include <vector>

using namespace std;

template <class T_Type> class Counter
{
    public:
        //Constructor, map of T_Type. Key, value
        //Input param is map
        Counter(map<T_Type, int> input_map);

        //Constructor for initiliazing map with a vector of keys
        Counter(vector<T_Type> vec);

        //Defualt constructor
        Counter();

        //Increments value by n
        void IncValue(T_Type value_to_change, int change);

        //Increments value by 1
        void IncValue(T_Type value_to_change);

        //Decrements value by n
        void DecValue(T_Type value_to_change, int change);

        //Decrements value by 1
        void DecValue(T_Type value_to_change);

        //Returns n most/least common objects
        vector<T_Type> NMostCommon(int n);
        vector<T_Type> NLeastCommon(int n);

        //Returns percentage of overall weight each index, or value is, compared to the whole
        map<T_Type, float> NormalizedWeights();

        //Returns vector of all keys
        vector<T_Type> getKeys();

        //Returns vector of all values
        vector<int> getValues();

        //Access a converted Counter as a "regular" c++ map. IE return custom_map
        map<T_Type, int> CounterToMap();

        //Access the total of all counts so far (how many objects have been counted)
        int TotalCount();

        //Given the key range (min, max), return sum of all values in range
        int TotalGivenRange(int min, int max);

        //Removes input parameter from the map
        void RemoveFromMap(T_Type key_to_remove);

        //Function returns the count associated with value key
        int KeyWeight(T_Type key);

    private:
        map<T_Type, int> custom_map;
};


/**
    constructer

    @param map object
    @return NA.
*/
//Constructor, map with Key: T_Type, value: int
//Initilize with a map
template <class T_Type> Counter<T_Type>::Counter(map<T_Type, int> input_map)
{
    //Sets class map as passed in value
    custom_map = input_map;
}

/**
    constructer

    @param vector of TTypes
    @return NA.
*/
template <class T_Type> Counter<T_Type>::Counter(vector<T_Type> vec)
{
    //Will be value of each key (How many times it occurs in input vec)
    int count = 1;

    //Loops through vec
    for (int x = 0; x < vec.size(); x++)
    {
        count = 1;

        //Inner for loop checks for duplicate values in vec
        for (int i = 0; i < vec.size(); i++)
        {
            //If not same index in vector
            if (x != i)
            {
                //If values are equal
                if (vec[x] == vec[i])
                {
                    //Update count
                    count++;
                }
            }
        }
        //Maps do not allow duplicate of same key, so insert vec element with corresponding times value was found in vec
        custom_map[vec[x]] = count;
    }
}

/**
    Default constructer - sets custom map objects.

    @param NA
    @return NA.
*/
template <class T_Type> Counter<T_Type>::Counter()
{
    //Nothing in code body, just need so I have a defualt constructor
    custom_map;
}
/**
    IncValue - //Increments value by n

    @param key in map, value to add
    @return NA.
*/

template <class T_Type> void Counter<T_Type>::IncValue(T_Type key_to_change, int change)
{
    //Declares an iterator named it and sets pointer equal to address of desired key
    typename map<T_Type, int>::iterator it;
    it = custom_map.find(key_to_change);

    //If not found
    if (it == custom_map.end())
    {
        cout << "Not found!" << endl;
    }
    //If found
    else
    {
        it->second = it->second + change;
    }
}
/**
    //Overloaded function - - IncValue - //Increments value by 1 automatically

    @param key in map
    @return NA.
*/

template <class T_Type> void Counter<T_Type>::IncValue(T_Type key_to_change)
{
    //Declares an iterator named it and sets pointer equal to address of desired key
    typename map<T_Type, int>::iterator it;
    it = custom_map.find(key_to_change);

    //If not found
    if (it == custom_map.end())
    {
        cout << "Not found!" << endl;
    }
    //If found
    else
    {
        it->second = it->second + 1;
    }
}
/**
     DecValue - //decrements value by n

    @param key in map, value
    @return NA.
*/

template <class T_Type> void Counter<T_Type>::DecValue(T_Type key_to_change, int change)
{
    //Declares an iterator named it and sets pointer equal to address of desired key
    typename map<T_Type, int>::iterator it;
    it = custom_map.find(key_to_change);

    //If not found
    if (it == custom_map.end())
    {
        cout << "Not found!" << endl;
    }
    //If found
    else
    {
        it->second = it->second - change;
    }
}

/**
    //Overloaded function - - DecValue - //decrements value by 1 automatically

    @param key in map
    @return NA.
*/

template <class T_Type> void Counter<T_Type>::DecValue(T_Type key_to_change)
{
    //Declares an iterator named it and sets pointer equal to address of desired key
    typename map<T_Type, int>::iterator it;
    it = custom_map.find(key_to_change);

    //If not found
    if (it == custom_map.end())
    {
        cout << "Not found!" << endl;
    }
    //If found
    else
    {
        it->second = it->second - 1;
    }
}

/**
    NMostCommon //Returns n most common keys in a vector

    @param interger
    @return vector of T_Types
*/


template <class T_Type> vector<T_Type> Counter<T_Type>::NMostCommon(int n)
{
    //Will get all values from the custom_map
    vector<int> sorted_values = getValues();

    //Sorts the vector in descending order
    sort(sorted_values.begin(), sorted_values.end(), greater<int>());

    vector<T_Type> sorted_keys;

    //Handles edge case
    if (n > sorted_values.size())
    {
        cout << "Error, input is greater than map size!" << endl;
        return sorted_keys;
    }

    //Loops through sorted_values n times
    for (int x = 0; x < n; x++)
    {
        //Loops through map, gets corresponding key
        for (typename map<T_Type, int>::iterator it = custom_map.begin(); it != custom_map.end(); it++)
        {
            if (it->second == sorted_values[x])
            {
                sorted_keys.push_back(it->first);
            }
        }
    }

    return sorted_keys;
}
/**
    NLeastCommon //Returns n least common keys in a vector

    @param interger
    @return vector of T_Types
*/
//Returns n least common keys in a vector
template <class T_Type> vector<T_Type> Counter<T_Type>::NLeastCommon(int n)
{
    //Will get all values from the custom_map
    vector<int> sorted_values = getValues();

    //Sorts the vector in descending order
    sort(sorted_values.begin(), sorted_values.end());

    vector<T_Type> sorted_keys;

    //Handles edge case
    if (n > sorted_values.size())
    {
        cout << "Error, input is greater than map size!" << endl;
        return sorted_keys;
    }

    //Loops through sorted_values n times
    for (int x = 0; x < n; x++)
    {
        //Loops through map, gets corresponding key
        for (typename map<T_Type, int>::iterator it = custom_map.begin(); it != custom_map.end(); it++)
        {
            if (it->second == sorted_values[x])
            {
                sorted_keys.push_back(it->first);
            }
        }
    }

    return sorted_keys;
}
/**
    NormalizedWeights //Returns percentage of overall weight each index, or value is, compared to the whole

    @param NA
    @return vector of T_Types
*/

template <class T_Type> map<T_Type, float> Counter<T_Type>::NormalizedWeights()
{
    //Map with same keys but values are their weights
    map<T_Type, float> normalized_map;

    //Gets the total weight from summing all of the values in the map
    float weight = TotalCount();

    //Loops through custom_map and sets values of normalized map
    for (typename map<T_Type, int>::iterator it = custom_map.begin(); it != custom_map.end(); it++)
    {
        //Key = value / total weight
        normalized_map[it->first] = it->second / weight;
    }
    return normalized_map;
}

/**
    getKeys //Returns vector of all keys

    @param NA
    @return vector of keys
*/

template <class T_Type> vector<T_Type> Counter<T_Type>::getKeys()
{
    vector<T_Type> vec;
    for (typename map<T_Type, int>::iterator it = custom_map.begin(); it != custom_map.end(); it++)
    {
        vec.push_back(it->first);
    }
    return vec;
}

/**
    getValues //Returns vector of all values

    @param NA
    @return vector of values
*/

template <class T_Type> vector<int> Counter<T_Type>::getValues()
{
    vector<int> vec;
    for (typename map<T_Type, int>::iterator it = custom_map.begin(); it != custom_map.end(); it++)
    {
        vec.push_back(it->second);
    }
    return vec;
}

/**
    CounterToMap //Access a converted Counter as a "regular" c++ map, return class map, custom_map


    @param NA
    @return custom map field
*/
template <class T_Type> map<T_Type, int> Counter<T_Type>::CounterToMap()
{
    return custom_map;
}

/**
    CounterToMap//Access the total of all counts so far (how many objects have been counted)


    @param NA
    @return custom int
*/
template <class T_Type> int Counter<T_Type>::TotalCount()
{
    int count = 0;
    for (typename map<T_Type, int>::iterator it = custom_map.begin(); it != custom_map.end(); it++)
    {
        count += it->second;
    }
    return count;
}

/**
    CounterToMap //Given the key range (min, max), return sum of all values in range (inclusive)


    @param min and max
    @return custom int
*/

template <class T_Type> int Counter<T_Type>::TotalGivenRange(int min, int max)
{
    //Will be vector I am summing from
    vector<int> sorted_values = getValues();

    //Value I will be returning
    int sum_in_range = 0;

    //Sorts the vector in descending order
    sort(sorted_values.begin(), sorted_values.end(), greater<int>());

    for (int x = 0; x < sorted_values.size(); x++)
    {
        if (sorted_values[x] >= min && sorted_values[x] <= max)
        {
            sum_in_range += sorted_values[x];
        }
    }
    return sum_in_range;

}

/**
    CounterToMap //Removes input parameter from the map


    @param key
    @return NA
*/


template <class T_Type> void Counter<T_Type>::RemoveFromMap(T_Type key_to_remove)
{
    //Will be return value
    map<T_Type, int> new_map;

    //Loops through custom_map
    for (auto it = custom_map.begin(); it != custom_map.end(); it++)
    {
        //Adds all but the undesired key
        if (it->first != key_to_remove)
        {
            new_map[it->first] = it->second;
        }
    }
    custom_map = new_map;
}
/**
    CounterToMap //Function returns the count associated with value key


    @param key
    @return int
*/

template <class T_Type> int Counter<T_Type>::KeyWeight(T_Type key)
{
    //Declares an iterator named it and sets pointer equal to address of desired key
    typename map<T_Type, int>::iterator it;
    it = custom_map.find(key);

    //If not found
    if (it == custom_map.end())
    {
        return 0;
    }
    //Else it's found
    return (it->second);
}
