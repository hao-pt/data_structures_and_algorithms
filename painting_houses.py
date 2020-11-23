"""
1. Problem description:
There are a row of N houses, each house can be painted with one of the three colors: red, blue or green.
The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.
The cost of painting each house with a certain color is represented by a N x 3 cost matrix A.
For example, A[0][0] is the cost of painting house 0 with color red; A[1][2] is the cost of painting house 1 with color green, and so on.
Find the minimum total cost to paint all houses.

2. Constraint:
1 <= N <= 105

1 <= A[i][j] <= 103

3. Example:
Input: A = [  [1, 2, 3]
        [10, 11, 12]
     ]
Output: 12
Paint house 1 with red and house 2 with green i.e A[0][0] + A[1][1] = 1 + 11 = 12

Input: A = [[1, 3, 5],[2, 4, 6],[5, 4, 3]]
Output: 8
Paint the first house red, paint the second house blue, and paint the third house green.
"""
class Solution:
    # @param A : list of list of integers
    # @return an integer 
    def solve(self, A):
        '''
        Approach: Bottom-up DP
        Idea: dp(i, j) presents the minimum cost of painting house i with color j plus cost of previous houses.
        Therefore, to find cheapest price to paint all houses is min(dp(n-1)) 
        Time complexity: O(n*m) where n is number of houses, m is number of colors. In this problem, m is fixed with 3
        so O(n)
        Space complexity: O(1) because we use A as our dp matrix
        '''
        if len(A) == 0:
            return 0
        n = len(A)
        
        # Use A for storing solutions of smaller problems
        # # dp[i][j] store minimum cost of house i with color j
        # dp = [[0 for _ in range(3)] for _ in range(n)]
        # dp[0] = A[0] # cost of painting first house is the same as input
        
        for i in range(1, n):
            for j in range(3):
                # paint house i with color j
                # plus minimum cost of previous house not conflicting with color j
                A[i][j] = A[i][j] + min(A[i-1][(j+1)%3], A[i-1][(j+2)%3])
        
        return min(A[-1])