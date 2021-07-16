#include <fstream>
#include <sstream>
#include <vector>
#include <exception>
#include <cmath>
#include <conio.h>
#include <ctime>

using namespace std;

ostream &operator<<(ostream &out, const vector<pair<string, int>> &player)
{
    for (auto a : player)
        out << a.first << " " << a.second << "\n";
    return out;
}

istream &operator>>(istream &in, vector<pair<string, int>> &x)
{
    string str, s1, s2;
    while (getline(in, str))
    {
        stringstream s(str);
        s >> s1 >> s2;
        stringstream num(s2);
        int n;
        num >> n;
        x.push_back({s1, n});
    }
    return in;
}

void createTeam()
{
    string tName, pName;
    int spc;
    vector<pair<string, int>> player;
    cout << "\nEnter the team name : ";
    cin >> tName;
    fstream in, out;
    in.open(tName + ".txt", ios::in);
    if (!in)
    {
        for (int i = 0; i < 11; i++)
        {
            cin.ignore();
            cout << "\nPlayer " << i + 1 << " name : ";
            getline(cin, pName);
            cout << "Specilization [1]Batsman [2]Bowler :";
            cin >> spc;
            player.push_back(pair<string, int>(pName, spc));
        }
        out.open(tName + ".txt", ios::out);
        out << player;
        out.close();
    }
    else
        cout << "\n *** Team " << tName << " already exists *** \n";

    in.close();
}

string getPlayers(vector<pair<string, int>> &x, int n)
{
    string name;
    ifstream in;

    while (true)
    {
        try
        {
            cout << "\nEnter the Team " << n << " name : ";
            cin >> name;
            in.open(name + ".txt", ios::in);
            if (!in)
                throw runtime_error("\n *** Team " + name + " not exits ***\n");

            else
            {
                cout << "\n *** Team " << name << " found (Players loaded) ***\n";
                in >> x;
                break;
            }
        }
        catch (const exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    return name;
}

int toss(int &toss, int &elected)
{
    system("clear");
    int choice, pass;
    cout << "\n\n\n[1] Head [2]Tail \nEnter your choice : ";
    cin >> choice;
    srand(time(0));
    pass = rand() % 2 + 1;

    (pass == 1) ? cout << "\n*** HEAD ***\n" : cout << "\n*** Tail ***\n";

    if (choice == pass)
    {
        cout << "\n**** You win the toss ****\n";
        toss = 1;
        cout << "[1]Bat [2]Bowl\nEnter your choice : ";
        cin >> choice;
        elected = choice;
    }
    else
    {
        cout << "\n**** You lost the toss ****\n";
        toss = 2;
        srand(time(0));
        elected = rand() % 2 + 1;
    }
    return toss;
}

void dispOver(vector<char> x)
{
    for (auto a : x)
        cout << a << " ";
}
void swap(int &x, int &y)
{
    int temp;
    temp = x;
    x = y;
    y = temp;
}

int getRun(int speed, int meet)
{
    int run, diff;

    diff = abs(speed - meet);
    if (diff <= 2)
        run = 6;
    else if (diff > 2 && diff <= 5)
        run = 4;
    else if (diff > 5 && diff <= 10)
        run = 3;
    else if (diff > 10 && diff <= 15)
        run = 2;
    else if (diff > 15 && diff <= 20)
        run = 1;
    else if (diff > 20 && diff <= 25)
        run = 0;
    else
        run = -1;

    return run;
}

void take_space()
{
    while (true)
    {
        getche();
        break;
    }
}

void getShot(int speed, int &shot, int x)
{
    clock_t t;

    int meet = 150;
    cout << "(play)";
    t = time(0);
    take_space();
    t = time(0) - t;
    srand(time(0));
    meet = (meet - t * 10) + rand() % 9 + 1;
    cout << "\t(Bat Time)" << meet << "\t";
    shot = getRun(speed, meet);
}

void getShot(int speed, int &shot)
{
    int meet = rand() % 50 + 1;
    meet += 100;
    cout << "(Bat Time)" << meet << "\t";
    shot = getRun(speed, meet);
}
void batting(int team, vector<string> batsman, vector<int> &scores, int &totalScore, int &wickets, vector<string> bowler, int over, int target)
{

    int curOver = 0, striker = 0, non_striker = 1, b = 1, speed, old = 0, shot, curStrick = 1;

    while (curOver < over)
    {
        vector<char> curOverSmry;
        while (b == old)
        {
            try
            {
                srand(time(0));
                b = rand() % bowler.size() - 1;
                if (b < 0)
                    throw b;
            }
            catch (int b)
            {
                old = b;
            }
        }
        int ball = 1;
        while (ball <= 6)
        {
            if (curStrick <= 10)
            {
                srand(time(0));
                speed = rand() % 50 + 1;
                speed += 100;
                cout << "\n"
                     << bowler[b] << " bowls to " << batsman[striker] << "\t\t" << speed << "/kmph\t";
                if (team == 2)
                    getShot(speed, shot);
                else if (team == 1)
                    getShot(speed, shot, 1);
                if (shot >= 0)
                {
                    curOverSmry.push_back(shot + 48);
                    cout << shot << "\t";
                    totalScore += shot;
                    scores[striker] += shot;
                    if (shot == 1 || shot == 3)
                        swap(striker, non_striker);
                }
                else if (shot == -1)
                {
                    ++wickets;
                    cout << "wkt\t";
                    striker = ++curStrick;
                    curOverSmry.push_back('w');
                }
                cout << totalScore << "/" << wickets << "(" << curOver << "." << ball++ << ")\t";
                dispOver(curOverSmry);
                if (team == 2)
                    sleep(1);

                if (totalScore >= target || wickets == 11)
                {
                    ball = 7;
                    curOver = over + 1;
                    sleep(1);
                }
            }
            else 
            {
                cout << " \n *** All Out ***\n";
                sleep(2);
                ball = 7;
                curOver =over;
            }
        }
        swap(striker, non_striker);
        old = b;
        curOver++;
        curOverSmry.clear();
        if (curOver == over)
            sleep(1);
    }
}