#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class NFA
{
    int noOfStates;
    unordered_set<char> states;
    int noOfSymbols;
    unordered_set<char> symbols;
    int noOfTransitions;
    unordered_map<char, vector<pair<char, char>>> transitions;
    set<char> initialStates;
    set<char> finalStates;

    void printStates()
    {
        cout << "The states are:\n";
        for (auto it : states)
            cout << it << " ";
        cout << endl;
    }

public:
    NFA(int nst, int nsy, int ntr) : noOfStates{nst}, noOfSymbols{nsy}, noOfTransitions{ntr}
    {
        // Epsilon is valid symbol for all NFA
        symbols.insert('e');
    }

    void inputSymbols()
    {
        cout << "Enter symbols. Each symbols must be represented with a single character\nEpsilon is already considered and should not be entered here\n";
        char curr;
        for (int i = 0; i < noOfSymbols; i++)
        {
            cin >> curr;
            symbols.insert(curr);
        }
    }

    void inputStates()
    {
        cout << "Enter the states (Each state must be represented by a single character): ";
        char curr;
        for (int i = 0; i < noOfStates; i++)
        {
            cin >> curr;
            states.insert(curr);
        }
        printStates();

        cout << "Enter no. of initial states: ";
        int is;
        cin >> is;
        cout << "Enter initial states\n";
        for (int i = 0; i < is; i++)
        {
            cin >> curr;
            initialStates.insert(curr);
        }

        cout << "Enter no. final states\n";
        int fs;
        cin >> fs;
        cout << "Enter final states\n";
        for (int i = 0; i < fs; i++)
        {
            cin >> curr;
            finalStates.insert(curr);
        }
    }

    void inputTransitions()
    {
        cout << "Enter transitions in the format startstate symbol end state\ne is taken as epsilon\n";
        char from, s, to; // s - symbol, from - from state, to - to state.
        int i = 0;
        while (i < noOfTransitions)
        {
            cin >> from >> s >> to;
            if (states.find(from) == states.end() || states.find(to) == states.end())
            {
                cout << "Invalid state\n";
                continue;
            }
            else if (symbols.find(s) == symbols.end())
            {
                cout << "Invalid symbol\n";
                continue;
            }
            else
            {
                transitions[from].push_back(make_pair(s, to));
                i++;
            }
        }
    }

    void removeEpsilonTransition(char from, char to)
    {
        auto to_trans = transitions[to];
        auto from_trans = transitions[from];
        for (auto it = from_trans.begin(); it != from_trans.end(); it++)
        {
            if (it->first == 'e' && it->second == to)
            {
                transitions[from].erase(it);
                break;
            }
        }
        for (auto t : to_trans)
        {
            if (t.first != 'e')
            {
                transitions[from].push_back({t.first, t.second});
            }
            else
            {
                removeEpsilonTransition(to, t.second);
            }
        }
        if (initialStates.find(from) != initialStates.end())
        {
            initialStates.insert(to);
        }
        if (finalStates.find(to) != finalStates.end())
        {
            finalStates.insert(from);
        }
    }

    void findNFA()
    {
        for (auto it : transitions)
        {
            auto from = it.first;
            auto trans = it.second;
            for (auto t : trans)
            {
                if (t.first == 'e')
                {
                    removeEpsilonTransition(from, t.second);
                }
            }
        }
    }

    void printNFA()
    {
        cout << "\nStart states: \n";
        for (auto s : initialStates)
        {
            cout << s << ", ";
        }
        cout << "\nEnd states: \n";
        for (auto s : finalStates)
        {
            cout << s << ", ";
        }
        cout << "\nTransitions: \n";
        for (auto t : transitions)
        {
            for (auto trans : t.second)
            {
                cout << t.first << "\t" << trans.first << "\t" << trans.second << "\n";
            }
        }
    }
};

int main()
{
    int states, symbols, transitions;
    cout << "Enter number of states: ";
    cin >> states;
    cout << "Enter number of input symbols: ";
    cin >> symbols;
    cout << "Enter number of transitions: ";
    cin >> transitions;
    NFA z{states, symbols, transitions};
    z.inputStates();
    z.inputSymbols();
    z.inputTransitions();
    z.findNFA();
    z.printNFA();
}
