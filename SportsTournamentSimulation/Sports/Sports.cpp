#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Player class definition
class Player
{
private:
    string playerName; // Private member variable

public:
    // Default constructor
    Player()
    {
        playerName = "Unknown"; // Default player name
        cout << "Player Default Constructor called.\n";
    }

    // Parameterized constructor to initialize player name
    Player(string name) : playerName(name)
    {
        cout << "Player Parameterized Constructor called for " << playerName << ".\n";
    }

    // Destructor
    ~Player()
    {
        cout << "Player Destructor called for " << playerName << ".\n";
    }

    // Method to get the player's name (Accessor)
    string getPlayerName() const
    {
        return playerName;
    }

    // Method to set the player's name (Mutator)
    void setPlayersName(string name)
    {
        playerName = name;
    }
};

// Team class definition
class Team
{
private:
    string teamName;        // Private member variable
    vector<Player> players; // Private member variable

    static int teamCount; // Static variable to count the number of teams

public:
    // Default constructor
    Team()
    {
        teamName = "Unknown Team";
        teamCount++;
        cout << "Team Default Constructor called.\n";
    }

    // Parameterized constructor to initialize team name and players
    Team(string name, vector<Player> teamPlayers) : teamName(name), players(teamPlayers)
    {
        teamCount++;
        cout << "Team Parameterized Constructor called for " << teamName << ".\n";
    }

    // Destructor
    ~Team()
    {
        cout << "Team Destructor called for " << teamName << ".\n";
        teamCount--; // Decrease team count when a team is destroyed
    }

    // Method to display team details
    void displayTeam() const
    {
        cout << "Team: " << teamName << "\nPlayers: ";
        for (const Player &player : players)
        {
            cout << player.getPlayerName() << " ";
        }
        cout << endl;
    }

    // Method to add a player to the team
    void addPlayer(Player newPlayer)
    {
        if (players.size() < 11)
        { // Assuming a maximum of 11 players per team
            players.push_back(newPlayer);
            cout << newPlayer.getPlayerName() << " added to " << teamName << endl;
        }
        else
        {
            cout << "Cannot add more players to " << teamName << ". Team is full." << endl;
        }
    }

    // Static method to get the total number of teams created
    static int getTeamCount()
    {
        return teamCount;
    }
};

int Team::teamCount = 0; // Initialize static team count

// Match class definition
class Match
{
private:
    Team *team1;   // Private member variable
    Team *team2;   // Private member variable
    string result; // Private member variable

    static int matchCount; // Static variable to count the number of matches played

public:
    // Default constructor
    Match()
    {
        team1 = nullptr;
        team2 = nullptr;
        result = "Match not played yet.";
        matchCount++;
        cout << "Match Default Constructor called.\n";
    }

    // Parameterized constructor to initialize the match with two teams
    Match(Team *t1, Team *t2) : team1(t1), team2(t2)
    {
        result = "Match not played yet.";
        matchCount++;
        cout << "Match Parameterized Constructor called.\n";
    }

    // Destructor
    ~Match()
    {
        cout << "Match Destructor called.\n";
        matchCount--; // Decrease match count when a match is destroyed
    }

    // Method to simulate the match and determine the winner
    void playMatch()
    {
        // Logic to decide the result of the match (e.g., based on number of players)
        result = "Match played. Result: Draw.";
        cout << result << endl;
    }

    // Static method to get the total number of matches played
    static int getMatchCount()
    {
        return matchCount;
    }
};

int Match::matchCount = 0; // Initialize static match count

// Function to get player names from the user
vector<Player> getPlayers(int numPlayers)
{
    vector<Player> players;
    for (int i = 0; i < numPlayers; ++i)
    {
        string playerName;
        cout << "Enter name of player " << (i + 1) << ": ";
        cin >> playerName;
        players.push_back(Player(playerName)); // Using the parameterized constructor
    }
    return players;
}

int main()
{
    // Get team A details from the user
    string teamAName;
    int numPlayersA;
    cout << "Enter the name of Team A: ";
    cin >> teamAName;
    cout << "Enter the number of players in Team A: ";
    cin >> numPlayersA;
    vector<Player> playersA = getPlayers(numPlayersA);
    Team *teamA = new Team(teamAName, playersA); // Using the parameterized constructor

    // Get team B details from the user
    string teamBName;
    int numPlayersB;
    cout << "Enter the name of Team B: ";
    cin >> teamBName;
    cout << "Enter the number of players in Team B: ";
    cin >> numPlayersB;
    vector<Player> playersB = getPlayers(numPlayersB);
    Team *teamB = new Team(teamBName, playersB); // Using the parameterized constructor

    // Create a match between Team A and Team B
    Match *match1 = new Match(teamA, teamB); // Using the parameterized constructor

    // Play the match
    match1->playMatch();

    // Clean up (delete the dynamically allocated objects)
    delete teamA;
    delete teamB;
    delete match1;

    return 0;
}
