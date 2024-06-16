//This code has been adapted from GeeksforGeeks: https://www.geeksforgeeks.org/introduction-to-dijkstras-shortest-path-algorithm/
//I am referencing the fact that I have adapted this code from geeksforgeeks, and have inspired the layout and techniques of Dijkstra throughout this code to aid my algorithm's development, as well as my own custom coding techniques that I have learnt throughout codelab and data structures.

#include <iostream> 
#include <vector> //I have added vectors to better organise my array which consists of the 2D weighted points.
using namespace std; 

#define P 9 //Using define to define the amount of vertex's used throughout the implementation of my code. Sets P = points

class edge { //Class set to edge which includes detailes of how to get to destination
   int points; //setting points as int to output how many points it took to get from source to destination
   char source; //Sets source as a character, so user can enter a letter. This is the same as destination
   char destination; 
};

char retrievePoint (int map) { //Sets A as 0, which follow on to B as 1, C as 2, and so on
    return map + 'A'; //Returns entered value
}

int retrieveList (char point) { 
    return point - 'A';
}

void userInputEdge (int map [P] [P], const vector < pair < pair < string, string >, int >> edge) { //Function which focuses on taking an input from a user, such as A to B.

    for (const auto & edge : edge) { //For loop which goes through all edges from the user input

            char source = edge.first.first[0]; //Gets source (starting point) example A ->
            char destination = edge.first.second[0]; //Gets destination (end point) example B
            int points = edge.second; //Gets total points, for example 10
            map [retrieveList (source)] [retrieveList (destination)] = points; //Adds the edge to graph
    }
}

int distance (int distance [], bool userSource []) { //This function finds the points within the distance value, It is also specified with an current int array, and a boolean array to specify which points have been analysed
    int dist = INT_MAX, map; //Sets the maximum value and list, so it cannot go any further

    for (int j = 0; j < P; j++) //Using a for loop here so it iterates through each edge 
        if (!userSource [j] && distance [j] <= dist) //Using an if statement to update if the point isnt part of the shortest path, and has a smaller distance
            dist = distance [j], map = j; //Updates both distance and index of the list
            return map; //Returns value with the required distance
}

void outputRoute (int parent [], int j) { //This function will output the route provided by the user's source to any given point
    if (parent[j] == -1) //if a point is a source, then it is not a parent point
        return; //returns output
    outputRoute(parent, parent [j]); //Outputs the current route taken from parent 
    cout << " -> " << retrievePoint (j); //Cout here which outputs an arrow for the user to indicate source point to (A ->)
}

void outputResult (int distance [], int parent [], char userSource, char destination) { //This function will output the result of the overall algorithm's performance so far
    cout << "Shortest distance from " << userSource << " to " << destination << ": " << distance [retrieveList (destination) ] << endl; //Outputs the shortast distance via a user input
    cout << "Path taken: " << userSource; //Shows the that was taken. The route will be shown via connected nodes such as A -> B
    outputRoute(parent, retrieveList (destination)); //Calls outputRoute when outputResult has been called. This is to show the path that has been taken to achieve the desired optimal and quickest route

}

void shortestPathDijkstra(int graph[P][P], char sources, char destinations) { //This function mainly focuses on the implementation of the Dijkstra algorithm to achieve the shortest path possible

    int parent [P];
    int distances [P]; //Array to store each distance from source point
    bool source [P]; //Array to store a boolean of the inclusion of points in the shortest path. If true, source point is true and added, if false, source point excluded
     //Array to store overall route taken

    for (int i = 0; i < P; i++) { //Initialises all distances as infinitiy, sets source to false

            distances [i] = INT_MAX; //Sets distances to infinity for all verticles 
            source [i] = false; //Sets all verticles as false
            parent [i] = -1; //Sets to no parent, currently waiting
    }

    distances[retrieveList(sources)] = 0; //Sets distance from source to 0

    for (int add = 0; add < P - 1; add++) { //Counts up points

            int v = distance(distances, source); //Retrieves the points and compares against verticles
            source [v] = true; //Establishes a connection, and marks it as analysed

            for (int p = 0; p < P; p++) { //Updating distance for loop, if current point (v) is connected to (p), and max weight from source to (p) through (v) is currently smaller then the distance required

                if (!source [p] && graph [v][p] != INT_MAX && distances [v] != INT_MAX && distances [v] + graph [v][p] < distances [p]) {
                        distances [p] = distances [v] + graph [v][p]; //Updates distance to point p
                        parent [p] = v; //Updates parent point via p to v
            }
        }
    }

    outputResult(distances, parent, sources, destinations); //Outputs distance and path taken from source to destination
}

int main() {
    int graph [P][P]; //Declares a max for the graph

    for (int i = 0; i < P; i++) //Initialises the graph provided from the path.txt. Sets = 0 for self loop, and INT_MAX for no direct path
        for (int j = 0; j < P; j++)
            graph [i][j] = (i == j) ? 0 : INT_MAX;
    
    vector < pair < pair < string, string >, int >> edges = { //Adds the weights provided from the path.txt file
        {{"A", "B"}, 10}, {{"A", "D"}, 12}, {{"A", "G"}, 11}, {{"A", "H"}, 4}, {{"B", "A"}, 10}, {{"B", "D"}, 8}, {{"B", "H"}, 20},
        {{"C", "D"}, 17}, {{"C", "E"}, 8},  {{"C", "G"}, 13}, {{"C", "H"}, 10}, {{"D", "A"}, 12}, {{"D", "B"}, 8}, {{"D", "C"}, 17}, {{"D", "F"}, 16},
        {{"D", "G"}, 24}, {{"D", "H"}, 14}, {{"E", "C"}, 8}, {{"E", "F"}, 8}, {{"E", "G"}, 11}, {{"E", "H"}, 5},
        {{"F", "D"}, 16}, {{"F", "E"}, 8},  {{"F", "G"}, 18}, {{"F", "H"}, 21},{{"G", "A"}, 11}, {{"G", "C"}, 13}, {{"G", "D"}, 24}, {{"G", "E"}, 11},
        {{"G", "F"}, 18}, {{"G", "H"}, 30}, {{"H", "A"}, 4}, {{"H", "B"}, 20}, {{"H", "C"}, 10}, {{"H", "D"}, 14},
        {{"H", "E"}, 5}, {{"H", "F"}, 21}, {{"H", "G"}, 30}};
     
    userInputEdge (graph, edges); //Edges added from user input registered 
    char source, destination; //Initialising variables needed for functionality

    cout << "Enter a source please: (starting and end points A to I) ";
    cin >> source;

    cout << "Enter destination please: ";
    cin >> destination;
    //Cout and cin combination to allow users to enter their desired source and destination

    shortestPathDijkstra(graph, source, destination); //Finds the most shortest and optimal path

    return 0; 
}
