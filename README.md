# Graph
C++ Graph Implementation (Adjacency list, DFS)
Compilation Instructions
The program will compile on the C++17 standard, and it will possibly compile on older standards. To run the included main.cpp file, please enter three single character command line arguments. The maze_graph class needs these three command line arguments because they represent the starting character, ending character, and path character. These parameters are required to solve an actual ASCII-based maze using this graph. To run a short demo, enter ‘y’ when asked if the program should be run in debug mode.
If you want to test the classes and DFS with your own maze, please do, but keep in mind that you must update the command line arguments to reflect the characters used in your maze. The format is: <path character> <ending character> <starting character>. Also, the maze must be in a .txt file named “maze.txt” and located local to the program. The maze search has worked with every maze I have tried, regardless of size.
To run the included maze (which will automatically happen if you use the included main.cpp), please enter the following command line arguments: @ x *.

Class Graph<T>
This class represents a general graph.  THIS IS AN ABSTRACT BASE CLASS AND CANNOT BE INSTANTIATED. This graph is implemented in an adjacency list format. This general base class is templated so that it may store metadata (commonly edge weight) of any data type, including user-defined types. The metadata type is a parameter of the class (shown as 'T' in my code). Having the metadata type be a template parameter is highly beneficial because it lends my code to a large variety of problems; specific problems require storing specific types of metadata, but because the type of metadata can be chosen, my code can be used for a variety of problems. Because this base class is generalized, there are no requirements for what the metadata must be; however, if the user provides a user-defined struct or class as the template parameter, then the include print_graph() function (in the base class) will not work correctly. The user would need to override the print_graph() function within the derived class. This also applies to some STL containers such as list, stack, queue, vector, and more.

Class Edge<T>
This class represents the edges connecting the nodes of the graph. As mentioned above, this class has a template parameter that allows it to store metadata of any type. Each edge object stores the integer identifier of the source node, the integer identifier of the destination node, and metadata (usually edge weight).

Class maze_graph : public Graph<T_MetaData>
This is a derived class that inherits publicly from the abstract base class Graph<T>. This base class is specialized for the purpose of solving an ASCII-based maze (think of a maze made up of characters like #, /, and &). The <T_MetaData> argument means that my maze_graph class will be a graph that stores metadata of type T_MetaData, which is a user-defined struct I implemented in the graph.hpp file. To aid in its purpose of solving a maze, this class stores specific data, including the character that marks the starting point of the maze, the character that marks the ending point of the maze, and the character that marks the traversable part of the maze. This class overrides three functions declared within the Graph base class. Within this class, I implemented a functioning DFS (depth first search) function that is able to scan the graph for a path from the starting node to the ending node and then return an std::list of all the moves from the starting node to the ending node. For a demonstration, compile main.cpp and enter ‘y’ when asked if the program should be run in debug mode.

Implementation Explanation
I chose to implement a graph using an adjacency list because it allows me to store lots of data, store data of any type I want, and leads to the highest code reusability possible. My other main option was to implement the graph as an adjacency matrix; however, this approach would strictly limit the amount of data that I could store. If I used the most common implementation of an adjacency matrix, then I would not be able to store anything more than one piece of metadata per edge on the graph. In addition, I would realistically be limited to this metadata being of an integer type because it traditionally represents if there is an edge between two nodes or not (a 0 or 1). For the maze problem that I intend to solve, as well as for most other conceivable graph search problems, my adjacency list representation is better than an adjacency matrix representation because it allows me to store unlimited amounts of metadata, and this metadata can be of any type the user wants (including user defined types). This additionally yields itself to a higher degree of code reusability, because I can store different types of metadata for different problems.

