#include <limits.h>
using namespace std;

class Team
{
    vector<pair<string, int>> player;
    string team;

public:
    Team() : player(11), team("") {}
    Team(vector<pair<string, int>> play, string name) : player(play), team(name) {}
    Team(const Team &x) : player(x.player), team(x.team) {}

    void disp();
    void operator=(const Team &x);
    string getPlayerName(int i) { return player[i].first; }
    string getTeamName() { return team; }
    int getSize() { return player.size(); }
    vector<string> getBowlers();
    vector<string> getPlayers();

    ~Team()
    {
        player.clear();
        team.clear();
    }
};

void Team ::disp()
{
    cout << "\n";
    cout << "\t ***** " << team << " *****\n";
    for (auto a : player)
    {
        cout << "\n"
             << a.first << "\t\t";
        (a.second == 1) ? cout << "Batsman /" : cout << "Bolwer 0";
    }
}

void Team ::operator=(const Team &x)
{
    for (int i = 0; i < x.player.size(); i++)
    {
        player[i].first = x.player[i].first;
        player[i].second = x.player[i].second;
    }
    team = x.team;
}

vector<string> Team ::getBowlers()
{
    vector<string> bowl;
    for (auto a : player)
        if (a.second == 2)
            bowl.push_back(a.first);

    return bowl;
}
vector<string> Team ::getPlayers()
{
    vector<string> bat;
    for (auto a : player)
        bat.push_back(a.first);
    return bat;
}

class Schedule
{
protected:
    Team Team1, Team2;
    string date;
    int over;

public:
    Schedule() {}

    virtual void setSchedule() {}
    ~Schedule() {}
};

class Match : public Schedule
{
protected:
    int totalScore1, totalScore2, wickets1, wickets2, tossWin, elected;
    vector<int> team1playersScore, team2playersScore;

public:
    Match() : Schedule(), totalScore1(0), totalScore2(0), wickets1(0), wickets2(0), tossWin(0), elected(0), team1playersScore(11, 0), team2playersScore(11, 0) {}

    void setSchedule();
    void playGame();
    void display(Team, vector<int>, int, int);

    ~Match() {}
};

void Match ::setSchedule()
{
    vector<pair<string, int>> players1, players2;
    string T1, T2;

    cout << "\nEnter the date of the match : ";
    cin >> date;
    cout << "\n";
    system("ls *.txt");

    T1 = getPlayers(players1, 1);
    T2 = getPlayers(players2, 2);

    Team temp1(players1, T1), temp2(players2, T2);

    Team1 = temp1;
    Team2 = temp2;

    cout << "\nEnter the number of overs : ";
    cin >> over;

    system("clear");
    Team1.disp();
    Team2.disp();
    sleep(4);
}

void Match::display(Team team, vector<int> playersScore, int wickets, int totalScore)
{
    system("clear");
    cout << "\n\n\tName \t\t\tRun\n";
    for (int i = 0; i < team.getSize(); i++)
        cout << "\n"
             << team.getPlayerName(i) << "\t\t\t" << playersScore[i];

    cout << "\n\n"
         << team.getTeamName() << " Score :" << totalScore << "/" << wickets;
}

void Match ::playGame()
{
    vector<string> Bowlers;
    vector<string> Batsman;

    system("clear");
    if (tossWin == 1 && elected == 1 || tossWin == 2 && elected == 2)
    {
        cout << "\n\n *** Use space button to bat ***\n";
        Bowlers = Team2.getBowlers();
        Batsman = Team1.getPlayers();
        batting(1, Batsman, team1playersScore, totalScore1, wickets1, Bowlers, over, INT_MAX);
        Bowlers.clear();
        Batsman.clear();
        Bowlers = Team1.getBowlers();
        Batsman = Team2.getPlayers();
        cout << "\n\n " << Team2.getTeamName() << " Needs " << totalScore1 + 1 << " runs to win\n";
        sleep(1);
        batting(2, Batsman, team2playersScore, totalScore2, wickets2, Bowlers, over, totalScore1 + 1);
    }
    else if (tossWin == 1 && elected == 2 || tossWin == 2 && elected == 1)
    {
        cout << "\n";
        Bowlers = Team1.getBowlers();
        Batsman = Team2.getPlayers();
        batting(2, Batsman, team2playersScore, totalScore2, wickets2, Bowlers, over, INT_MAX);
        Bowlers.clear();
        Batsman.clear();
        Bowlers = Team2.getBowlers();
        Batsman = Team1.getPlayers();
        cout << "\n\n " << Team1.getTeamName() << " Needs " << totalScore2 + 1 << " runs to win\n";
        sleep(1);
        cout << "\n *** Use space button to bat ***\n";
        batting(1, Batsman, team1playersScore, totalScore1, wickets1, Bowlers, over, totalScore2 + 1);
    }
}

class matchSummary : public Match
{
    string winner;

public:
    matchSummary() : Match(), winner("") {}

    void startMatch();
    void summary();
    friend void storeMatchDetails(matchSummary match);
    friend void showPreviousMatchDetails();
    ~matchSummary() {}
};

void matchSummary ::startMatch()
{
    system("clear");
    setSchedule();
    toss(tossWin, elected);
    cout << "\n";
    (tossWin == 1) ? cout << Team1.getTeamName() << " win the toss elected to " : cout << Team2.getTeamName() << " win the toss elected to ";
    (elected == 1) ? cout << " bat first" : cout << " bowl firstn";
    playGame();
}

void matchSummary ::summary()
{
    system("clear");
    cout << "\n\n\t*** " << Team1.getTeamName() << " ****\t\t\t**** " << Team2.getTeamName() << " ****\n";
    for (int i = 0; i < Team1.getSize(); i++)
        cout << "\n"
             << Team1.getPlayerName(i) << "\t" << team1playersScore[i] << "\t\t\t" << Team2.getPlayerName(i) << "\t" << team2playersScore[i];
    cout << "\n\n";
    cout << "\nTotal Score :" << totalScore1 << "/" << wickets1 << "\t\t\t"
         << "TotalScore : " << totalScore2 << "/" << wickets2 << "\n\n\n";

    if (totalScore1 > totalScore2)
    {
        winner = Team1.getTeamName();
        cout << "\n**** Team " << winner << " won the match ***";
    }
    else if (totalScore1 < totalScore2)
    {
        winner = Team2.getTeamName();
        cout << "\n**** Team " << winner << " won the match ***";
    }
    else
        cout << "\n**** Match tie ****";
}

void storeMatchDetails(matchSummary match)
{
    ofstream out;
    out.open("allMatchDetails.bin", ios::app | ios::binary | ios::out);
    out.write((char *)&match, sizeof(match));
    out.close();
}

void showPreviousMatchDetails()
{
    ifstream in;
    in.open("allMatchDetails.bin", ios::in);
    while (!in.eof())
    {
        matchSummary m;
        in.read((char *)&m, sizeof(m));
        m.summary();
    }
    in.close();
}