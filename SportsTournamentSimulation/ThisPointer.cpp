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

public:
    // Constructor to initialize team name and players
    Team(string name, vector<Player> teamPlayers) : teamName(name), players(teamPlayers) {}

    // Method to display team details
    void displayTeam() const {
        cout << "Team: " << this->teamName << "\nPlayers: ";
        for (const Player& player : this->players) {
            cout << player.getPlayerName() << " ";
        }
        cout << endl;
    }

    // Method to add a player to the team
    void addPlayer(Player newPlayer) {
        this->players.push_back(newPlayer);
        cout << newPlayer.getPlayerName() << " added to " << this->teamName << endl;
    }

    // Method to get the team name
    string getTeamName() const {
        return this->teamName;
    }

    // Method to get the number of players in the team
    int getPlayerCount() const {
        return this->players.size();
    }
};

// Match class definition
class Match {
private:
    Team team1;
    Team team2;
    string result;

public:
    // Constructor to initialize the match with two teams
    Match(Team t1, Team t2) : team1(t1), team2(t2) {
        this->result = "Match not played yet.";
    }

    // Method to simulate the match and determine the winner
    void playMatch() {
        if (this->team1.getPlayerCount() > this->team2.getPlayerCount()) {
            this->result = this->team1.getTeamName() + " wins!";
        } else if (this->team1.getPlayerCount() < this->team2.getPlayerCount()) {
            this->result = this->team2.getTeamName() + " wins!";
        } else {
            this->result = "It's a draw!";
        }
        cout << "Result: " << this->result << endl;
    }

    // Method to display the result of the match
    void displayResult() const {
        cout << "Match Result: " << this->result << endl;
    }
};

// Function to get player names from user
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
    Team teamA(teamAName, playersA);

    // Get team B details from the user
    string teamBName;
    int numPlayersB;
    cout << "Enter the name of Team B: ";
    cin >> teamBName;
    cout << "Enter the number of players in Team B: ";
    cin >> numPlayersB;
    vector<Player> playersB = getPlayers(numPlayersB);
    Team teamB(teamBName, playersB);

    // Display team details
    cout << "\nInitial Teams:\n";
    teamA.displayTeam();
    teamB.displayTeam();

    // Add a player to Team A
    string newPlayerName;
    cout << "\nEnter name of a new player to add to Team A: ";
    cin >> newPlayerName;
    Player newPlayer(newPlayerName);
    teamA.addPlayer(newPlayer);

    // Display updated team details
    cout << "\nUpdated Teams:\n";
    teamA.displayTeam();
    teamB.displayTeam();

    // Create and play a match between the two teams
    cout << "\nPlaying a match between " << teamA.getTeamName() << " and " << teamB.getTeamName() << "...\n";
    Match match1(teamA, teamB);
    match1.playMatch();
    match1.displayResult();

    return 0;
}
