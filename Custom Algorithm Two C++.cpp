//I am referencing the fact that I have adapted this code from https://www.scaler.com/topics/best-first-search/ 
// and have used it to create a Greedy first best search algorithm.
// I have taken the logic and structure, and applied it to the problem via the path.txt file with the 2D edges. 
// I have combined my knowledge learnt in codelab 1 and 2, and data structures to achieve the desired functionality of this code.

#include <iostream>
#include <vector> //Vector used so I can store my edges in a graph via my array
#include <climits> //climits library added for INT MAX functionality 
#include <unordered_map> //Unordered maps used for parent tracking throughout the code
#include <queue> //Queue used for my priority queue function

using namespace std;
#define P 9 //Using define to define the amount of vertex's used throughout the implementation of my code. Sets P = points

int retrievePoint (char point) { //This function invovles taking a character, and converts the character to a point in the list 
    return point - 'A';
}

// This function to convert the list to the related character, for example; start at 0, 0 = A, 1 = B, and so on 
char retrieveList (int list) {
    return list + 'A';
}


void userInputEdge (int graph[P][P], const vector < pair < pair < string, string >, int >> & edge) { // Function to add edges to the graph from a list of edges, this is done for functionality for a user input

    for (const auto & edge : edge) {  //Using a for loop to go through the list, essentialty iterating through each edge in the list of data given
        int start = retrievePoint(edge.first.first[0]); //Retrieves the starting position from the list via the entered point
        int end = retrievePoint(edge.first.second[0]); //Retrieves the end position from the list via the entered point
        graph[start][end] = edge.second; //Acknowledges the weight of each beginning and end point
    }
}


int heuristicCalculation (char current, char goal) { //This function uses a simple approach to an heuristic, which will estimate a distance from each node to the destination
    return abs (retrievePoint(current) - retrievePoint(goal)); //Calculates the value for the distance, abs used for an absolute value
}

struct Node { //Using a stucture here to give details to the node, for example the point and heuristic value
    char point; //Using a character to represent a point
    int hueristicVal; //Keeps track of the calculated valued cost for the heuristic

    Node(char p, int h) : point(p), hueristicVal(h) {} //Taking both p = point, and h = huerstic, to initialise the node setup
    bool operator> (const Node & other) const {return hueristicVal > other.hueristicVal;} //Comparison regarding the priority queue
};

// Function to output the path from the source to the destination
void outputRoute(unordered_map < char, char > & parent, char v) { //This function ultimately finds the path from the user entered source

    if (parent.find (v) == parent.end()) return; //This line checks to see if the parent actually has a path. This is mainly for quaility control
    outputRoute (parent, parent [v]); //Keeps on printing path from each parent
    cout << " -> " << v; //Outputs the node 
}


void routeDiscover (int graph [P][P], char source, char destination) {// Function that finds the route from start to finish

    priority_queue < Node, vector < Node >, greater < Node >> priority; //This stores each node that is reviewed by the priority queue 
    unordered_map  < char, char > parent; // This will store each node of the parent
    vector         < int > distance (P, INT_MAX); //Using a vector which stores a distance from the 

    priority.emplace(source, heuristicCalculation(source, destination)); //Using a combination of source and destination, via emplace to add the source node into the priority queue
    distance[retrievePoint(source)] = 0; //Distance to the source is registed as 0

    while (!priority.empty()) { //Using a while loop to keep checking until the priority queue is finally empty

        Node current = priority.top(); //Retrieve the node with the lowest valued cost
        priority.pop(); // Takes away node from the priority queue
        int u = retrievePoint(current.point); //Retrieves the data of the current node selected

        if (current.point == destination) { //If statement used to decided if the point has reached its destination

            cout << "Distance from " << source << " to " << destination << ": " << distance[u] << endl; //if so, it will output the distance
            cout << "Path taken: " << source;

            outputRoute(parent, destination); //Takes into consideration the function developed earlier, which outputs the route taken to get from source point to end point
            return; //Return used to exit this function
        }

        for (int v = 0; v < P; ++v) { //For loop used to loop through all nodes

            if (graph[u][v] != INT_MAX) { //If statement used to tell the algorithm if there is an edge to the chosen node
                    int newCost = distance[u] + graph[u][v]; //Calculates the updated valued cost 

                    if (newCost < distance[v]) { //If statement used, to explain, if the updated cost is lower than current cost 
                        distance[v] = newCost; //Then update valued cost
                        parent[retrieveList(v)] = current.point; //Brings in the parent of the node chosen
                        priority.emplace(retrieveList(v), heuristicCalculation(retrieveList(v), destination)); //Puts the node into the priority queue
                }
            }
        }
    }

    cout << "No path found from " << source << " to " << destination << endl; //Quaility control used, to suggest to the user that a path was not found
}

int main() {
    
    int graph[P][P]; //Sets a 2D array

        for (int i = 0; i < P; ++i) //Using a for loop to loop through each row 

        for (int j = 0; j < P; ++j) //Using a for loop which loops through each column

        graph[i][j] = (i == j) ? 0 : INT_MAX; //Sets this to infinitiy for the distance

    
    vector<pair<pair<string, string>, int>> edges = { //Using an array to store the path.txt data, utilising both vector and strings
        {{"A", "B"}, 10}, {{"A", "D"}, 12}, {{"A", "G"}, 11}, {{"A", "H"}, 4},{{"B", "A"}, 10}, {{"B", "D"}, 8}, {{"B", "H"}, 20},
        {{"C", "D"}, 17}, {{"C", "E"}, 8}, {{"C", "G"}, 13}, {{"C", "H"}, 10},{{"D", "A"}, 12}, {{"D", "B"}, 8}, {{"D", "C"}, 17}, {{"D", "F"}, 16},
        {{"D", "G"}, 24}, {{"D", "H"}, 14}, {{"E", "C"}, 8}, {{"E", "F"}, 8}, {{"E", "G"}, 11}, {{"E", "H"}, 5}, {{"F", "D"}, 16}, {{"F", "E"}, 8},
        {{"F", "G"}, 18}, {{"F", "H"}, 21}, {{"G", "A"}, 11}, {{"G", "C"}, 13},{{"G", "D"}, 24}, {{"G", "E"}, 11}, {{"G", "F"}, 18}, {{"G", "H"}, 30},
        {{"H", "A"}, 4}, {{"H", "B"}, 20}, {{"H", "C"}, 10}, {{"H", "D"}, 14},{{"H", "E"}, 5}, {{"H", "F"}, 21}, {{"H", "G"}, 30} 
    };

    userInputEdge(graph, edges); //Adds the edges from the user input via the list

    char source, destination; //Source and destination used for cin, for example, user enters A, this is stored. User then enters destination, which is reviewed by priority queue
    cout << "Enter a source please: (starting and end points A to I) ";//User friendly message which explains to the user how to work the algorithm, and outputs the information.
    cin >> source;

    cout << "Enter destination please: ";
    cin >> destination; //Outputs end point

    routeDiscover(graph, source, destination); //Called after message to give the user the route 

    return 0;
}
