# Week 5

Inheritance is a simulation of blood type inheritance and an application of recursion, though not as fun as tideman.

Speller has some difficulty as the last problem in C. The framework given is a hash tree based on prefix alphas. A trie might offer a faster speed.

Code thoughts: Map the dictionary based on the first several characters. The mapping function is the order in the alphabet. The single quote should be taken into consideration.

There's not much improvement when changing from two characters prefix to three, let alone four. The final total running time is still 0.1 sec slower than the staff's solution.

The texts provided are all very classic, including a selection from *Dream of the Red Chamber*.

## Hash Table

More frequently used than hash tree and trie, the course didn't provide deep analyse about hash table and hash function.

Hash table is a hash tree with one layer leading to the requirement of careful design in hash function to avoid conflicts, which is a mathematical problem.

Trie doesn't need to calculate hash value, and is free from the conflict problem. The prefix searching method also provides more versatile appliaction. However, the link table structure results in multiple memory accesses, slowing the speed. Trie usually requires more memory spaces as well.