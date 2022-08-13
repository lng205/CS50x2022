[Course station](https://cs50.harvard.edu/x/2022/)

# Summary

This is a course for CS beginners. I've completed several embedded projects with C before the course, also I've been learning python through half of [this blog](https://www.liaoxuefeng.com/wiki/1016959663602400).

Thinking as a review, the course surprised me. The C part greatly deepened my understanding of the language. Moreover, the Web application part opened a new world for me. Recommended.

The course took me three weeks in total. Apart from the relaxing time, it's about a hundred hours, which is neither short nor quite long, compared with my steam gaming hours. The feeling of study is pretty well.

Choose [Nand2Tetris](https://github.com/lng205/Nand2Tetris) as my next course. With complete and open-sourced material, the course has been dubbed 'CS101'. The textbook had just been republished in 2021. The course only requires commanding a high-level language for the latter half, and CS50x is sufficient.

# Snippets&Review

## Week 0

Though scratch is the starting point of the course, skipping it won't affect further study much. Thus students with programming basics could skip this part.


## Week 1

The digit's algorithm in credit is quite interesting, using the bit operating technique of integer.


## Week 2

The three functions in readability walk through the text three times, resulting in inefficiency. But the framework was given three functions in it, probably for check50 and simpler design.


## Week 3

Plurality properly introduced the concept of voting.

As a student unfamiliar with voting, Tideman's principle is interesting.

As a student unfamiliar with data structure, the 2-D data structure like matrix and graph, along with the adjacency matrix is interesting.

Besides the comprehension of the problem's description and the coding framework, the hardest part of the code should be judging whether there's a loop in the graph. This is a brilliant application of the recursive thinking taught. The guidance from lectures and problem is perfect, which make this problem a **great** one in the course.

Code thoughts: To find whether there's a route from a node to a given node, one can search every next node current node pointing to, and recurse until an end node or finding the route.


## Week 4

Filter and volume are image and audio processing respectively. Having done quite a few similar labs with Matlab and FPGA, I'm familiar with the principles.

There are lots of tedious repetitions in the code which may require some improvement. The cumbersome in this problem might be emphasizing the benefits of python.

Recover is an application of data recovery which is pretty interesting.

The problem set contains projects with multiple C files, helpful to deepen the understanding of library, linking and compiling.


## Week 5

Inheritance is a simulation of blood type inheritance and an application of recursion, though not as fun as tideman.

Speller has some difficulty as the last problem in C. The framework given is a hash tree based on prefix alphas. A trie might offer a faster speed.

Code thoughts: Map the dictionary based on the first several characters. The mapping function is the order in the alphabet. The single quote should be taken into consideration.

There's not much improvement when changing from two characters prefix to three, let alone four. The final total running time is still 0.1 sec slower than the staff's solution.

The texts provided are all very classic, including a selection from *Dream of the Red Chamber*.


## Week 6
The first lecture in Python. The problem set includes the reimplementation of previous problems and two new ones.

Python's grammar is much more user-friendly while needs to memorize more stuff.

The new problems include data processing with CSV files which foreshadows the SQL.


## Week 7

Movies and songs used data from real databases and are interesting.

Fiftyville is **highly recommended** to all SQL beginners.

With elegant design and moderate difficulty, solving the problem is as fun as playing games. Could be made into an independent game.


## Week 8
Open-ended problems are annoying.

Took quite a whole day skimming through the HTML, CSS and JS tutorials on W3Shools, and also read about the tutorials of bootstrap and W3.CSS. Front-end stuff is complicated.

Made a homepage and a navbar for my resource station. Might share the project after completion.


## Week 9

Web application development. **Another excellent problem**, Including the front-end and back-end, using Python with Flask and SQL, chains the latter half of the course into a whole.

Modify the code framework a lot thinking there's no check50. Used the flash function provided by Flask based on the session, but was unable to pass check50, having to change back to the given framework, which is an unsatisfying experience.


## Week 10

Plan to build a personal resource station.

Familiar with Linux after the course, I tried to use WSL and Docker, but was not satisfied with them. So I turned to my Raspberri pi 4B on hand. I've successfully moved the project of Week9 to it and ran it on my campus LAN.

With remote development via VScode, Raspberri pi can be free from screen, mouse and keyboard, making the device useful again.

Might share the project of Raspberri pi remote Webapp development in the future.

# Gradebook
![p1](./images/p1.png)