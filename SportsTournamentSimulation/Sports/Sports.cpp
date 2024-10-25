#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

// Match class definition inheriting from SportsTeam
class Match : public SportsTeam {
private:
    Team* team1;
    Team* team2;
    string result;
    static int matchCount;

public:
    // Constructor for single match
    Match(Team* t1, Team* t2) : SportsTeam(t1->getTeamName() + " vs " + t2->getTeamName()), team1(t1), team2(t2) {
        result = "Match not played yet.";
        matchCount++;
    }

    // Function to play a single match (overloaded for polymorphism)
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

    // Overloaded function to play multiple rounds
    void playMatch(int rounds) {
        int team1Wins = 0, team2Wins = 0;
        for (int i = 1; i <= rounds; i++) {
            if (team1->getPlayerCount() > team2->getPlayerCount()) {
                team1Wins++;
            } else if (team1->getPlayerCount() < team2->getPlayerCount()) {
                team2Wins++;
            }
            // Tie does not count as a win for either team in each round
        }

        if (team1Wins > team2Wins) {
            result = team1->getTeamName() + " wins the match series!";
        } else if (team1Wins < team2Wins) {
            result = team2->getTeamName() + " wins the match series!";
        } else {
            result = "The match series is a draw!";
        }
        cout << "Result after " << rounds << " rounds: " << result << endl;
    }

    void displayResult() const {
        cout << "Match Result: " << result << endl;
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

    cout << "\nPlaying a single match between " << teamA->getTeamName() << " and " << teamB->getTeamName() << "...\n";
    Match* match1 = new Match(teamA, teamB);
    match1->playMatch();  // Play single match
    match1->displayResult();

    int rounds;
    cout << "\nEnter the number of rounds for a match series: ";
    cin >> rounds;
    cout << "Playing a match series of " << rounds << " rounds...\n";
    match1->playMatch(rounds);  // Play series of matches

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
