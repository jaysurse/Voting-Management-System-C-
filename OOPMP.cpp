#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

#define MAX_CANDIDATES 10 // Maximum number of candidates
#define MAX_VOTERS 100    // Maximum number of voters

class Candidate
{
public:
    string name; // Name of the candidate
    int votes;   // Number of votes the candidate has received

    // Constructor to initialize votes to 0
    Candidate()
    {
        votes = 0;
    }

    // Set the name of the candidate
    void setName(string candidateName)
    {
        name = candidateName;
    }

    // Increment the vote count by 1 when a vote is cast
    void addVote()
    {
        votes++;
    }
};

// Voter class to represent a voter in the election
class Voter
{
public:
    string voterID; // Unique ID of the voter
    bool hasVoted;  // Flag to check if the voter has already voted

    // Constructor to initialize voting status to false
    Voter()
    {
        hasVoted = false;
    }

    // Set the voter ID
    void setID(string id)
    {
        voterID = id;
    }
};

// VotingSystem class to manage the entire voting process
class VotingSystem
{
private:
    Candidate candidates[MAX_CANDIDATES]; // Array of candidates
    Voter voters[MAX_VOTERS];             // Array of voters
    int candidateCount;                   // Total number of candidates
    int voterCount;                       // Total number of registered voters

public:
    // Constructor to initialize candidateCount and voterCount to 0
    VotingSystem()
    {
        candidateCount = 0;
        voterCount = 0;
    }

    // Function to add a new candidate
    void addCandidate(string name)
    {
        if (candidateCount < MAX_CANDIDATES)
        {                                             // Check if candidate limit is not reached
            candidates[candidateCount].setName(name); // Set the candidate name
            candidateCount++;                         // Increment the candidate count
            cout << "Candidate " << name << " added successfully.\n";
        }
        else
        {
            cout << "Maximum number of candidates reached.\n";
        }
    }

    // Function to register a new voter
    void addVoter(string voterID)
    {
        if (voterCount < MAX_VOTERS)
        {                                      // Check if voter limit is not reached
            voters[voterCount].setID(voterID); // Set the voter ID
            voterCount++;                      // Increment the voter count
            cout << "Voter with ID " << voterID << " registered successfully.\n";
        }
        else
        {
            cout << "Maximum number of voters reached.\n";
        }
    }

    // Function to cast a vote by a voter
    void castVote(string voterID)
    {
        bool voterFound = false; // Flag to track if voter ID is found

        // Search for the voter in the list of registered voters
        for (int i = 0; i < voterCount; i++)
        {
            if (voters[i].voterID == voterID)
            {
                voterFound = true;
                if (!voters[i].hasVoted)
                {
                    int candidateChoice;
                    cout << "List of Candidates:\n";

                    // Display the list of candidates
                    for (int j = 0; j < candidateCount; j++)
                    {
                        cout << j + 1 << ". " << candidates[j].name << "\n";
                    }

                    // Ask voter to select a candidate
                    cout << "Enter the number corresponding to the candidate you want to vote for: ";
                    cin >> candidateChoice;

                    // Validate the choice and cast the vote
                    if (candidateChoice > 0 && candidateChoice <= candidateCount)
                    {
                        candidates[candidateChoice - 1].addVote(); 
                        voters[i].hasVoted = true;                
                        cout << "Vote cast successfully!\n";
                    }
                    else
                    {
                        cout << "Invalid choice. No vote cast.\n";
                    }
                }
                else
                {
                   
                    cout << "Voter has already voted.\n";
                }
                return; 
            }
        }

        
        if (!voterFound)
        {
            cout << "Voter ID not found.\n";
        }
    }

    // Function to display the voting results
    void displayResults()
    {
        cout << "\nVoting Results:\n";
        cout << left << setw(20) << "Candidate Name" << right << setw(10) << "Votes" << "\n"; // Table headers

        
        for (int i = 0; i < candidateCount; i++)
        {
            cout << left <<  setw(20) << candidates[i].name   
                 << right << setw(10) << candidates[i].votes 
                 << "\n";
        }
    }

    // Function to display the winner of the election
    void displayWinner()
    {
        int maxVotes = -1;
        string winner;    

        // Find the candidate with the highest votes
        for (int i = 0; i < candidateCount; i++)
        {
            if (candidates[i].votes > maxVotes)
            {
                maxVotes = candidates[i].votes;
                winner = candidates[i].name;
            }
        }

        // Display the winner if there were any votes cast
        if (maxVotes != 0)
        {
            cout << "\nThe winner is: " << winner << " with " << maxVotes << " votes!\n";
        }
        else
        {
            cout << "No votes have been cast.\n";
        }
    }
};

// Main function to manage the voting system
int main()
{
    VotingSystem system; 
    int choice;
    string name, voterID;

    do
    {
        // Display the menu
        cout << "\nVoting Management System\n";
        cout << "1. Register a candidate\n";
        cout << "2. Register a voter\n";
        cout << "3. Cast a vote\n";
        cout << "4. Display results\n";
        cout << "5. Display winner\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            // Add a candidate
            cout << "Enter candidate name: ";
            cin >> name;
            system.addCandidate(name);
            break;

        case 2:
            // Register a voter
            cout << "Enter voter ID: ";
            cin >> voterID;
            system.addVoter(voterID);
            break;

        case 3:
            // Cast a vote
            cout << "Enter voter ID to cast vote: ";
            cin >> voterID;
            system.castVote(voterID);
            break;

        case 4:
            // Display voting results
            system.displayResults();
            break;

        case 5:
            // Display the winner
            system.displayWinner();
            break;

        case 6:
            // Exit the program
            cout << "Exiting...\n";
            break;

        default:
            // Handle invalid choice
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6); // Repeat the menu until user selects "Exit"

    return 0;
}
