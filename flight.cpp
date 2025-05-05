#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// Class to represent the graph
class FlightGraph {
public:
    unordered_map<string, vector<pair<string, int>>> adjList;

    // Function to add a flight (edge) between two cities (nodes)
    void addFlight(const string& cityA, const string& cityB, int cost) {
        adjList[cityA].push_back({cityB, cost}); // Adding directed edge A -> B
        adjList[cityB].push_back({cityA, cost}); // Adding directed edge B -> A (if flight is bi-directional)
    }

    // Function to display the graph
    void displayGraph() {
        for (auto& city : adjList) {
            cout << "Flights from " << city.first << ":\n";
            for (auto& flight : city.second) {
                cout << "  to " << flight.first << " with cost " << flight.second << " units\n";
            }
            cout << endl;
        }
    }

    // Function to find if there is a direct flight between two cities
    bool hasDirectFlight(const string& cityA, const string& cityB) {
        for (auto& flight : adjList[cityA]) {
            if (flight.first == cityB) {
                return true;
            }
        }
        return false;
    }

    // Function to find the cost of a direct flight between two cities
    int getFlightCost(const string& cityA, const string& cityB) {
        for (auto& flight : adjList[cityA]) {
            if (flight.first == cityB) {
                return flight.second;
            }
        }
        return -1; // Return -1 if there is no direct flight
    }
};

int main() {
    FlightGraph graph;

    // Add some flights between cities with cost (time or fuel)
    graph.addFlight("New York", "Los Angeles", 5);   // 5 hours or 5 units of fuel
    graph.addFlight("Los Angeles", "Chicago", 3);
    graph.addFlight("Chicago", "New York", 4);
    graph.addFlight("New York", "Miami", 2);
    
    // Display the graph
    graph.displayGraph();

    // Check if there is a direct flight between New York and Miami
    if (graph.hasDirectFlight("New York", "Miami")) {
        cout << "There is a direct flight from New York to Miami.\n";
    }

    // Get the cost of the flight between New York and Los Angeles
    int cost = graph.getFlightCost("New York", "Los Angeles");
    if (cost != -1) {
        cout << "The cost of the flight from New York to Los Angeles is " << cost << " units.\n";
    } else {
        cout << "There is no direct flight from New York to Los Angeles.\n";
    }

    return 0;
}
