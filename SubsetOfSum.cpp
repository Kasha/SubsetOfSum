/*Subset Of Sum - Retrieves First occurred subset or the closest subset if there is an exists a subarray of array[0..n] for a given sum
Dynamic Programming, in which subproblem solutions are Memoized rather than computed again and again.
Below Memoized version follows the top-down approach,
since we first break the problem into subproblems and then calculate and store values

The time complexity of above solution is O(n x sum. Auxiliary space used by the program is also O(n x sum)*/
#include<stdio.h> 
#include<string>
#include "pch.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;
////////////////////////////////////////
// prints subset found 
void printSubset(const vector<uint32_t>& M, const uint32_t& T, const uint32_t& S)
{
    cout << "\n----Subset-----\n";
    for (auto i : M)
    {
        cout << " " << i;
    }

    cout << "\nTarget NO:" << T << " Sum:" << S;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum FOUND_TYPE
{
    NOT_FOUND,
    FOUND,
    FOUND_CLOSEST,
    FOUND_CLOSEST_FINISH
}FOUND_STATUS;

//Top/Down dynamic programming using Memorized (storage) and recursion
//Retrieves First occurred subset or the closest subset if there is an exists a subarray of array[0..n] for a given sum
bool subsetSum(/*in*/const vector<uint32_t>& arr, /*in*/ uint32_t T, /*in*/uint32_t n, /*in*/uint32_t sum, /*out*/ vector<uint32_t>& M, /*out*/uint32_t& S, /*out*/ vector<uint32_t>& M2)
{
    static FOUND_STATUS found = NOT_FOUND;
    // create a map to store solutions of subproblems
    static unordered_map<string, bool> lookup;
    static unordered_map<uint32_t, vector<uint32_t>> lookupClosestMatch;
    static bool findClosest = false;

    if (found == FOUND)
    {
        return true;
    }

    // return true if sum becomes 0 (subset found)
    if (sum == T)
    {
        found = FOUND;
        return true;
    }
    else if (sum > T)
    {
        found = FOUND_CLOSEST;
        return false;
    }
    if (arr.size() <= n)
    {
        found = FOUND_CLOSEST;
        return false;
    }

    // construct an unique map key from dynamic elements of the input
    string key = to_string(n) + "|" + to_string(sum);

    // if sub-problem is seen for the first time, solve it and
    // store its result in a map
    if (lookup.find(key) == lookup.end())
    {
        if (findClosest == false)
        {
            if (S < sum)
            {
                S = sum;
                lookupClosestMatch[S] = M2;
            }

            M2.push_back(arr[n]);
        }

        // Case 1. include current item in the subset (arr[n]) and recur
        // for remaining items (n + 1) with remaining sum (sum + arr[n])

        bool include = subsetSum(arr, T, n + 1, sum + arr[n], M, S, M2);

        if (include == true)
        {
            M.push_back(arr[n]);
            if (sum + arr[n] == T)
            {
                return true;
            }
        }


        // Case 2. exclude current item n from subset and recur for
        // remaining items (n + 1)
        bool exclude = subsetSum(arr, T, n + 1, sum, M, S, M2);

        bool bSubsetKey = include || exclude;
        if (findClosest == false)
        {
            M2.clear();
        }
        // assign true if we can get subset by including the
        // current item
        lookup[key] = bSubsetKey;
    }

    bool bRes = lookup[key];
    if (found == FOUND_CLOSEST)
    {
        if (bRes == false)
        {
            if (findClosest == false)
            {
                unordered_map<uint32_t, vector<uint32_t>>::const_iterator item = lookupClosestMatch.find(S);

                if (item != lookupClosestMatch.end())
                {
                    M2 = item->second;
                    findClosest = true;
                }
            }
        }
    }
    // return solution to current sub-problem
    return bRes;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool subset_sum(/*in*/ uint32_t T, /*in*/const vector<uint32_t>& I, /*out*/ vector<uint32_t>& M, /*out*/uint32_t& S)
{
    bool bRes = false;
    S = 0;
    //If I is empty then no subset: Example T=?, I={} - O(1)
    if (I.size() == 0)
    {
        return false;
    }//If I size == 1, I contains 1 item and I[0] = T then there is a subset of one item : Example T = 2, I = { 2) - O(1)
    else if (I.size() == 1 && I[0] == T)
    {
        M = I;
        S = T;
        return true;
    }
    else
    {
        vector<uint32_t> vec_limit_up_to_T;

        for (auto i : I)
        {
            //If I contains a subset of 1 element eq to T then this one item is the subset to return: Example T = 2, I = {1,2,3} - o(1)
            if (i == T)
            {
                M.push_back(i);
                S = T;
                return true;
            }

            if (i <= T)//Creating new Vector without elements > T
            {
                vec_limit_up_to_T.push_back(i);
            }

            S += i;
            /*; Cloning I and sorting new vector with cutting vector up to T could save time but will not give the first real subset of I.

            if ( i < T || S < T )
            {
                vec_up_to_T.push_back(i);
            }*/
        }

        //If total items in I = T then I is the subset of T : Example T = 5, I = { 2, 3 } - O(1)
        if (S == T)
        {
            M = I;
            return true;
        }

        size_t size = vec_limit_up_to_T.size();
        if (size == 0)//If after sorting I and removing all elements > T array might be empty : Example T = 5, I = { 6 }
        {
            M.clear();
            S = 0;
            return false;
        }

        S = 0;
        vector<uint32_t> M2;
        //Top/Down dynamic programming using Memorized (storage) and recursion
        bRes = subsetSum(vec_limit_up_to_T, T, 0, 0, M, S, M2);
        if (bRes == false)
        {
            if (M2.size() > 0)
            {
                M = M2;
            }
        }
        else
        {
            if (M.size() > 0)
            {
                reverse(M.begin(), M.end());//Due to "top/down" recursion array elements call, Vector is in the opposite order
            }
        }
    }
    return bRes;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Parameters:
uint32_t T, target of subset sum to look for
const std::vector<uint32_t>& I
vector<uint32_t>& M,  The output of subset=T the closest one
uint32_t& S - The output of subset sum=T the closest sum to T
Outout, fills M with subset=T or the closest subset
first occurred subset or the closest subset if there exists a subarray of array[0..n] with given sum
*/
void find_largest_sum(/*in*/uint32_t T, /*in*/const std::vector<uint32_t>& I, /*out*/vector<uint32_t>& M, /*out*/uint32_t& S)
{
    //Top/Down dynamic programming using Memorized (storage) and recursion
    if (subset_sum(T, I, M, S) == true)
    {
        S = T;
    }
}
////////////////////////////
int main()
{
   /* T = 8, I = { 0 }
    T = 8, I = { 1,1,1,1,1 }
    T = 2, I = { 1,2,3 }
    T = 5, I = { 2, 3 }
    T = 7, I = { 1,4,5 }
     T = 7, I = { 1,4,6 }
    T= 8, I = { 5,1,2,6,7,4,9,11 };*/
    uint32_t T = 8;
    vector<uint32_t> I = { 5,1,2,6,7,4,9,11 };
    vector<uint32_t> M;
    uint32_t S = 0;

    find_largest_sum(T, I, M, S);

    if (M.size() > 0)
    {
        printSubset(M, T, S);
    }
    else
    {
        cout << "no required subset found\n";
    }


  
    return 0;
}