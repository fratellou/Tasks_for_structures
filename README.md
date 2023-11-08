# Tasks_for_structures
1) Checking the correctness of the bracket sequence.
The input is a string containing various characters,
including the parenthesis characters "({[". It is necessary to implement an algorithm that
determines whether the brackets are nested correctly using the stack. For example,
the sequence "({})" is correct, the sequences "({)}" and "(][)"
are incorrect.

2) It is necessary to implement an algorithm that should split the set
of natural numbers into disjoint subsets, all of which have
an equal sum. If the set cannot be divided in this way,
output an error message.
Example:
set S = {4, 10, 5, 1, 3, 7}.
It is necessary to arrange elements in each subset, the sum of which
is equal to 15.
We get two subsets {4, 10, 1} and {5, 3, 7}.
It is necessary to arrange elements in each subset, the sum of which
is equal to 10.
We get three subsets {10}, {3, 7} and {4, 5, 1}.

3) It is necessary to implement an algorithm that finds
the subarray with the largest sum in a circular array.
Example:
Array [ 4, -7, 1, 5, -4, 0, -3, 2, 4, 1]
The subarray with the largest amount - [2, 4, 1, 4]

4) It is necessary to implement an algorithm that will check whether
the tree is BST1.

5) Given a chess board of size NxN and the position of the knight. A new position is being set.
It is necessary to calculate and output the shortest path to this position using
a queue.
Example:
4x4 board, position (1, 4), goal (3, 1).
Result: (1, 4) -> (3, 3) -> (1, 2) -> (3, 1).

6) It is necessary to implement an algorithm that determines whether the strings
are isomorphic.
Two strings a and b are considered isomorphic if the characters in a can be replaced
by b.
A character is matched only to one other, the order of the characters must
be preserved.
Example:
"fall" and "redd" are isomorphic.
"mad" and "odd" are not isomorphic.