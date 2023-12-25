Recursive approach:

The LCHelper function is a recursive helper function that calculates the length of the LCS starting 
from indices i in string a and j in string b.
When the characters at indices i and j match (a[i] == b[j]), the function increments the length by 1 
and makes a recursive call for the next indices (i + 1 and j + 1).
table[i][j] is set to true to mark that these characters contribute to the LCS.
If the characters do not match, the function considers two possibilities:
i. Move to the next character in string a (LCHelper(i + 1, j, a, b, table)).
ii. Move to the next character in string b (LCHelper(i, j + 1, a, b, table)).
The result is the maximum length obtained from either of these possibilities.
The main function LCRecursion initializes a boolean table, calculates the length using LCHelper, 
and then constructs the LCS by extracting characters from the table.

Time Complexity:
At each recursive call, there are two possibilities:

Move to the next character in string 
i. T(i+1,j)
Move to the next character in string 
ii. T(i,j+1)
The recursion tree has O(2^(m+n)) nodes, as each node has two children.

Dynamic approach:

Initialization:
Two vectors, values and arrows, are created to store LCS lengths and directions, respectively.
A dummy character is added at the beginning of each string (a and b) to simplify indexing.
Filling the Table (values and arrows):
A nested loop iterates through each position in the values and arrows matrices.
If characters at the current positions in a and b match (a[i] == b[j]), the length of the LCS is extended
 diagonally ('D' direction) by 1, and the direction is marked as diagonal.
If characters do not match, the maximum value from the adjacent positions ('H' for horizontal or 'd' for down)
 is taken, and the corresponding direction is stored.
This process fills the entire table, providing the length of the LCS and the direction at each position.
Backtracking (result Construction):
Starting from the bottom-right corner of the table (i = len1 - 1, j = len2 - 1), the backtracking loop uses
 the directions stored in the arrows matrix.
If the direction is diagonal ('D'), it means a match, so the corresponding character from string b is appended 
to the result.
If the direction is horizontal ('H'), j is decremented to move to the left.
If the direction is down ('d'), i is decremented to move upwards.
This process continues until i and j reach 0, constructing the final LCS.
Reversing the Result:
The result is reversed because it was constructed from the bottom-right corner.
Return:
The length of the LCS is returned, which is stored in the bottom-right cell of the values matrix.

Time Complexity:
Filling the table requires iterating through each position in the table, taking constant time for each cell.
The nested loops result take O(m⋅n) time, where m is the length of string a and n is the length of string b.
Backtracking through the arrows also takes O(m+n) time since.
Overall, the dynamic programming approach has a time complexity of O(m⋅n).