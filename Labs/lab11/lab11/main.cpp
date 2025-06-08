#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unordered_map>
#include "DfsTreeNode.h"

using namespace std;

// TASK: Build a graph using an adjacency matrix.
void buildGraph(vector<vector<int>> &graph, int graph_size, int num_connections)
{
    srand(time(NULL));

    //zero out graph and ensure that graph is large enough
    if (graph.size() < graph_size)
    {
        graph.resize(graph_size);
    }
    for (int i = 0; i < graph.size(); i++)
    {
        if (graph[i].size() < graph_size)
        {
			// resize number of rows we have
            graph[i].resize(graph_size);
        }
		// zero out the matrix 
        for (int j = 0; j < graph[i].size(); j++)
        {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < num_connections; i++)
    {
        int x = rand() % graph_size;
        int y = rand() % graph_size;
		// x and y are connected
        graph[x][y] = 1;
    }

	// zero out diagonal (do not allow self-connections)
	for (int i = 0; i < graph_size; i++)
	{
		graph[i][i] = 0; 
	}
}

// TASK: Build a depth-first search tree for a graph. 

/* MY SECTION'S LAB:
void buildDfsTree(
	vector<vector<int>>& graph, 
	int node, 
	int visit_order, 
	unordered_map<int, int>& visited
	)
{
	// Add node to visited. 
	visited[node]++; 

	// set diagonal to be our visit ID
	graph[node][node] = visit_order; 

	// For each outgoing node in our graph: 
	for (int i = 0; i < graph[node].size(); i++) // where size is 5 
												// (width of matrix)
	{
		// If this node is connected to item i
		if (graph[node][i] > 0)
		{
			//skip us
			if (i == node)
			{
				continue; 
			}
			// Have we seen this node? 
			if (visited[i] > 0) // if we have seen this node
			{
				// Do we have a larger ID (visit order) than the other node? 
				if (graph[node][node] > graph[i][i])
				{
					// If so, connect n and outgoing using a back edge. 
					graph[node][i] = -1;
				}
				else
				{
					graph[node][i] = 0; 
				}
			}
			else // if we have not seen the current node
			{
				// Repeat the process at the outgoing node. 
				// Remove child's connection to parent. 
				graph[i][node] = 0; // WHY NOT [node][i]?
				buildDfsTree(
					graph, 
					i, 
					visit_order + 1, 
					visited
				); 
			}
		}
	}
}
*/

// The second section's lab: 
void buildDfsTree(
	vector<vector<int>>& graph,
	int node,
	int visit_order,
	unordered_map<int, int>& visited
)
{
	// Add node to visited.
	visited[node]++;

	// Assign the diagonal the visit order. 
	graph[node][node] = visit_order; 

	for (int outgoing = 0; outgoing < graph[node].size(); outgoing++)
	{
		// avoid recursive call on same node
		if (node == outgoing)
		{
			continue; 
		}

		// if there is a connection between node and outgoing:
		if (graph[node][outgoing] > 0)
		{
			// if we've already seen the outgoing node
			if (visited[outgoing] > 0)
			{
				// create a directional back edge
				// this differs in that includes ALL back edges,
				// even "forward-going" ones
				graph[node][outgoing] = -1;
				
				// remove any edges going backward from outgoing to node
				// i.e. get rid of outgoing-->node
				graph[outgoing][node] = 0; 
			}
			else // if we haven't seen the outgoing edge yet
			{
				// turn edge(node, outgoing) into a directional edge
				// where node --> outgoing. 
				// i.e. get rid of outgoing-->node
				graph[outgoing][node] = 0; 
				visit_order++; 
				buildDfsTree(graph, outgoing, visit_order, visited); 
			}
		}
	}
	return;
}

// TASK: determine the articulation points in a graph.
// from last thursday's lecture - we created algorithm in class
// my section's version:
/* void getArticulationPoints(
	vector<vector<int>>& graph, 
	int node,
	unordered_map<int, int>& low_values,
	vector<int>& articulation_points) //node = starting location 
{
	// First: get low values

	// post-order traversal
	// children first
	for (int i = 0; i < graph.size(); i++)
	{
		if (i == node) // self-referential - this space contains visit ID
		{
			continue; 
		}
		else if (graph[node][i] > 0) // forward edge
		{
			getArticulationPoints(graph, i, low_values, articulation_points); 
		}
	}

	// process us
	int low = graph[node][node]; 

	// check for back edges
	for (int i = 0; i < graph[node].size(); i++)
	{
		if (i == node) // visiting ourselves?
		{
			continue; 
		}
		if (graph[node][i] < 0) // this edge is a back edge
		{
			// is this back edge better? 
			// if so:
			if (low > graph[i][i]) // id of back edge
			{
				// take our low value as our back edge's id value 
				low = graph[i][i]; 
			}
		}
		// is it better to take our back edge or to take a child's forward edge? 
		// go through each child
		else if (graph[node][i] > 0) // this edge is a forward edge 
		{
			// if our low is greater than our child's low
			if (low > low_values[i])
			{
				// take our child's low value
				low = low_values[i]; 
			}
		}
	}
	low_values[node] = low; 

	// Finally, we can determine if we're an articulation point
		// if we're the root w/ 2+ children, or 
		// if we have a child with a low value >= our id
	
		// are we the root? 
	if (graph[node][node] == 1)
	{
		int counter = 0; 
		for (int i = 0; i < graph[node].size(); i++)
		{
			if (node == i)
			{
				continue; 
			}
			if (graph[node][i] > 0)
			{
				counter++; 
			}
		}
		if (counter > 1)
		{
			articulation_points.push_back(node);
		}
	}

	// do we have a child with a low value >= our id?
	bool is_articulation = false; 
	for (int i = 0; i < graph[node].size(); i++)
	{
		if (i == node)
		{
			continue; 
		}
		if (graph[node][i] > 0) // forward edge to child
		{
			if (low_values[i] >= graph[node][node])
			{
				is_articulation = true;
				break;
			}
		}
	}
	if (is_articulation == true)
	{
		articulation_points.push_back(node);
	}
}*/

// The second section's version: 
void getArticulationPoints(
	vector<vector<int>>& graph,
	int node,
	unordered_map<int, int>& low_values,
	vector<int>& articulation_points
)
{
	// perform post-order traversal of our tree
	for (int outgoing = 0;
		outgoing < graph[node].size();
		outgoing++)
	{
		// ignore ourselves 
		if (outgoing == node)
		{
			continue; 
		}
		// if there is a forward edge between node and outgoing
		if (graph[node][outgoing] > 0)
		{
			// find the articulation points on outgoing 
			getArticulationPoints(
				graph,
				outgoing,
				low_values,
				articulation_points
			);
		}
	}

	// max low value is always equal to our ID value
	int low = graph[node][node]; 

	// examine OUR back edges and immediate children
	for (int outgoing = 0;
		outgoing < graph[node].size();
		outgoing++
		)
	{
		// ignore ourselves
		if (outgoing == node)
		{
			continue; 
		}
		// if we are connected to outgoing via a back edge
		if (graph[node][outgoing] < 0)
		{
			// does the back edge have a lower ID value?
			// if so, STEAL IT
			if (low > graph[outgoing][outgoing])
			{
				low = graph[outgoing][outgoing];
			}
		}
	}
}

int main(void)
{
    vector<vector<int>> graph{};

	// MY IDEA: build matrix manually 
	graph.push_back({ 0, 0, 0, 1, 0 }); 
	graph.push_back({ 0, 0, 1, 0, 1 }); 
	graph.push_back({ 1, 1, 0, 0, 1 });
	graph.push_back({ 1, 1, 0, 0, 1 });
	graph.push_back({ 0, 0, 0, 0, 0, }); 

    // buildGraph(graph, 5, 10);
	/* graph[0][3] = 1; 
	graph[1][2] = 1; 
	graph[1][4] = 1; 
	graph[2][0] = 1; 
	graph[2][1] = 1;
	graph[2][4] = 1; 
	graph[3][0] = 1; 
	graph[3][1] = 1; 
	graph[3][4] = 1; 
	*/

	unordered_map<int, int> visited{}; 
	buildDfsTree(graph, 0, 1, visited); 
	unordered_map<int, int>low_values{};
	vector<int> articulation_points{}; 
	getArticulationPoints(
		graph, 
		0, 
		low_values,
		articulation_points
	); 

	return 0; 
}