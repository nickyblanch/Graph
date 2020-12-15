#ifndef GRAPH
#define GRAPH
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <stack>
#include <fstream>


// Forward declaration of Edge class
template <class T>
class Edge;






template <class T>
class Graph {
	/* THIS IS AN ABSTRACT BASE CLASS AND SHOULD NOT BE INSTANTIATED
	 This class represents a general graph. This graph is implemented
	 in an adjacency list format. This general base class is templated
	 so that it may store metadata (commonly edge weight) of any
	 data type, including user-defined types. The metadata type is
	 a parameter of the class (shown as 'T' in my code). Because this
	 base class is generalized, there are no requirements for what the
	 metadata must be; however, if the user provides a user-defined
	 struct or class as the template parameter, then the included
	 print_graph() function will not work correctly. The user would
	 need to create their own print function within the derived class.*/
public:
	// Default constructor
	Graph() { this->N = 0; };

	// Parameterized constructor
	Graph(std::vector<Edge<T>> in_vec, unsigned int size) {
		this->adj_list.resize(size);
		this->N = size;
		for (unsigned int i = 0; i < in_vec.size(); i++) {
			this->add_edge(in_vec[i]);
		}
	};

	// Add an edge to the graph
	void add_edge(Edge<T> new_edge);

	// Overloaded funcion to add an edge to the graph
	void add_edge(unsigned int source, unsigned int destination, T metadata);

	// Overloaded funcion to add an edge to the graph
	void add_edge(unsigned int source, unsigned int destination);

	// Scan an input file to load the graph (virtual function)
	virtual void load_graph() = 0;

	// Run the implemented graph search algorithm (virtual function)
	virtual std::list<unsigned int> run_algorithm(unsigned int start_node, unsigned int end_node) = 0;

	//DEBUG:
	void print_graph() {
		for (unsigned int i = 0; i < this->adj_list.size(); i++) {
			for (unsigned int j = 0; j < this->adj_list[i].size(); j++) {
				std::cout << "Source: " << this->adj_list[i][j].source << " Destination: " << this->adj_list[i][j].destination << " Metadata: " << this->adj_list[i][j].meta_data << std::endl;
			}
		}
	}

protected:
	// This 'adjacency list' is actually a vector of vectors, instead of
	// the traditional array of lists. However, the funtionality is still
	// the same, with the added benefit of it being easily resizeable.
	std::vector<std::vector<Edge<T>>> adj_list;

	// Number of nodes
	unsigned int N;
};


template <class T>
void Graph<T>::add_edge(Edge<T> new_edge) {
	// Due to the adjacency list representation, each 'node' is considered
	// to be an integer between 0 and the length of the adjacency list. The
	// nodes must be continuous, because we cannot leave a gap in our adjacency
	// list, at least as it is currently implemented with vectors.

	// If either node is not included in the adjacency list, resize
	while (new_edge.source >= this->N || new_edge.destination >= this->N) {
		this->adj_list.resize(this->N + 1);
		this->N = this->N + 1;
	}

	// Add the new edge
	this->adj_list[new_edge.source].push_back(new_edge);
};

// Overloaded funcion to add an edge to the graph
template <class T>
void Graph<T>::add_edge(unsigned int source, unsigned int destination, T metadata) {
	// If either node is not included in the adjacency list, resize
	while (source >= this->N || destination >= this->N) {
		this->adj_list.resize(this->N + 1);
		this->N = this->N + 1;
	}

	// Add the new edge
	Edge<T>* temp = new Edge<T>;
	temp->source = source;
	temp->destination = destination;
	temp->meta_data = metadata;
	this->adj_list[temp->source].push_back(*temp);
};

// Overloaded funcion to add an edge to the graph
template <class T>
void Graph<T>::add_edge(unsigned int source, unsigned int destination) {
	// If either node is not included in the adjacency list, resize
	while (source >= this->N || destination >= this->N) {
		this->adj_list.resize(this->N + 1);
		this->N = this->N + 1;
	}

	// Add the new edge
	Edge<T>* temp = new Edge<T>;
	temp->source = source;
	temp->destination = destination;
	this->adj_list[temp->source].push_back(*temp);
};






template <class T>
class Edge {
	// This class represents the edges of the graph.
	// As mentioned in the above class declaration, it
	// has a template parameter that tells it what type
	// of data to store.
public:
	int source, destination;
	T meta_data;
};





// Struct to hold metadata for the maze_graph class
struct T_MetaData {
	int int_data;
	std::string string_data;
};


// Derived class implementing the maze problem (with user-defined struct as metadata template parameter)
class maze_graph : public Graph<T_MetaData> {
	// This is the derived class that inherits from the abstract
	// base class Graph. 
	// This approach is very useful because the same Graph
	// and Edge classes could be used for many, many different
	// problems that require storing different types of data
	// and doing different operations.
	// I could reuse these same classes for a problem in which
	// I need to store string data, as well as in a problem
	// in which I need to store a user struct.  All I would
	// need to do is create a derived class and define
	// any overrided functions. The code reuse posibilities are endless.
public:
	// Maze graph constructor
	maze_graph(char in_search_char, char in_end_char, char in_start_char, std::vector<Edge<T_MetaData>> in_vec, unsigned int size) {
		this->search_char = in_search_char;
		this->end_char = in_end_char;
		this->start_char = in_start_char;

		this->adj_list.resize(size);
		this->N = size;
		for (unsigned int i = 0; i < in_vec.size(); i++) {
			this->add_edge(in_vec[i]);
		}
	}
	
	// Overloaded constructor
	maze_graph(char in_search_char, char in_end_char, char in_start_char) {
		this->search_char = in_search_char;
		this->end_char = in_end_char;
		this->start_char = in_start_char;
		this->N = 0;
	}

	// Default constructor
	maze_graph() {
		this->N = 0; 
		this->search_char = '\0';
		this->end_char = '\0';
		this->start_char = '\0';
	}

	// Print graph (OVERRIDE)
	void print_graph() {
		for (unsigned int i = 0; i < this->adj_list.size(); i++) {
			for (unsigned int j = 0; j < this->adj_list[i].size(); j++) {
				std::cout << "Source: " << this->adj_list[i][j].source << " Destination: " << this->adj_list[i][j].destination << " Metadata: " << this->adj_list[i][j].meta_data.int_data << " " << this->adj_list[i][j].meta_data.string_data << std::endl;
			}
		}
	}

	// Load the graph from an input file (OVERRIDE)
	void load_graph();
	
	// Search algorithm to find a path through the maze (OVERRIDE)
	std::list<unsigned int> run_algorithm(unsigned int start_node, unsigned int end_node);

	// Depth first search algorithm
	std::list<unsigned int> DFS(std::stack<unsigned int> in_stack, std::list<unsigned int> path, unsigned int end_node);

	// Print the new, solved maze
	void print_maze(std::list<unsigned int>);


	// MEMBERS UNIQUE TO THE DERIVED CLASS
	// 'Path' character to follow, in the maze
	char search_char;
	// 'End' character to end at, in the maze
	char end_char;
	// 'Start' character to start at, in the maze
	char start_char;
	// Integer identifier of the starting node
	unsigned int start_node;
	// Integer identifier of the ending node
	unsigned int end_node;
	// Width of the maze
	unsigned int maze_width;
	// Vector that stores the maze after it is read from a file
	std::vector<std::vector<char>> maze;

	// MEMBERS INHERITED FROM THE BASE CLASS (REMINDER)
	// unsigned int N;
	// std::vector<std::vector<Edge<T>>> adj_list;
};


// Maze graph algorithm function definitions
std::list<unsigned int> maze_graph::DFS(std::stack<unsigned int> in_stack, std::list<unsigned int> path, unsigned int end_node) {
	/*
	Disclaimer: In my testing, I have found that this function does not respond well to graphs with loops in them (example: 3->4, 4->2, 2->3).
	More often than not, running this DFS on this type of graph will result in a stack overflow.
	*/

	// Stores current node
	unsigned int curr_node = 0;

	// Check if the stack is empty (occurrs when we reach the end of a path without finding the end node)
	if (in_stack.empty()) {
		return *(new std::list<unsigned int>);
	}

	// Add top stack element to path
	path.push_back(in_stack.top());

	// Check to see if we have reached the end node
	if (in_stack.top() == end_node) {
		return path;
	}

	// Remove top stack element
	curr_node = in_stack.top();
	in_stack.pop();

	int run = 1;
	// Add nodes connected to the node we just removed
	// If we have more than one path, create a new stack for each path so that we can try all of them
	for (unsigned int i = 0; i < this->adj_list[curr_node].size(); i++) {
		// Check to see if we have already seen the node we are about to add
		run = 1;
		for (std::list<unsigned int>::iterator k = path.begin(); k != path.end(); ++k) {
			if (*k == this->adj_list[curr_node][i].destination) {
				run = 0;
			}
		}
		if (run == 1) {
			// If we have not already visited this node:
			in_stack.push(this->adj_list[curr_node][i].destination);
			std::list<unsigned int> path_temp = DFS(in_stack, path, end_node);

			// If this resursive call found the end node, return this path!
			if (!path_temp.empty()) {
				return path_temp;
			}
		}
	}

	// If no path is return yet (the maze is unsolvable):
	return *(new std::list<unsigned int>);
};


std::list<unsigned int> maze_graph::run_algorithm(unsigned int start_node, unsigned int end_node) {
	// CREATE STACK
	std::stack<unsigned int> start_stack;
	start_stack.push(start_node);

	// CREATE LIST OF VISITED NODES ("PATH")
	std::list<unsigned int> path;

	// CALL DFS FUNCTION
	return DFS(start_stack, path, end_node);
};


void maze_graph::load_graph() {
	int count = 0;
	// Open input file
	std::ifstream maze_file("maze.txt");

	// Temp variables used to store file data
	char char_temp;
	std::vector<char> vec_temp;

	// Fill maze vector with file data
	while (maze_file.get(char_temp)) {
		// Store maze in the array
		if (char_temp != '\n') {
			vec_temp.push_back(char_temp);
			count++;
		}
		else {
			this->maze.push_back(vec_temp);
			vec_temp.resize(0);
			this->maze_width = count;
			count = 0;
		}
	}
	// Add final vector
	this->maze.push_back(vec_temp);

	// DEBUG: PRINT MAZE
	std::cout << "Rows: " << this->maze.size() << " Columns: " << this->maze[0].size() << std::endl;
	for (int i = 0; i < this->maze.size(); i++) {
		for (int j = 0; j < this->maze[i].size(); j++) {
			std::cout << this->maze[i][j];
		}
		std::cout << std::endl;
	}
	
	// Add edges to adjacency list
	for (unsigned int i = 0; i < this->maze.size(); i++) {
		for (unsigned int j = 0; j < this->maze[i].size(); j++) {
			char_temp = this->maze[i][j];

			if (char_temp == this->start_char) {
				// Add the starting node to the adjacency list (also assume that the node underneath it is connected)
				this->start_node = this->maze_width * i + j;
				this->add_edge(this->start_node, this->maze_width * (i + 1) + j);
			}
			else if (char_temp == this->end_char) {
				this->end_node = this->maze_width * i + j;
			}
			else if (char_temp == this->search_char || char_temp == this->start_char) {
				// Check to see if any of the surrounding nodes are also path characters
				if (this->maze[i][j - 1] == this->search_char || this->maze[i][j - 1] == this->end_char) {
					this->add_edge(this->maze_width * i + j, this->maze_width * i + j - 1);
				}
				if (this->maze[i][j + 1] == this->search_char || this->maze[i][j + 1] == this->end_char) {
					this->add_edge(this->maze_width * i + j, this->maze_width * i + j + 1);
				}
				if (this->maze[i-1][j] == this->search_char || this->maze[i - 1][j] == end_char) {
					this->add_edge(this->maze_width * i + j, this->maze_width * (i-1) + j);
				}
				if (this->maze[i + 1][j] == this->search_char || this->maze[i + 1][j] == this->end_char) {
					this->add_edge(this->maze_width * i + j, this->maze_width * (i + 1) + j);
				}
			}
		}

	}
};



void maze_graph::print_maze(std::list<unsigned int> in_list) {
	int solution = 0;
	for (unsigned int i = 0; i < this->maze.size(); i++) {
		for (unsigned int j = 0; j < this->maze[i].size(); j++) {
			// Check to see if this is a coordinate that is part of the solution
			solution = 0;
			for (std::list<unsigned int>::iterator k = in_list.begin(); k != in_list.end(); ++k) {
				if (*k == (i * this->maze_width + j) && (i * this->maze_width + j) != this->start_node && (i * this->maze_width + j) != this->end_node) {
					solution = 1;
				}
			}
			// If the coordinate is part of the solution, print a "+"
			if (solution == 1) {
				std::cout << "+";
			}
			else {
				std::cout << this->maze[i][j];
			}
		}
		// After each line, print a newline
		std::cout << std::endl;
	}
}

#endif





// IMPLEMENTATION EXPLANATION
/*
I chose to implement a graph using an adjacency list because it allows me to store
lots of data, store data of any type I want, and leads to the highest reusability possible.
My other main option was to implement the graph as an adjacency matrix; however, this
approach would strictly limit the amount of data that I could store. If I used the most
common implementation of an adjacency matrix, then I would not be able to store anything
more than one piece of metadata per edge on the graph. In addition, I would realistically
be limited to this metadata being of an integer type because it traditionally represents
if there is an edge between two nodes or not (a 0 or 1). For the maze problem that I intend
to solve, as well as for most other conceivable graph search problems, my adjacency list
representation is better than an adjacency matrix representation because it allows me to store
unlimited amounts of metadata, and this metadata can be of any type the user wants (including
user defined types). This additionally yields itself to a higher degree of code reusability,
because I can store different types of metadata for different problems.
*/

// GRAPH SEARCH ALGORITHMS
/*
For my class maze_graph : public Graph<T>, a depth first search would look like:

	void run_algorithm(int start_node, int end_node) {
		// CREATE STACK
		stack<int> stack;
		start_stack.push(start_node);

		// CREATE LIST OF VISITED NODES ("PATH")
		list<int> path;

		// CALL DFS FUNCTION
		DFS(start_stack, path);
	}

	// Returns a std::list of the correct path directly from the start node to the end node
	std::list DFS(in_stack, path, end_node) {
		// Stores current node
		int curr_node;

		// Check if the stack is empty (occurs when we reach the end of a path without finding the end node)
		if (stack is empty)
			return empty path;
		}

		// Add top stack element to path
		path.push_back(stack.top());

		// Check to see if we have reached the end node
		if (stack.top() == end_node) {
			return path;
		}

		// Remove top stack element
		curr_node = stack.top();
		stack.pop();

		// Add nodes connected to the node we just removed
		// If we have more than one path, create a new stack for each path so that we can try all of them
		for (int i = 0; i < number of nodes connected to current node; i++) {
			path_temp = DFS(stack.push(this->adj_list[curr_node][i]), path, end_node);

			// If this recursive call found the end node, return this path!
			if (!path_temp.empty()) {
				return path_temp;
			}
		}

		// If no path is return yet (the maze is unsolvable):
		return empty path;
	}

For my class maze_graph : public Graph<T>, a breadth first search would look very similar to a depth first search.
We would begin with the same run_algorithm(start node, end node) function, but we would need a function
called BFS. The largest difference between the DFS implementation and the BFS implementation would be using
a stack in DFS and a queue in BFS. (because this is pseudocode, I did not really worry about getting the 
exact std::queue method names correct)

	// Returns a list of the correct path directly from the start node to the end node
	std::list BFS(queue, path, end_node) {
		// Stores current node
		int curr_node;

		// Check if the queue is empty (occurs when we reach the end of a path without finding the end node)
		if (queue is empty)
			return empty path;
		}

		// Add bottom queue element to path
		path.push_back(queue.bottom());

		// Check to see if we have reached the end node
		if (queue.bottom() == end_node) {
			return path;
		}

		// Remove bottom queue element
		curr_node = queue.top();
		queue.pop();

		// Add nodes connected to the node we just removed
		// If we have more than one path, create a new stack for each path so that we can try all of them
		for (int i = 0; i < number of nodes connected to current node; i++) {
			path_temp = BFS(queue.push(this->adj_list[curr_node][i]), path, end_node);

			// If this recursive call found the end node, return this path!
			if (!path_temp.empty()) {
				return path_temp;
			}
		}

		// If no path is return yet (the maze is unsolvable):
		return empty path;
	}


*/