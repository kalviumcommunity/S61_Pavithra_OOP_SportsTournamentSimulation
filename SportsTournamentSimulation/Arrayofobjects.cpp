#include <iostream>
#include <string>

using namespace std;

// Player class definition
class Player {
private:
    string playerName;

public:
    // Constructor to initialize player name
    Player() {}
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
    Player players[11]; // Assuming a maximum of 11 players per team
    int playerCount;

public:
    // Constructor to initialize team name and players
    Team(string name, Player teamPlayers[], int count) : teamName(name), playerCount(count) {
        for (int i = 0; i < count; ++i) {
            players[i] = teamPlayers[i];
        }
    }

    // Method to display team details
    void displayTeam() const {
        cout << "Team: " << teamName << "\nPlayers: ";
        for (int i = 0; i < playerCount; ++i) {
            cout << players[i].getPlayerName() << " ";
        }
        cout << endl;
    }

    // Method to add a player to the team
    void addPlayer(Player newPlayer) {
        if (playerCount < 11) {
            players[playerCount] = newPlayer;
            playerCount++;
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
        return playerCount;
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
    Match(Team t1, Team t2) : team1(t1), team2(t2), result("Match not played yet.") {}

    // Method to simulate the match and determine the winner
    void playMatch() {
        if (team1.getPlayerCount() > team2.getPlayerCount()) {
            result = team1.getTeamName() + " wins!";
        } else if (team1.getPlayerCount() < team2.getPlayerCount()) {
            result = team2.getTeamName() + " wins!";
        } else {
            result = "It's a draw!";
        }
        cout << "Result: " << result << endl;
    }

    // Method to display the result of the match
    void displayResult() const {
        cout << "Match Result: " << result << endl;
    }
};

// Function to get player names from the user
void getPlayers(Player players[], int numPlayers) {
    for (int i = 0; i < numPlayers; ++i) {
        string playerName;
        cout << "Enter name of player " << (i + 1) << ": ";
        cin >> playerName;
        players[i] = Player(playerName);
    }
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
    Player playersA[11]; // Assuming a maximum of 11 players per team
    getPlayers(playersA, numPlayersA);
    Team teamA(teamAName, playersA, numPlayersA);

    // Get team B details from the user
    string teamBName;
    int numPlayersB;
    cout << "Enter the name of Team B: ";
    cin >> teamBName;
    cout << "Enter the number of players in Team B: ";
    cin >> numPlayersB;
    Player playersB[11];
    getPlayers(playersB, numPlayersB);
    Team teamB(teamBName, playersB, numPlayersB);

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
