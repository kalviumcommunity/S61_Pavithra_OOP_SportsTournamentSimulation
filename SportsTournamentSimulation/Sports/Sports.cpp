#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Player class definition
class Player {
private:
    string playerName;

public:
    // Constructor to initialize player name
    Player(string name) : playerName(name) {}

    // Method to get the player's name
    string getPlayerName() const {
        return playerName;
    }
};

// Team class definition
class Team {
private:
    string teamName;
    vector<Player> players;

    // Static variable to count the number of teams
    static int teamCount;

public:
    // Constructor to initialize team name and players
    Team(string name, vector<Player> teamPlayers) : teamName(name), players(teamPlayers) {
        teamCount++; // Increment team count when a new team is created
    }

    // Method to display team details
    void displayTeam() const {
        cout << "Team: " << teamName << "\nPlayers: ";
        for (const Player& player : players) {
            cout << player.getPlayerName() << " ";
        }
        cout << endl;
    }

    // Method to add a player to the team
    void addPlayer(Player newPlayer) {
        if (players.size() < 11) {  // Assuming a maximum of 11 players per team
            players.push_back(newPlayer);
            cout << newPlayer.getPlayerName() << " added to " << teamName << endl;
        } else {
            cout << "Cannot add more players to " << teamName << ". Team is full." << endl;
        }
    }

    // Method to get the team name
    string getTeamName() const {
        return teamName;
    }

    // Method to get the number of players in the team
    int getPlayerCount() const {
        return players.size();
    }

    // Static method to get the total number of teams created
    static int getTeamCount() {
        return teamCount;
    }

    // Static method to reset the team count
    static void resetTeamCount() {
        teamCount = 0;
    }
};

// Initialize static variable for Team
int Team::teamCount = 0;

// Match class definition
class Match {
private:
    Team* team1;
    Team* team2;
    string result;

    // Static variable to count the number of matches played
    static int matchCount;

public:
    // Constructor to initialize the match with two teams
    Match(Team* t1, Team* t2) : team1(t1), team2(t2) {
        result = "Match not played yet.";
        matchCount++; // Increment match count when a new match is created
    }

    // Method to simulate the match and determine the winner
    void playMatch() {
        if (team1->getPlayerCount() > team2->getPlayerCount()) {
            result = team1->getTeamName() + " wins!";
        } else if (team1->getPlayerCount() < team2->getPlayerCount()) {
            result = team2->getTeamName() + " wins!";
        } else {
            result = "It's a draw!";
        }
        cout << "Result: " << result << endl;
    }

    // Method to display the result of the match
    void displayResult() const {
        cout << "Match Result: " << result << endl;
    }

    // Static method to get the total number of matches played
    static int getMatchCount() {
        return matchCount;
    }

    // Static method to reset the match count
    static void resetMatchCount() {
        matchCount = 0;
    }

    // Destructor to clean up dynamically allocated memory
    ~Match() {
        delete team1;
        delete team2;
    }
};

// Initialize static variable for Match
int Match::matchCount = 0;

// Function to get player names from the user
vector<Player> getPlayers(int numPlayers) {
    vector<Player> players;
    for (int i = 0; i < numPlayers; ++i) {
        string playerName;
        cout << "Enter name of player " << (i + 1) << ": ";
        cin >> playerName;
        players.push_back(Player(playerName));
    }
    return players;
}

// Main function
int main() {
    // Get team A details from the user
    string teamAName;
    int numPlayersA;
    cout << "Enter the name of Team A: ";
    cin >> teamAName;
    cout << "Enter the number of players in Team A: ";
    cin >> numPlayersA;
    vector<Player> playersA = getPlayers(numPlayersA);
    Team* teamA = new Team(teamAName, playersA);

    // Get team B details from the user
    string teamBName;
    int numPlayersB;
    cout << "Enter the name of Team B: ";
    cin >> teamBName;
    cout << "Enter the number of players in Team B: ";
    cin >> numPlayersB;
    vector<Player> playersB = getPlayers(numPlayersB);
    Team* teamB = new Team(teamBName, playersB);

    // Display team details
    cout << "\nInitial Teams:\n";
    teamA->displayTeam();
    teamB->displayTeam();

    // Add a player to Team A
    string newPlayerName;
    cout << "\nEnter name of a new player to add to Team A: ";
    cin >> newPlayerName;
    Player newPlayer(newPlayerName);
    teamA->addPlayer(newPlayer);

    // Display updated team details
    cout << "\nUpdated Teams:\n";
    teamA->displayTeam();
    teamB->displayTeam();

    // Create and play a match between the two teams
    cout << "\nPlaying a match between " << teamA->getTeamName() << " and " << teamB->getTeamName() << "...\n";
    Match* match1 = new Match(teamA, teamB);
    match1->playMatch();
    match1->displayResult();

    // Display the total number of teams and matches
    cout << "\nTotal number of teams created: " << Team::getTeamCount() << endl;
    cout << "Total number of matches played: " << Match::getMatchCount() << endl;

    // Resetting team and match counts
    Team::resetTeamCount();
    Match::resetMatchCount();
    cout << "\nTeam and Match counts reset." << endl;
    cout << "Total number of teams created: " << Team::getTeamCount() << endl;
    cout << "Total number of matches played: " << Match::getMatchCount() << endl;

    // Clean up dynamically allocated memory
    delete match1;

    return 0;
}
