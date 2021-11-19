/**
 * @file graph.cpp
 * @author Rohan Amjad
 * @brief 
 * @version 0.1
 * @date 2021-11-19
 * 
 * 
 */

#include "graph.h"
#include <iostream>
#include <fstream>
#include <limits.h>

Graph::Graph() : num_nodes(0) {}

Graph::Graph(std::string file_path) : num_nodes(0)
{
    string_matrix parsed_data = parse_file(file_path);
    string_matrix::iterator row;
    add_nodes(parsed_data);

    this->adj_matrix.resize(this->num_nodes, std::vector<int>(this->num_nodes, 0));

    for (row = parsed_data.begin(); row != parsed_data.end(); row++)
    {
        add_edge(row->at(0), row->at(1), stoi(row->at(2)));
    }
}

std::string Graph::shortest_path(std::string start_node, std::string end_node)
{
    // transform start_node and end_node's names to upper case
    std::transform(start_node.begin(), start_node.end(), start_node.begin(), ::toupper);
    std::transform(end_node.begin(), end_node.end(), end_node.begin(), ::toupper);

    // vector holding the shortest distances between start_node and every other node in the graph
    std::vector<int> shortest_distances(this->num_nodes, INT_MAX);
    // vector holding bool values for each nodes index based on if it has been added to the shortest_distance vector or not
    std::vector<bool> added(this->num_nodes, false);
    // vector holding the index of the parent of each node at its respective index
    std::vector<int> parents(this->num_nodes);
    
    // number of vertices in the Graph
    int n_vertices = this->num_nodes;
    // index of the start_node
    int startVertex = get_node(start_node).second;

    // set the shortest_distance to 0 for the starting node
    shortest_distances[startVertex] = 0;
    // set the parent of the starting node to -1 (no parent)
    parents[startVertex] = -1;

    // Dijktra's Algorithm that finds the shortest_distances of each node in the graph from start_node 
    for (int i = 0; i < n_vertices; i++) 
    {   
        // find the minimum distance vertex that has not yet been added
        int nearest_vertex = -1;
        int shortest_distance = INT_MAX;
        for (int vert_ind = 0; vert_ind < n_vertices; vert_ind++) 
        {
            if (!added[vert_ind] && shortest_distances[vert_ind] < shortest_distance) 
            {
                nearest_vertex = vert_ind;
                shortest_distance = shortest_distances[vert_ind];
            }
        }

        // set the nearest vertex as added
        added[nearest_vertex] = true;

        // update the distance of the adjacent vertices
        for (int vert_ind = 0; vert_ind < n_vertices; vert_ind++) 
        {
            int edge_dist = this->adj_matrix[nearest_vertex][vert_ind];
            
            if (edge_dist > 0 && (shortest_distance + edge_dist < shortest_distances[vert_ind])) 
            {
                parents[vert_ind] = nearest_vertex;
                shortest_distances[vert_ind] = shortest_distance + edge_dist;
            }
        }
    }

    // construct the path string using the calculated shortest_distances
    int vert = get_node(end_node).second;
    int cost = shortest_distances[vert];
    int hops = 0;
    std::string path = "";
    path.insert(0, get_node(vert).first + "\n");
    vert = parents[vert];
    while (vert != -1) 
    {
        path.insert(0, get_node(vert).first + "-->");
        hops++;
        vert = parents[vert];
    }
    path.insert(0, std::to_string(hops) + " ");
    path.insert(0, std::to_string(cost) + " "); 

    return path;
}

void Graph::print_graph() const
{
    std::cout << "--- ";
    for (int i = 0; i < this->num_nodes; i++) 
    {
        std::cout << get_node(i).first << "\t";
    }
    std::cout << std::endl;
    for (int i = 0; i < adj_matrix.size(); i++)
    {
        std::cout << get_node(i).first << " ";
        for (int j = 0; j < adj_matrix[i].size(); j++)
        {
            std::cout << adj_matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

void Graph::print_node_map() const
{
    for (int i = 0; i < this->num_nodes; i++)
    {
        std::pair<std::string, int> node = get_node(i);
        std::cout << node.first << "\tIndex: " << node.second << "\n";
    }
}

string_matrix Graph::parse_file(std::string file_path)
{
    string_matrix parsed_data;
    std::ifstream file(file_path);
    std::string curr_str;

    while (std::getline(file, curr_str))
    {
        std::vector<std::string> tmp_vect;
        std::string tmp_str = "";
        for (int i = 0; i < curr_str.length(); i++)
        {
            if (curr_str[i] == ' ' || curr_str[i] == '\n')
            {
                tmp_vect.push_back(tmp_str);
                tmp_str = "";
            }
            else
            {
                tmp_str.push_back(curr_str[i]);
            }
        }
        tmp_vect.push_back(tmp_str);

        parsed_data.push_back(tmp_vect);
    }

    return parsed_data;
}

void Graph::print_parsed_file(const string_matrix &m)
{
    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < m[i].size(); j++)
        {
            std::cout << m[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

void Graph::add_nodes(const string_matrix data)
{
    string_matrix::const_iterator it;
    std::pair<node_map::iterator, bool> ins;

    for (it = data.begin(); it != data.end(); it++)
    {
        ins = this->nodes.insert(std::make_pair(it->at(0), this->num_nodes));
        if (ins.second)
        {
            this->nodes_rvs.insert(std::make_pair(this->num_nodes, it->at(0)));
            num_nodes++;
        }

        ins = this->nodes.insert(std::make_pair(it->at(1), this->num_nodes));
        if (ins.second)
        {
            this->nodes_rvs.insert(std::make_pair(this->num_nodes, it->at(1)));
            num_nodes++;
        }
    }
}

void Graph::add_edge(std::string node_1, std::string node_2, int weight)
{
    int index_1 = get_node(node_1).second;
    int index_2 = get_node(node_2).second;

    if (index_1 != -1 && index_2 != -1)
    {
        this->adj_matrix[index_1][index_2] = weight;
        this->adj_matrix[index_2][index_1] = weight;
    }
    else
    {
        fprintf(stderr, "Failed to add edge to graph!\n");
        exit(1);
    }
}

std::pair<std::string, int> Graph::get_node(std::string n) const
{
    std::pair<std::string, int> node;

    node_map::const_iterator it;

    it = this->nodes.find(n);

    if (it != this->nodes.end())
    {
        node = std::make_pair(it->first, it->second);
    }

    return node;
}

std::pair<std::string, int> Graph::get_node(int index) const
{
    std::pair<std::string, int> node;

    rvs_node_map::const_iterator it;

    it = this->nodes_rvs.find(index);

    if (it != this->nodes_rvs.end())
    {
        node = std::make_pair(it->second, it->first);
    }

    return node;
}