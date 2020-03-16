# SubsetOfSum
 Subset Of Sum - Retrieves First occurred subset or the closest subset if there is an exists a subarray of array[0..n] for a given sum


Subset Sum Problem Retrieving Subset of Sum or Closest to Sum
Solution using Top/Down dynamic programming using Memorized (storage) and recursion.
Retrieves the first occurred subset or the closest subset of the sum.

The time complexity of the above solution is O(n x sum. Auxiliary space used by the program is also O(n x sum)

Described Problem:
Given an integer (T) and an integer set (I), find a subset (M) that the sum (S) of M's elements is the largest among all subsets of I. S <= T. Signature of the interface : void find_largest_sum(uint32_t T, const std::vector &I, vector& M, uint32_t &S); 

example 
T: 11 
I: 1 , 2, 3, 4, 5, 6,7 
possible answers 
M: 5,6 S:11 
M: 4, 7 
S: 11

T = sum
I = Array

Special Scenarios:
1. If I is empty then no subset: Example T=?, I={}
2. If I size == 1, I contains 1 item and I[0] = T then there is a subset of one item: Example T = 2, I={2)
3. If I contains a subset of 1 element eq to T then this one item is the subset to return: Example T = 2, I = {1,2,3}
4. If total items in I = T then I is the subset of T: Example T = 5, I = {2, 3}
5. T can be 0 and I can contains subset of 0; T = 0, I ={0,0,0,0} 
6. If after sorting I and removing all elements > T array might be empty: Example T=5, I={6}
7. Case where the biggest subset in I < T: Example T= 8; I={0}

Input Use Cases:
T = 8, I = { 0 }
T = 8, I = { 1,1,1,1,1 }
T = 2, I = { 1,2,3 }
T = 5, I = { 2, 3 }
T = 7, I = { 1,4,5 }
T = 7, I = { 1,4,6 }
T= 8, I = { 5,1,2,6,7,4,9,11 };


