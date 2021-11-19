/**
 * @file graph.h
 * @author Rohan Amjad
 * @brief 
 * @version 0.1
 * @date 2021-11-19
 * 
 * 
 */

#ifndef GRAPH
#define GRAPH

#include <vector>
#include <string>
#include <map>

typedef std::vector<std::vector<int> > int_matrix;
typedef std::vector<std::vector<std::string> > string_matrix;
typedef std::map<std::string, int> node_map;
typedef std::map<int, std::string> rvs_node_map;


/**
 * @brief Implementation of a Graph data structure. 
 * 
 * Includes methods to: 
 * - find shortest path between two nodes 
 * - parse edge data from a text file
 * - print parsed edge data
 * - print the Graph's adjacency matrix
 * - print the Graph's node map
 * 
 */
class Graph
{
public:
    /**
     * @brief Default constructor to construct a new Graph object 
     * 
     */
    Graph();
    
    /**
     * @brief Construct a new Graph object by reading data from a file
     * 
     * @param file_path 
     */
    Graph(std::string file_path);
    
    /**
     * @brief Dijkstra's Algorithm to find the shortest path between two nodes in the Graph
     * 
     * @param start_node starting node's name
     * @param end_node ending node's name
     * @return std::string a with the format {cost hops shortest_path}
     */
    std::string shortest_path(std::string start_node, std::string end_node);
    
    /**
     * @brief Print the Graph's adjacency matrix
     * 
     */
    void print_graph() const;

    /**
     * @brief Print the Graph's node map
     * 
     */
    void print_node_map() const;

    /**
     * @brief Parse edge data from a text file into a string_matrix
     * 
     * @param file_path 
     * @return string_matrix that holds parsed edge data
     */
    static string_matrix parse_file(std::string file_path);

    /**
     * @brief Print the parsed edge data
     * 
     * @param m string_matrix that holds parsed edge data
     */
    static void print_parsed_file(const string_matrix &m);

private:
    /**
     * @brief Add all nodes from data to the Graph's node_map
     * 
     * @param data a string_matrix that holds parsed edge data
     */
    void add_nodes(const string_matrix data);
    
    /**
     * @brief Add an edge to the Graph's adjacency matrix
     * 
     * @param node_1 the first node's name
     * @param node_2 the second node's name
     * @param weight the weight of the edge connecting node_1 and node_2
     */
    void add_edge(std::string node_1, std::string node_2, int weight);
    
    /**
     * @brief Get the node name and its index in a pair
     * 
     * @param n the name of the node
     * @return std::pair<std::string, int> a pair that holds the node name and its respective index in the adjacency list
     */
    std::pair<std::string, int> get_node(std::string n) const;
    
    /**
     * @brief Get the node name and its index in a pair
     * 
     * @param index the index of the node
     * @return std::pair<std::string, int> a pair that holds the node name and its respective index in the adjacency list
     */
    std::pair<std::string, int> get_node(int index) const;

    /// an adjacency matrix that holds the Graph's data
    int_matrix adj_matrix;
    /// a node map that maps each node name to its respective index in the adjacency matrix
    node_map nodes;
    /// a reverse node map that maps the index in the adjacency matrix to its respective node name
    rvs_node_map nodes_rvs;
    /// the number of nodes in the Graph
    int num_nodes;
};

#endif
