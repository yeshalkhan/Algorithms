Greedy Approach:

isGreedyPossible function function: Checks if the greedy algorithm can be applied by verifying if denominations are multiples of each other.
coinChangeGreedy: Implements the greedy algorithm. It iteratively selects the largest possible denominations until the totalSum
is satisfied, updating the total number of coins used (total) and the result vector with the number of each denomination used.
If totalSum is not completely satisfied, it returns -1, indicating that the greedy algorithm cannot be applied.
Calls printDenominations to display the result.
Returns the total number of denominations used.
If the greedy algorithm cannot be applied, the program switches to the dynamic programming solution and displays the result.

Time Complexity:
The loop runs for each denomination in denValues. The operations inside the loop are constant time.
Therefore, the time complexity of the coinChangeGreedy function is O(n), where n is numOfDen or the number of denominations.

Dynamic Programming Approach:

Initialization:
The table is a 2D array representing a dynamic programming table.
The first column is filled with zeros since making change for zero requires zero coins.
The first row is filled based on the assumption that only the first denomination is used.
Filling the Table:
The nested loops iterate over each combination of denominations and target sums.
The table is filled using the recurrence relation. If the current denomination can't be used to make change for the current sum, 
the entry is copied from the row above. Otherwise, it's the minimum of the entry above and the entry at a specific offset 
(indicating the use of the current denomination).
Extracting Denominations Used:
The loop at the end extracts the denominations used based on the filled table. It starts at the bottom-right corner and moves 
backward to reconstruct the solution.
Displaying the Result:
The printDenominations function is called to display the denominations used.
Error Handling:
If the remaining totalSum is less than 0, it means the sum can't be constructed, and -1 is returned.

Time Complexity:
The time complexity of filling the table is O(m * n), where m is the number of denominations and n is the totalSum. The loop that
extracts denominations used takes O(m + n) time. Therefore, the overall time complexity of the dynamic programming solution is O(m * n).