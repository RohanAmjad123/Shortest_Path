/**
 * @file main.cpp
 * @author Rohan Amjad
 * @brief 
 * @version 0.1
 * @date 2021-11-19
 * 
 * 
 */

#include "iostream"
#include "graph.h"

int main(int argc, char *argv[]) 
{   
    // create Graph object using test.txt 
    Graph g("./test.txt");
    // print shortest path from Calgary (YYC) to Toronto (YYZ) 
    std::cout << g.shortest_path("YYC", "YYZ");
    // print shortest path from Calgary (YYC) to Montreal (YUL)
    std::cout << g.shortest_path("YYC", "YUL");
    // print shortest path from Calgary (YYC) to Vancouver (YVR)
    std::cout << g.shortest_path("YYC", "YVR");
    //g.print_graph();
    //g.print_node_map();
    return 0;
}