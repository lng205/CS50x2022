# Week 5

inheritance模拟血型遗传，是对递归的应用，感觉不如tideman。。设计。

speller作为C的最后一个作业，有一定的难度。给出的框架是基于前缀字母的哈希树，想提高速度的话用字典树应该更加合适。

代码思路：将字典按照前若干位字符映射为哈希树，映射函数为字母表序号。前缀字符串需考虑单引号情况。

实测从两位改为三位前缀的树时，查找速度提升已经不大了，四位则基本无提升。最后的总运行时间还是比staff的代码慢了近0.1秒。

提供的文本都相当经典，包括红楼梦选段。

## 哈希表

哈希表通常比哈希树和字典树使用的更加频繁。课程没有提供关于哈希表和哈希函数的深入分析。

哈希表实际就是只有一层的哈希树，因此需对哈希函数进行设计来避免哈希值冲突。哈希函数的设计属于数学问题。

字典树不需计算哈希值，也不存在冲突问题，前缀式查找也提供了更灵活的应用方式。但字典树的链表结构需要多次访问内存，降低速度，此外还需要更大的内存空间。


Inheritance is a simulation of blood type inheritance and an application of recursion, though not as fun as tideman.

Speller has some difficulty as the last problem in C. The framework given is a hash tree based on prefix alphas. A trie might offer a faster speed.

Code thoughts: Map the dictionary based on the first several characters. The mapping function is the order in the alphabet. The single quote should be taken into consideration.

There's not much improvement when changing from two characters prefix to three, let alone four. The final total running time is still 0.1 sec slower than the staff's solution.

The texts provided are all very classic, including a selection from *Dream of the Red Chamber*.

## Hash Table

More frequently used than hash tree and trie, the course didn't provide deep analyse about hash table and hash function.

Hash table is a hash tree with one layer leading to the requirement of careful design in hash function to avoid conflicts, which is a mathematical problem.

Trie doesn't need to calculate hash value, and is free from the conflict problem. The prefix searching method also provides more versatile appliaction. However, the link table structure results in multiple memory accesses, slowing the speed. Trie usually requires more memory spaces as well.