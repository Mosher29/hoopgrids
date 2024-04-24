#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

vector<int> categories;
vector<string> selectedTeams;

// stats to be used later
struct PlayerData {
    string player;
    int Rk, From, To, Yrs, G, MP, FG, FGA, ThreeP, ThreePA, FT, FA, FTA, ORB, TRB, AST, STL, BLK, TOV, PF, PTS;
    double FGP, ThreePP, FTP, MPG, PTSPG, TRBPG, ASTPG, STLPG, BLKPG;
};

vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void displayTeams(const vector<string>& teams) {
    cout << "NBA Teams:\n";
    for (int i = 0; i < teams.size(); ++i) {
        cout << i+1 << ". " << teams[i] << endl;
    }
}

vector<string> selectTeams(const vector<string>& teams) {
    int choice1;

    displayTeams(teams);

    cout << "Enter the numbers corresponding to the teams you want to select (separated by space): ";
    cin >> choice1;

    if (choice1 >= 1 && choice1 <= teams.size()) {
        selectedTeams.push_back(teams[choice1 - 1]);
    } else {
        cout << "Invalid choices. Please select valid numbers within the range and make sure they are not the same." << endl;
    }

    return selectedTeams;
}

vector<string> team1() {
    vector<string> nbaTeams = {
            "Atlanta Hawks", "Boston Celtics", "Brooklyn Nets", "Charlotte Hornets",
            "Chicago Bulls", "Cleveland Cavaliers", "Dallas Mavericks", "Denver Nuggets",
            "Detroit Pistons", "Golden State Warriors", "Houston Rockets", "Indiana Pacers",
            "LA Clippers", "Los Angeles Lakers", "Memphis Grizzlies", "Miami Heat",
            "Milwaukee Bucks", "Minnesota Timberwolves", "New Orleans Pelicans", "New York Knicks",
            "Oklahoma City Thunder", "Orlando Magic", "Philadelphia 76ers", "Phoenix Suns",
            "Portland Trail Blazers", "Sacramento Kings", "San Antonio Spurs", "Toronto Raptors",
            "Utah Jazz", "Washington Wizards"
    };
    vector<string> team1 = selectTeams(nbaTeams);
    for (const string& str : team1) {
        cout << str << endl;
    }
    return team1;
}

vector<string> team2() {
    vector<string> nbaTeams = {
            "Atlanta Hawks", "Boston Celtics", "Brooklyn Nets", "Charlotte Hornets",
            "Chicago Bulls", "Cleveland Cavaliers", "Dallas Mavericks", "Denver Nuggets",
            "Detroit Pistons", "Golden State Warriors", "Houston Rockets", "Indiana Pacers",
            "LA Clippers", "Los Angeles Lakers", "Memphis Grizzlies", "Miami Heat",
            "Milwaukee Bucks", "Minnesota Timberwolves", "New Orleans Pelicans", "New York Knicks",
            "Oklahoma City Thunder", "Orlando Magic", "Philadelphia 76ers", "Phoenix Suns",
            "Portland Trail Blazers", "Sacramento Kings", "San Antonio Spurs", "Toronto Raptors",
            "Utah Jazz", "Washington Wizards"
    };
    vector<string> team2 = selectTeams(nbaTeams);
    for (const string& str : team2) {
        cout << str << endl;
    }
    return team2;
}

vector<string> teamFile(const string& teamName) {
    string fileName = teamName + ".csv";
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        return {}; // return empty on error
    }

    vector<string> playerList;
    string line;
    // skip header
    getline(file, line);

    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        if (tokens.size() < 28) {
            continue; // skip incomplete
        }
        playerList.push_back(tokens[1]);
    }
    file.close();
    return playerList;
}

vector<string> teamxteam(const string& team1, const string& team2) {
    vector<string> playersTeam1 = teamFile(team1);
    vector<string> playersTeam2 = teamFile(team2);

    // sort both player lists
    sort(playersTeam1.begin(), playersTeam1.end());
    sort(playersTeam2.begin(), playersTeam2.end());

    vector<string> commonPlayers;
    // find common players
    set_intersection(playersTeam1.begin(), playersTeam1.end(),
                     playersTeam2.begin(), playersTeam2.end(),
                     back_inserter(commonPlayers));

    return commonPlayers;
}

vector<int> catGet() {
    cout << "Enter Categories: (1. Team) separated by space: ";
    // add more later, (2. stats, 3. awards, 4. playoffs, 5. etc.)
    for (int i = 0; i < 2; ++i) {
        int cat;
        cin >> cat;
        categories.push_back(cat);
    }
    return categories;
}

vector<string> openCat(const vector<int>& categories) {
    if (categories.size() != 2) {
        cerr << "Please select exactly two categories." << endl;
        return {};
    }

    int cat1 = categories[0];
    int cat2 = categories[1];
    if (cat1 == 1 && cat2 == 1) {
        vector<string> team1Selected = team1();
        vector<string> team2Selected = team2();

        selectedTeams.insert(selectedTeams.end(), team1Selected.begin(), team1Selected.end());
        selectedTeams.insert(selectedTeams.end(), team2Selected.begin(), team2Selected.end());

        return selectedTeams;
    } else if ((cat1 == 1 && cat2 == 2) || (cat1 == 2 && cat2 == 1)) {
        vector<string> team1Selected = team1();
    }else {
            cerr << "Selected categories not supported for this operation." << endl;
            return {};
        }
    }

int main() {
    cout << "All data is from sportsreference.com.\n\n";
    catGet();
    selectedTeams = openCat(categories);

    vector<string> commonPlayers = teamxteam(selectedTeams[0], selectedTeams[1]);

    cout << "\nCommon players between " << selectedTeams[0] << " and " << selectedTeams[1] << ":" << endl;
    for (const string& player : commonPlayers) {
        cout << player << endl;
    }

    return 0;
}