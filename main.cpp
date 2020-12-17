#include "graph.hpp"
#include <string.h>

using std::string;

int main(int argc, char** argv) {

	// Verify the correct command line arguments are given
	if (argc < 4) {
		std::cout << "Incorrect number of command line arguments given. Exiting." << std::endl;
		return -1;
	}

	

	//
	// DEBUG
	//

	// Test graph
	std::cout << "Constructing example graph with T_MetaData (user-defined struct) metadata. Edges are:" << std::endl;
	std::vector<Edge<T_MetaData>> test_vec;
	for (int i = 2; i < 5; i++) {
		Edge<T_MetaData>* temp = new Edge<T_MetaData>;
		temp->source = i;
		temp->destination = i + 1;
		temp->meta_data.string_data = "test";
		temp->meta_data.int_data = i;
		test_vec.push_back(*temp);
	}
	Edge<T_MetaData>* temp = new Edge<T_MetaData>;
	temp->source = 5;
	temp->destination = 1;
	temp->meta_data.int_data = 5;
	temp->meta_data.string_data = "maze";
	test_vec.push_back(*temp);
	temp = new Edge<T_MetaData>;
	temp->source = 1;
	temp->destination = 0;
	temp->meta_data.int_data = 1;
	temp->meta_data.string_data = "maze";
	test_vec.push_back(*temp);
	temp = new Edge<T_MetaData>;
	temp->source = 0;
	temp->destination = 8;
	temp->meta_data.int_data = 0;
	temp->meta_data.string_data = "maze";
	test_vec.push_back(*temp);
	temp = new Edge<T_MetaData>;
	temp->source = 8;
	temp->destination = 10;
	temp->meta_data.int_data = 8;
	temp->meta_data.string_data = "maze";
	test_vec.push_back(*temp);

	// Print the graph
	maze_graph* test_graph = new maze_graph(**(argv + 1), **(argv + 2), **(argv + 3), test_vec, 3);
	test_graph->print_graph();

	std::cout << std::endl << "Press any key to continue." << std::endl;
	std::cin.ignore();

	// Print divider
	std::cout << "_____________________________________________" << std::endl << std::endl;

	// Run algorithm
	std::cout << "Running a search algorithm on the graph storing integer metadata. Starting at node 2, looking for node 10. The correct sequence to follow is:" << std::endl;
	std::list<unsigned int> my_list = test_graph->run_algorithm(2, 10);

	// Print algorithm result
	std::cout << "Start";
	for (std::list<unsigned int>::iterator i = my_list.begin(); i != my_list.end(); ++i)
		std::cout << "->" << *i;
	std::cout << std::endl;

	std::cout << std::endl << "Press any key to continue." << std::endl;
	std::cin.ignore();

	// Print divider
	std::cout << "_____________________________________________" << std::endl << std::endl;
	std::cout << "MAZE SOLVING TEST" << std::endl;

	// Scan in maze
	maze_graph* test_graph_maze = new maze_graph(**(argv + 1), **(argv + 2), **(argv + 3));
	test_graph_maze->load_graph();

	// Print graph
	//test_graph_maze->print_graph();

	// Run algorithm
	std::cout << "Running a search algorithm on the maze. The correct sequence to follow is:" << std::endl;
	my_list = test_graph_maze->run_algorithm(test_graph_maze->start_node, test_graph_maze->end_node);

	// Print algorithm result
	std::cout << "Start: ";
	for (std::list<unsigned int>::iterator i = my_list.begin(); i != my_list.end(); ++i)
		std::cout << "->" << *i;
	std::cout << std::endl;

	// Print solved maze
	test_graph_maze->print_maze(my_list);


	std::cout << std::endl <<  "Press any key to continue." << std::endl;
	std::cin.ignore();
	return 0;
}