# Week 3

plurality很好地引入了投票这个概念。

作为没怎么接触过投票的同学，tideman的原理很有趣。

作为没怎么接触过数据结构的同学，矩阵和图这样的二维数据结构，以及用到的邻接矩阵都很有趣。

除去理解题目和框架，代码中最难的地方应该是判断图中是否存在环路。这是对课程所教的递归思想的一次巧妙应用，题目和课堂的引导恰到好处，是本课程中**非常优秀的一道作业题**。

代码思路：要寻找是否存在一个节点指向某一目标结点的路线，可寻找该节点指向的每个下一级节点是否有指向目标结点的路线，递归直到没有下一级节点或者找到路线。


Plurality properly introduced the concept of voting.

As a student unfamiliar with voting, Tideman's principle is interesting.

As a student unfamiliar with data structure, the 2-D data structure like matrix and graph, along with the adjacency matrix is interesting.

Besides the comprehension of the problem's description and the coding framework, the hardest part of the code should be judging whether there's a loop in the graph. This is a brilliant application of the recursive thinking taught. The guidance from lectures and problem is perfect, which make this problem a **great** one in the course.

Code thoughts: To find whether there's a route from a node to a given node, one can search every next node current node pointing to, and recurse until an end node or finding the route.