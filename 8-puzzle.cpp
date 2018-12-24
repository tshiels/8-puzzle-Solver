#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <cstdlib>
using namespace std;

int max_q = 0;
int num_expanded = 0;
int final_depth = 0;

struct Node
{
    int g_n;
    int h_n;
    int f_x;
    vector<vector<int> > state = {{0,0,0},{0,0,0},{0,0,0}};
};

struct Compare
{
    bool operator()(const Node& l, const Node& r) const
    {
        return l.f_x > r.f_x;
    }
};

int misplaced_tile(Node test, Node goal)
{
    int count = 0;
    
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (test.state.at(i).at(j) != goal.state.at(i).at(j))
            {
                if (test.state[i][j] != 0)
                {
                    ++count;
                }
            }
        }
    }
    return count;
}

int manhattan_dist(Node test, Node goal)
{
    int dist = 0;
    int x = 0;
    int y = 0;
    int temp;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (test.state.at(i).at(j) != 0)
            {
                temp = test.state.at(i).at(j);
                x = abs(i - ((temp - 1) / 3));
                y = abs(j - ((temp - 1) % 3));
                dist += x + y;
            }
        }
    }
    return dist;
}

void print_board(Node ndptr)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cout << ndptr.state.at(i).at(j) << ' ';
        }
        cout << endl;
    }
}

void expand(Node curr, priority_queue<Node, vector<Node>, Compare> & open, 
map<vector<vector<int> >, bool> & visited, int heuristic)
{
    Node temp, temp2, temp3, temp4, goal;
    goal.state = {{1,2,3},{4,5,6},{7,8,0}};
    
    temp.g_n = curr.g_n + 1;
    temp2.g_n = curr.g_n + 1;
    temp3.g_n = curr.g_n + 1;
    temp4.g_n = curr.g_n + 1;
    
    temp.state = curr.state;
    temp2.state = curr.state;
    temp3.state = curr.state;
    temp4.state = curr.state;
    
    //find position of 0
    int x = 0;
    int y = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (curr.state.at(i).at(j) == 0)
            {
                x = i;
                y = j;
            }
        }
    }
    //check all moves
    
    //move right
    if (y < 2)
    {
        int temp_int = 0;
        temp_int = temp.state.at(x).at(y);
        temp.state.at(x).at(y) = temp.state.at(x).at(y + 1);
        temp.state.at(x).at(y + 1) = temp_int;
        
        if (heuristic == 1) //uniform cost search
        {
            temp.f_x = temp.g_n;
        }
        else if (heuristic == 2) //misplaced tile
        {
            temp.h_n = misplaced_tile(temp, goal);
            temp.f_x = temp.h_n + temp.g_n;
        }
        else if (heuristic == 3) //manhattan distance
        {
            temp.h_n = manhattan_dist(temp, goal);
            temp.f_x = temp.h_n + temp.g_n;
        }
        //if not found, then insert
        if (visited.find(temp.state) == visited.end())
        {
            visited.insert(pair<vector<vector<int> >, bool>(temp.state, 0));
            open.push(temp);
            ++num_expanded;
        }
    }
    
    //move left
    if (y > 0)
    {
        int temp_int2 = 0;
        temp_int2 = temp2.state.at(x).at(y);
        temp2.state.at(x).at(y) = temp2.state.at(x).at(y - 1);
        temp2.state.at(x).at(y - 1) = temp_int2;
        
        if (heuristic == 1) //uniform cost search
        {
            temp2.f_x = temp2.g_n;
        }
        else if (heuristic == 2) //misplaced tile
        {
            temp2.h_n = misplaced_tile(temp2, goal);
            temp2.f_x = temp2.h_n + temp2.g_n;
        }
        else if (heuristic == 3) //manhattan distance
        {
            temp2.h_n = manhattan_dist(temp2, goal);
            temp2.f_x = temp2.h_n + temp2.g_n;
        }
        //if not already visited, insert
        if (visited.find(temp2.state) == visited.end())
        {
            visited.insert(pair<vector<vector<int> >, bool>(temp2.state, 0));
            open.push(temp2);
            ++num_expanded;
        }
    }
    
    //move up
    if (x > 0)
    {
        int temp_int3 = 0;
        temp_int3 = temp3.state.at(x).at(y);
        temp3.state.at(x).at(y) = temp3.state.at(x - 1).at(y);
        temp3.state.at(x - 1).at(y) = temp_int3;
        
        if (heuristic == 1) //uniform cost search
        {
            temp3.f_x = temp3.g_n;
        }
        else if (heuristic == 2) //misplaced tile
        {
            temp3.h_n = misplaced_tile(temp3, goal);
            temp3.f_x = temp3.h_n + temp3.g_n;
        }
        else if (heuristic == 3) //manhattan distance
        {
            temp3.h_n = manhattan_dist(temp3, goal);
            temp3.f_x = temp3.h_n + temp3.g_n;
        }
        //check if visited
        if (visited.find(temp3.state) == visited.end())
        {
            visited.insert(pair<vector<vector<int> >, bool>(temp3.state, 0));
            open.push(temp3);
            ++num_expanded;
        }
    }
    
    //move down
    if (x < 2)
    {
        int temp_int4 = 0;
        temp_int4 = temp4.state.at(x).at(y);
        temp4.state.at(x).at(y) = temp4.state.at(x + 1).at(y);
        temp4.state.at(x + 1).at(y) = temp_int4;
        
        if (heuristic == 1) //uniform cost search
        {
            temp4.f_x = temp4.g_n;
        }
        else if (heuristic == 2) //misplaced tile
        {
            temp4.h_n = misplaced_tile(temp4, goal);
            temp4.f_x = temp4.h_n + temp4.g_n;
        }
        else if (heuristic == 3) //manhattan distance
        {
            temp4.h_n = manhattan_dist(temp4, goal);
            temp4.f_x = temp4.h_n + temp4.g_n;
        }
        //check if visited
        if (visited.find(temp4.state) == visited.end())
        {
            visited.insert(pair<vector<vector<int> >, bool>(temp4.state, 0));
            open.push(temp4);
            ++num_expanded;
        }
    }
    return;
}

bool first_iteration = 1;

Node a_star(Node init, Node goal, int heuristic)
{
    priority_queue<Node, vector<Node>, Compare> open; //create queue
    open.push(init);
    
    map <vector<vector<int> >, bool> visited; //visited nodes
    visited.insert(pair<vector<vector<int> >,bool>(init.state, 0));
    
    while (1)
    {
        if (open.empty()) //IF EMPTY then return Failure
        {
            cout << "Could not find a solution." << endl;
            exit(0);
        }
        
        Node curr = open.top(); //REMOVE_FRONT
        open.pop();
        
        if (!first_iteration)
        {
            cout << "The best state to expand with a g(n) = "
                << curr.g_n << " and h(n) = " << curr.h_n << " is..." << endl;
            print_board(curr);
            cout << "Expanding this node..." << endl;
        }
        else
        {
            cout << "Expanding state: " << endl;
            print_board(curr);
            cout << endl;
            first_iteration = 0;
        }
        //print_board(curr);
        //cout << endl;
        
        if (max_q < open.size())
        {
            max_q = open.size();
        }
        //1=UCS, 2=MTH, 3=MDH
        if ((misplaced_tile(curr, goal) == 0) && (heuristic < 3)) //if GOAL state
        {
            final_depth = curr.g_n;
            return curr;
        }
        else if ((manhattan_dist(curr, goal) == 0) && (heuristic == 3))
        {
            final_depth = curr.g_n;
            return curr;
        }
        expand(curr, open, visited, heuristic);
    }
}

int main()
{
    Node start;
    start.g_n = 0;
    start.h_n = 0;
    start.f_x = 0;
    
    start.state = {{0,1,2},{4,5,3},{7,8,6}};
    Node goal;
    goal.state = {{1,2,3},{4,5,6},{7,8,0}};
    
    Node custom;
    custom.g_n = 0;
    custom.h_n = 0;
    custom.f_x = 0;
    
    cout << "Welcome to Bertie Woosters 8-puzzle solver." << endl;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle."
        << endl;
    int puzzle;
    cin >> puzzle;
    
    if (puzzle == 1)
    {
        cout << "Enter your choice of algorithm." << endl;
        cout << "1. Uniform Cost Search" << endl;
        cout << "2. A* with Misplaced Tile heuristic" << endl;
        cout << "3. A* with Manhattan Distance heuristic" << endl;
        int heur;
        cin >> heur;
        while (!((heur >= 0) && (heur <= 3)))
        {
            cout << "Invalid Choice." << endl;
            cin >> heur;
        }
        
        a_star(start, goal, heur);
    }
    else if (puzzle == 2)
    {
        cout << "Enter your puzzle, use a zero to represent the blank." << endl;
        cout << "Enter the first row, use space or tabs between numbers: ";
        int v,v2,v3;
        cin >> v >> v2 >> v3;
    
        custom.state.at(0).at(0) = v;
        custom.state.at(0).at(1) = v2;
        custom.state.at(0).at(2) = v3;
    
        cout << "Enter the second row, use space or tabs between numbers: ";
        cin >> v >> v2 >> v3;
    
        custom.state.at(1).at(0) = v;
        custom.state.at(1).at(1) = v2;
        custom.state.at(1).at(2) = v3;
    
        cout << "Enter the third row, use space or tabs between numbers: ";
        cin >> v >> v2 >> v3;
    
        custom.state.at(2).at(0) = v;
        custom.state.at(2).at(1) = v2;
        custom.state.at(2).at(2) = v3;
        
        cout << "Enter your choice of algorithm." << endl;
        cout << "1. Uniform Cost Search" << endl;
        cout << "2. A* with Misplaced Tile heuristic" << endl;
        cout << "3. A* with Manhattan Distance heuristic" << endl;
        int heur2;
        cin >> heur2;
        while (!((heur2 >= 0) && (heur2 <= 3)))
        {
            cout << "Invalid Choice." << endl;
            cin >> heur2;
        }
        
        a_star(custom, goal, heur2);
    }
    else
    {
        cout << "Invalid Choice." << endl;
        exit(0);
    }
    cout << endl;
    cout << "Goal!!" << endl;
    cout << "To solve this problem the search algorithm expanded a total of " 
        << num_expanded << " nodes." << endl;
    cout << "The maximum number of nodes in the queue at any one time was "
        << max_q << endl;
    cout << "The depth of the goal node was " << final_depth << endl;
    return 0;
}