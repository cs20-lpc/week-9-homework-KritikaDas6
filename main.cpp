#include "QueueFactory.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// Safely dequeue if not empty
template <typename Q>
inline void safeDequeue(Q* q, int& servicedCount) {
    if (!q->isEmpty()) {
        q->dequeue();
        ++servicedCount;
    }
}

// Run a simulation with random arrivals and services
template <typename T>
void runSimulation(Queue<T>* line, int steps, int arrivalRange, const string& name) {
    int arrivals = 0, serviced = 0, turnedAway = 0;
    int minLen = 0, maxLen = 0;
    double totalLen = 0.0;

    for (int i = 0; i < steps; ++i) {
        int event = (rand() % arrivalRange) - 1; // -1 means service, 0+ means arrival
        if (event < 0) {
            safeDequeue(line, serviced);
        } else {
            try {
                line->enqueue(i);
                ++arrivals;
            } catch (string&) {
                ++turnedAway;
            }
        }

        int len = line->getLength();
        totalLen += len;
        if (i == 0) minLen = maxLen = len;
        if (len < minLen) minLen = len;
        if (len > maxLen) maxLen = len;
    }

    cout << "\n=== Simulation: " << name << " ===" << endl;
    cout << left << setw(30) << "Total arrivals accepted:" << arrivals << endl;
    cout << left << setw(30) << "Total arrivals turned away:" << turnedAway << endl;
    cout << left << setw(30) << "Total customers served:" << serviced << endl;
    cout << left << setw(30) << "Final line length:" << line->getLength() << endl;
    cout << left << setw(30) << "Shortest line observed:" << minLen << endl;
    cout << left << setw(30) << "Longest line observed:" << maxLen << endl;
    cout << left << setw(30) << "Average line length:" << fixed << setprecision(2) 
         << (totalLen / steps) << endl;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    // Simulation 1: Ticket Counter (ArrayQueue)
    Queue<int>* ticketLine = QueueFactory::GetQueue<int>(10);
    runSimulation(ticketLine, 100, 3, "Ticket Counter (ArrayQueue, cap=10)");
    delete ticketLine;

    // Simulation 2: Bank Line (LinkedQueue)
    Queue<int>* bankLine = QueueFactory::GetQueue<int>();
    runSimulation(bankLine, 100, 4, "Hospital Line (LinkedQueue, unbounded)");
    delete bankLine;

    // Simulation 3: Airport Check-In (ArrayQueue)
    Queue<int>* airportLine = QueueFactory::GetQueue<int>(15);
    runSimulation(airportLine, 120, 5, "Airport Check-In (ArrayQueue, cap=15)");
    delete airportLine;

    cout << "\nAll simulations completed successfully.\n";
    return 0;
}
