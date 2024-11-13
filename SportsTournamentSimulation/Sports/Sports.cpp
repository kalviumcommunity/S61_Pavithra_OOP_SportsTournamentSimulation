#include <iostream>
#include <vector>
#include <string>
#include <memory> // For smart pointers

using namespace std;

// Abstract class for different match events
class MatchEvent {
public:
    virtual void playMatch() = 0; // Pure virtual function for playing a match
    virtual void displayResult() const = 0; // Pure virtual function for displaying match result
};

// Base class for common team properties
class SportsTeam {
private:
    string teamName;

public:
    SportsTeam(string name) : teamName(name) {}

    string getTeamName() const {
        return teamName;
    }
};

// Player class definition
class Player {
private:
    string playerName;

public:
    Player(string name) : playerName(name) {}

    string getPlayerName() const {
        return playerName;
    }

    void setPlayersName(string name) {
        playerName = name;
    }
};

// Team class definition inheriting from SportsTeam
class Team : public SportsTeam {
private:
    vector<Player> players;
    static int teamCount;

public:
    Team(string name, vector<Player> teamPlayers) : SportsTeam(name), players(teamPlayers) {
        teamCount++;
    }

    void displayTeam() const {
        cout << "Team: " << getTeamName() << "\nPlayers: ";
        for (const Player& player : players) {
            cout << player.getPlayerName() << " ";
        }
        cout << endl;
    }

    void addPlayer(Player newPlayer) {
        if (players.size() < 11) {
            players.push_back(newPlayer);
            cout << newPlayer.getPlayerName() << " added to " << getTeamName() << endl;
        } else {
            cout << "Cannot add more players to " << getTeamName() << ". Team is full." << endl;
        }
    }

    int getPlayerCount() const {
        return players.size();
    }

    static int getTeamCount() {
        return teamCount;
    }

    static void resetTeamCount() {
        teamCount = 0;
    }
};

// Initialize static variable for Team
int Team::teamCount = 0;

// New class to handle match results (SRP)
class MatchResult {
private:
    string result;

public:
    void determineResult(Team* team1, Team* team2) {
        if (team1->getPlayerCount() > team2->getPlayerCount()) {
            result = team1->getTeamName() + " wins!";
        } else if (team1->getPlayerCount() < team2->getPlayerCount()) {
            result = team2->getTeamName() + " wins!";
        } else {
            result = "It's a draw!";
        }
    }

    void displayResult() const {
        cout << "Match Result: " << result << endl;
    }
};

// Match class definition inheriting from MatchEvent
class Match : public MatchEvent {
private:
    Team* team1;
    Team* team2;
    MatchResult resultHandler;
    static int matchCount;

public:
    Match(Team* t1, Team* t2) : team1(t1), team2(t2) {
        matchCount++;
    }

    // Override the pure virtual function to play a single match
    void playMatch() override {
        resultHandler.determineResult(team1, team2);
        resultHandler.displayResult();
    }

    // Implement the displayResult method to satisfy the pure virtual function
    void displayResult() const override {
        cout << "Match between " << team1->getTeamName() << " and " << team2->getTeamName() << " has been played." << endl;
    }

    static int getMatchCount() {
        return matchCount;
    }

    static void resetMatchCount() {
        matchCount = 0;
    }

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
    string teamAName;
    int numPlayersA;
    cout << "Enter the name of Team A: ";
    cin >> teamAName;
    cout << "Enter the number of players in Team A: ";
    cin >> numPlayersA;
    vector<Player> playersA = getPlayers(numPlayersA);
    Team* teamA = new Team(teamAName, playersA);

    string teamBName;
    int numPlayersB;
    cout << "Enter the name of Team B: ";
    cin >> teamBName;
    cout << "Enter the number of players in Team B: ";
    cin >> numPlayersB;
    vector<Player> playersB = getPlayers(numPlayersB);
    Team* teamB = new Team(teamBName, playersB);

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

    cout << "\nPlaying a match between " << teamA->getTeamName() << " and " << teamB->getTeamName() << "...\n";
    Match* match1 = new Match(teamA, teamB);
    match1->playMatch();  // Play the match

    cout << "\nTotal number of teams created: " << Team::getTeamCount() << endl;
    cout << "Total number of matches played: " << Match::getMatchCount() << endl;

    Team::resetTeamCount();
    Match::resetMatchCount();
    cout << "\nTeam and Match counts reset." << endl;
    cout << "Total number of teams created: " << Team::getTeamCount() << endl;
    cout << "Total number of matches played: " << Match::getMatchCount() << endl;

    delete match1;

    return 0;
}
