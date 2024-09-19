#include <iostream>
#include <vector>
#include <string>

// Player class definition
class Player {
private:
    std::string playerName;

public:
    // Constructor to initialize player name
    Player(std::string name) : playerName(name) {}

    // Method to get the player's name
    std::string getPlayerName() const {
        return playerName;
    }
};

// Team class definition
class Team {
private:
    std::string teamName;
    std::vector<Player> players;

    // Static variable to count the number of teams
    static int teamCount;

public:
    // Constructor to initialize team name and players
    Team(std::string name, std::vector<Player> teamPlayers) : teamName(name), players(teamPlayers) {
        teamCount++; // Increment team count when a new team is created
    }

    // Method to display team details
    void displayTeam() const {
        std::cout << "Team: " << teamName << "\nPlayers: ";
        for (const Player& player : players) {
            std::cout << player.getPlayerName() << " ";
        }
        std::cout << std::endl;
    }

    // Method to add a player to the team
    void addPlayer(Player newPlayer) {
        players.push_back(newPlayer);
        std::cout << newPlayer.getPlayerName() << " added to " << teamName << std::endl;
    }

    // Method to get the team name
    std::string getTeamName() const {
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

    // Static member function to reset the team count
    static void resetTeamCount() {
        teamCount = 0;
    }
};

// Initialize static variable
int Team::teamCount = 0;

// Match class definition
class Match {
private:
    Team team1;
    Team team2;
    std::string result;

    // Static variable to count the number of matches played
    static int matchCount;

public:
    // Constructor to initialize the match with two teams
    Match(Team t1, Team t2) : team1(t1), team2(t2) {
        result = "Match not played yet.";
        matchCount++; // Increment match count when a new match is created
    }

    // Method to simulate the match and determine the winner
    void playMatch() {
        if (team1.getPlayerCount() > team2.getPlayerCount()) {
            result = team1.getTeamName() + " wins!";
        } else if (team1.getPlayerCount() < team2.getPlayerCount()) {
            result = team2.getTeamName() + " wins!";
        } else {
            result = "It's a draw!";
        }
        std::cout << "Result: " << result << std::endl;
    }

    // Method to display the result of the match
    void displayResult() const {
        std::cout << "Match Result: " << result << std::endl;
    }

    // Static method to get the total number of matches played
    static int getMatchCount() {
        return matchCount;
    }

    // Static member function to reset the match count
    static void resetMatchCount() {
        matchCount = 0;
    }
};

// Initialize static variable
int Match::matchCount = 0;

// Function to get player names from user
std::vector<Player> getPlayers(int numPlayers) {
    std::vector<Player> players;
    for (int i = 0; i < numPlayers; ++i) {
        std::string playerName;
        std::cout << "Enter name of player " << (i + 1) << ": ";
        std::cin >> playerName;
        players.push_back(Player(playerName));
    }
    return players;
}

// Main function
int main() {
    // Get team A details from the user
    std::string teamAName;
    int numPlayersA;
    std::cout << "Enter the name of Team A: ";
    std::cin >> teamAName;
    std::cout << "Enter the number of players in Team A: ";
    std::cin >> numPlayersA;
    std::vector<Player> playersA = getPlayers(numPlayersA);
    Team teamA(teamAName, playersA);

    // Get team B details from the user
    std::string teamBName;
    int numPlayersB;
    std::cout << "Enter the name of Team B: ";
    std::cin >> teamBName;
    std::cout << "Enter the number of players in Team B: ";
    std::cin >> numPlayersB;
    std::vector<Player> playersB = getPlayers(numPlayersB);
    Team teamB(teamBName, playersB);

    // Display team details
    std::cout << "\nInitial Teams:\n";
    teamA.displayTeam();
    teamB.displayTeam();

    // Add a player to Team A
    std::string newPlayerName;
    std::cout << "\nEnter name of a new player to add to Team A: ";
    std::cin >> newPlayerName;
    Player newPlayer(newPlayerName);
    teamA.addPlayer(newPlayer);

    // Display updated team details
    std::cout << "\nUpdated Teams:\n";
    teamA.displayTeam();
    teamB.displayTeam();

    // Create and play a match between the two teams
    std::cout << "\nPlaying a match between " << teamA.getTeamName() << " and " << teamB.getTeamName() << "...\n";
    Match match1(teamA, teamB);
    match1.playMatch();
    match1.displayResult();

    // Display the total number of teams and matches
    std::cout << "\nTotal number of teams created: " << Team::getTeamCount() << std::endl;
    std::cout << "Total number of matches played: " << Match::getMatchCount() << std::endl;

    // Resetting team and match counts
    Team::resetTeamCount();
    Match::resetMatchCount();
    std::cout << "\nTeam and Match counts reset." << std::endl;
    std::cout << "Total number of teams created: " << Team::getTeamCount() << std::endl;
    std::cout << "Total number of matches played: " << Match::getMatchCount() << std::endl;

    return 0;
}

