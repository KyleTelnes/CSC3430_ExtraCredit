#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;


// FileData structure holds information about the start,
// finish and value of a request extracted from the file
struct FileData
{
    int startTime;
    int finishTime;
    int weight;
    int nextCompatible;
};

// Comparison function for sorting by finish time
bool CompareFinishTime(FileData data1, FileData data2)
{
    return (data1.finishTime < data2.finishTime);
}

// Outputs the optimal schedule for the user
void OutputSolution(const int j, const int memo[], const vector<FileData> data) {
    if (j == 0) {
        return;
    }
    else if (data[j - 1].weight + memo[j] > memo[j - 1]) {
        cout << j << endl;
        OutputSolution(data[j - 1].nextCompatible, memo, data);
    }
    else {
        OutputSolution(j - 1, memo, data);
    }
}


int main(int argc, char const *argv[])
{
    ifstream readFile("requests.csv");

    // data vector holds all of the extracted data from the file
    vector<FileData> data;

    // Extract information from CSV file
    string line;
    while (getline(readFile, line)) 
    {
        FileData entry;
        
        entry.startTime = stoi(line.substr(0,line.find_first_of(',')));
        entry.finishTime = stoi(line.substr(line.find_first_of(',') + 1, line.find_last_of(',') - 2));
        entry.weight = stoi(line.substr(line.find_last_of(',') + 1, line.back()));
        
        data.push_back(entry);
    }
    // Done reading from the file
    readFile.close();

    // Sort requests by finish time in ascending order
    sort(data.begin(), data.end(), CompareFinishTime);

    // Output the sorted schedule so that it is easier to match the result 
    // to the requests
    for (int i = 0; i < data.size(); i++) {
        cout << "Request #" << i + 1 << " Start: " << data[i].startTime
            << " Finish: " << data[i].finishTime << " Value: " << data[i].weight << endl;
    }  
    // Calculate p(j) for each entry
    for (int j = data.size() - 1; j >= 0; j--) {
        for (int i = j; i >= 0; i--) {
            if (data[i].finishTime <= data[j].startTime) {
                data[j].nextCompatible = i + 1;
                break;
            }
            else {
                data[j].nextCompatible = 0;
            }
        }
    }

    // Initialize memoization array
    int memo[data.size() + 1];
    // First index has 0
    memo[0] = 0;

    // add the value of the solution to the array
    for (int j = 0; j < data.size(); j++) {
        memo[j + 1] = max(data[j].weight + memo[data[j].nextCompatible], memo[j]);
    }

    // Output Solution
    cout << "The Optimal Schedule is: " << endl;
    OutputSolution(data.size(), memo, data);
    cout << "The total weight of the schedule is: " << memo[data.size()] << endl;
    
    return 0;
}
