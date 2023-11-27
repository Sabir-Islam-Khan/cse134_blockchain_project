#include <iostream>
#include <stack>
#include <queue>
#include <thread>
#include <chrono>
#include <string.h>

using namespace std;

#define ANSI_RED "\033[31m"
#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
#define ANSI_BLUE "\033[34m"
#define ANSI_PURPLE "\033[35m"

void displayCentered(const string &text)
{
    int terminalWidth = 100; // Set the terminal width
    int spaces = (terminalWidth - text.size()) / 2;
    for (int i = 0; i < spaces; ++i)
    {
        cout << " ";
    }
    cout << ANSI_BLUE << text << ANSI_RESET << endl;
}

void flashText(const string &projectName, const string &madeBy1, const string &id1, const string &madeBy2, const string &id2)
{
    string boxLine = "\n\n\t\t##########################################################################";

    // Display blue text inside a box
    cout << "\033[1;34m"; // Set text color to blue
    cout << ANSI_PURPLE << boxLine << ANSI_RESET << "\n";
    cout << endl
         << endl;
    displayCentered(projectName);
    displayCentered("Made by");
    displayCentered("Name: " + madeBy1);
    displayCentered("ID: " + id1);
    displayCentered("And");
    displayCentered("Name: " + madeBy2);
    displayCentered("ID: " + id2);

    cout << ANSI_PURPLE << boxLine << ANSI_RESET << "\n";
    cout << "\033[0m"; // Reset text color

    getchar();
    system("clear");
}

struct Block
{
    int index;
    string data;
    string prevHash;
    string hash;
};

struct Vote
{
    int teamNumber;
};

struct Node
{
    Vote vote;
    Node *next;
};

class LinkedList
{
private:
    Node *head;

public:
    LinkedList() : head(nullptr) {}

    void addVote(Vote vote)
    {
        Node *newNode = new Node;
        newNode->vote = vote;
        newNode->next = head;
        head = newNode;
    }

    int countVotes(int teamNumber)
    {
        int count = 0;
        Node *current = head;
        while (current != nullptr)
        {
            if (current->vote.teamNumber == teamNumber)
            {
                count++;
            }
            current = current->next;
        }
        return count;
    }
};

int main()
{

    flashText("Decentralized Voting System", "MD Sabir Islam Khan", "0242310005101420", "Sarifa Siddika", "0242310005101838");
    stack<Block> blockchainStack; // Stack for blockchain
    queue<Block> blockchainQueue; // Queue for blockchain
    LinkedList votes;
    int team1Count = 0, team2Count = 0;
    Block genesisBlock;
    genesisBlock.index = 0;
    genesisBlock.data = "Genesis Block";
    genesisBlock.prevHash = "0";
    genesisBlock.hash = "HASH"; // Simplified hash, actual implementation is more complex
    blockchainStack.push(genesisBlock);
    blockchainQueue.push(genesisBlock);

    cout << ANSI_PURPLE << "\nDecentralized Voting System\n\n"
         << ANSI_RESET;
    cout << ANSI_BLUE << "1. Vote for Team 1\n";
    cout << "2. Vote for Team 2\n";
    cout << "3. Display Total Vote Counts\n";
    cout << "4. Display Result\n";
    cout << "5. View Blockchain (Stack)\n";
    cout << "6. Search Blockchain (Queue)\n"
         << ANSI_RESET;
    cout << ANSI_RED << "7. Exit\n\n"
         << ANSI_RESET;

    while (true)
    {

        cout << ANSI_GREEN << "Enter your choice: " << ANSI_RESET;

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Vote vote;
            vote.teamNumber = 1;
            votes.addVote(vote);
            team1Count++;
            Block block;
            block.index = blockchainStack.top().index + 1;
            block.data = "Vote for Team 1";
            block.prevHash = blockchainStack.top().hash;
            block.hash = to_string(vote.teamNumber) + "__HASH__" + to_string(team1Count); // Simplified hash calculation
            blockchainStack.push(block);
            blockchainQueue.push(block);
            cout << ANSI_PURPLE << "Voted for Team 1\n"
                 << ANSI_RESET;
            break;
        }
        case 2:
        {
            Vote vote;
            vote.teamNumber = 2;
            votes.addVote(vote);
            team2Count++;
            Block block;
            block.index = blockchainStack.top().index + 1;
            block.data = "Vote for Team 2";
            block.prevHash = blockchainStack.top().hash;
            block.hash = to_string(vote.teamNumber) + "__HASH__" + to_string(team2Count); // Simplified hash calculation
            blockchainStack.push(block);
            blockchainQueue.push(block);
            cout << ANSI_PURPLE << "Voted for Team 2\n"
                 << ANSI_RESET;
            break;
        }
        case 3:
        {
            cout << ANSI_PURPLE << "Total Vote Counts:\n"
                 << ANSI_RESET;
            cout << ANSI_BLUE << "Team 1: " << ANSI_RED << team1Count << ANSI_BLUE << " votes\n"
                 << ANSI_RESET;
            cout << ANSI_BLUE << "Team 2: " << ANSI_RED << team2Count << ANSI_BLUE << " votes\n"
                 << ANSI_RESET;
            break;
        }
        case 4:
        {
            cout << ANSI_PURPLE << "Results:\n"
                 << ANSI_RESET;
            cout << ANSI_BLUE << "Team 1: " << ANSI_RED << team1Count << ANSI_BLUE << " votes\n"
                 << ANSI_RESET;
            cout << ANSI_BLUE << "Team 2: " << ANSI_RED << team2Count << ANSI_BLUE << " votes\n"
                 << ANSI_RESET;
            if (team1Count > team2Count)
            {
                cout << ANSI_PURPLE << "Team 1 wins!\n"
                     << ANSI_RESET;
            }
            else if (team2Count > team1Count)
            {
                cout << ANSI_PURPLE << "Team 2 wins!\n"
                     << ANSI_RESET;
            }
            else
            {
                cout << ANSI_RED << "It's a tie!\n"
                     << ANSI_RESET;
            }
            break;
        }
        case 5:
        {
            cout << ANSI_PURPLE << "Blockchain (Stack):\n"
                 << ANSI_RESET;
            stack<Block> tempStack;
            while (!blockchainStack.empty())
            {
                tempStack.push(blockchainStack.top());
                blockchainStack.pop();
            }
            while (!tempStack.empty())
            {
                cout << ANSI_BLUE << "Block " << ANSI_RED << tempStack.top().index << ": " << ANSI_BLUE << tempStack.top().data << ANSI_RESET << endl;
                blockchainStack.push(tempStack.top());
                tempStack.pop();
            }
            break;
        }
        case 6:
        {
            int searchIndex;
            cout << ANSI_GREEN << "Enter the index of the block to search: " << ANSI_RESET;
            cin >> searchIndex;

            queue<Block> tempQueue = blockchainQueue;
            bool found = false;
            while (!tempQueue.empty())
            {
                if (tempQueue.front().index == searchIndex)
                {
                    cout << ANSI_PURPLE << "Block found in Blockchain (Queue):\n";
                    cout << ANSI_BLUE << "Block " << ANSI_RED << tempQueue.front().index << ": " << ANSI_BLUE << tempQueue.front().data << ANSI_RESET << endl;
                    found = true;
                    break;
                }
                tempQueue.pop();
            }

            if (!found)
            {
                cout << ANSI_RED << "Block with index " << searchIndex << " not found in Blockchain (Queue).\n"
                     << ANSI_RESET;
            }
            break;
        }
        case 7:
        {
            cout << ANSI_RED << "\n\nExiting...Thanks for using our program\n";
            return 0;
        }
        default:
            cout << ANSI_RED << "Invalid choice. Please try again.\n"
                 << ANSI_RESET;
        }
    }

    return 0;
}
