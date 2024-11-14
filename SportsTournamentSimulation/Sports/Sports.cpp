#include <iostream>
#include <vector>
#include <string>

using namespace std;

// **SRP**: Abstract class for different match events
class MatchEvent {
public:
    virtual void playMatch() = 0; // Pure virtual function to play a match
    virtual void displayResult() const = 0; // Pure virtual function to display match result
    virtual ~MatchEvent() {};
};

// **OCP**: By using inheritance, we allow easy extension of match types
class KnockoutMatch : public MatchEvent {
private:
    string result;
public:
    void playMatch() override {
        result = "Knockout match played.";
    }
    void displayResult() const override {
        cout << result << endl;
    }
};

class RoundRobinMatch : public MatchEvent {
private:
    string result;
public:
    void playMatch() override {
        result = "Round Robin match played.";
    }
    void displayResult() const override {
        cout << result << endl;
    }
};

// **SRP**: SportsTeam class handles team-specific functionality
class SportsTeam {
protected:
    string teamName;
public:
    SportsTeam(string name) : teamName(name) {}
    virtual void displayTeam() const = 0;
    string getTeamName() const {
        return teamName;
    }
};

// **SRP**: Player class handles player-specific functionality
class Player {
private:
    string playerName;
public:
    Player(string name) : playerName(name) {}
    string getPlayerName() const {
        return playerName;
    }
};

// **OCP**: Team class allows easy addition of different types of teams
class Team : public SportsTeam {
private:
    vector<Player> players;
    static int teamCount;
public:
    Team(string name, vector<Player> teamPlayers) : SportsTeam(name), players(teamPlayers) {
        teamCount++;
    }

    void displayTeam() const override {
        cout << "Team: " << getTeamName() << "\nPlayers: ";
        for (const Player& player : players) {
            cout << player.getPlayerName() << " ";
        }
        cout << endl;
    }

    void addPlayer(const Player& newPlayer) {
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

int Team::teamCount = 0;

// **SRP**: MatchResult class handles the result of the match
class MatchResult {
private:
    string result;
public:
    void determineResult(const Team& team1, const Team& team2) {
        if (team1.getPlayerCount() > team2.getPlayerCount()) {
            result = team1.getTeamName() + " wins!";
        } else if (team1.getPlayerCount() < team2.getPlayerCount()) {
            result = team2.getTeamName() + " wins!";
        } else {
            result = "It's a draw!";
        }
    }
    void displayResult() const {
        cout << "Match Result: " << result << endl;
    }
};

// **SRP**: Match class handles match-specific functionality
class Match {
private:
    Team* team1;
    Team* team2;
    MatchResult resultHandler;
    MatchEvent* matchEvent;
    static int matchCount; // Static variable to count the number of matches played 

public:
    Match(Team* t1, Team* t2, MatchEvent* event)
        : team1(t1), team2(t2), matchEvent(event) {
            matchCount++;
        }

    ~Match() {
        delete team1;
        delete team2;
        delete matchEvent;
    }

    void playMatch() {
        resultHandler.determineResult(*team1, *team2);
        resultHandler.displayResult();
        matchEvent->playMatch();
        matchEvent->displayResult();
    }

    // Static function to get the match count
    static int getMatchCount() {
        return matchCount;
    }

    // Static function to reset the match count
    static void resetMatchCount() {
        matchCount = 0;
    }
};

int Match::matchCount = 0;

// Function to get player names from the user
vector<Player> getPlayers(int numPlayers) {
    vector<Player> players;
    for (int i = 0; i < numPlayers; ++i) {
        string playerName;
        cout << "Enter name of player " << (i + 1) << ": ";
        cin >> playerName;
        players.emplace_back(playerName);
    }
    return players;
}

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

    string newPlayerName;
    cout << "\nEnter name of a new player to add to Team A: ";
    cin >> newPlayerName;
    Player newPlayer(newPlayerName);
    teamA->addPlayer(newPlayer);

    cout << "\nUpdated Teams:\n";
    teamA->displayTeam();
    teamB->displayTeam();

    MatchEvent* knockoutMatch = new KnockoutMatch();
    MatchEvent* roundRobinMatch = new RoundRobinMatch();

    cout << "\nPlaying a Knockout match between " << teamA->getTeamName() << " and " << teamB->getTeamName() << "...\n";
    Match match1(teamA, teamB, knockoutMatch);
    match1.playMatch();

    cout << "\nPlaying a Round Robin match between " << teamA->getTeamName() << " and " << teamB->getTeamName() << "...\n";
    Match* match2 = new Match(teamA, teamB, roundRobinMatch);
    match2->playMatch();  // Play the round robin match

    cout << "\nTotal number of teams created: " << Team::getTeamCount() << endl;

    cout << "\nTotal number of matches played: " << Match::getMatchCount() << endl;

    // Restet the team count and Match count and display it
    Team::resetTeamCount();
    Match::resetMatchCount();
    cout << "Team count reset. Total number of teams created: " << Team::getTeamCount() << endl;
    cout << "Match count reset. Total number of matches played: " << Match::getMatchCount() << endl;
    return 0;
}
