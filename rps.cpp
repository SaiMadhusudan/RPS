#include <bits/stdc++.h>

using namespace std;

char states[4] = "RPS";

typedef struct node Node;
typedef pair<int, set<int>> My_pair;

int max_index(int arr[])
{
    return max({pair<int, int>{arr[0], 0}, {arr[2], 2}, {arr[1], 1}}).second;
}

void set_arr(const set<int> all, int A[])
{
    int i = 0;
    for (auto itr : all)
        A[i++] = itr;
}

class node
{
public:
    char state;
    int St;
    int trans[3];
};

map<My_pair, int> Created_Nodes_rev;
map<int, My_pair> Created_Nodes;

void add_to_map(int &n, My_pair temp_set)
{
    Created_Nodes[n] = temp_set;
    Created_Nodes_rev[temp_set] = n;
    n++;
}

int main()
{
    int N;
    cin >> N;

    Node Node_s[N];

    int size_[3] = {0, 0, 0};

    set<int> all;

    for (int i = 0; i < N; i++)
    {
        cin >> Node_s[i].state;
        for (int j = 0; j < 3; j++)
            cin >> Node_s[i].trans[j];

        for (int j = 0; j < 3; j++)
        {
            if (Node_s[i].state == states[j])
            {
                size_[j]++;
                Node_s[i].St = j;
            }
        }
        all.insert(i + 1);
    }

    int zero_state = (max_index(size_) + 1) % 3;

    Node Final_nodes[1000];
    int new_nodes = 0;

    Final_nodes[0].state = states[zero_state];
    Final_nodes[0].St = zero_state;

    Created_Nodes[0] = {zero_state, all};
    Created_Nodes_rev[{zero_state, all}] = 0;
    int nodes_created = 1;

    deque<int> Q;
    Q.push_back(0);

    while (!Q.empty())
    {
        int top_node = Q.front();
        Q.pop_front();

        set<int> groups[3];
        int *arr_groups[3];
        int arr_sizes[3];

        set<int> temp;
        int char_state;
        tie(char_state, temp) = Created_Nodes[top_node];

        int set_size = temp.size();
        int A[temp.size()];
        set_arr(temp, A);

        for (int i = 0; i < set_size; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (Node_s[A[i] - 1].St == j)
                    groups[j].insert(A[i]);
            }
        }

        for (int j = 0; j < 3; j++)
        {
            arr_sizes[j] = groups[j].size();
            arr_groups[j] = (int *)malloc(sizeof(int) * arr_sizes[j]);
            set_arr(groups[j], arr_groups[j]);
        }

        int max_state[3] = {0, 0, 0};

        for (int j = 0; j < 3; j++)
        {
            int final[3] = {0, 0, 0};
            set<int> trans_set;

            for (int i = 0; i < arr_sizes[j]; i++)
            {
                trans_set.insert(Node_s[arr_groups[j][i] - 1].trans[char_state]);
                final[Node_s[Node_s[arr_groups[j][i] - 1].trans[char_state] - 1].St]++;
            }
            max_state[j] = (max_index(final) + 1) % 3;

            My_pair temp_set;

            temp_set = {max_state[j], trans_set};
            if (arr_sizes[j] != 0 && Created_Nodes_rev.find(temp_set) == Created_Nodes_rev.end())
            {
                Q.push_back(nodes_created);
                add_to_map(nodes_created, temp_set);
            }
            if (arr_sizes[j] != 0)
                Final_nodes[top_node].trans[j] = Created_Nodes_rev[temp_set];
            else
                Final_nodes[top_node].trans[j] = 0;
        }
        new_nodes++;
    }

    cout << new_nodes << '\n';

    for (int i = 0; i < new_nodes; i++)
    {
        cout << states[Created_Nodes[i].first] << " ";
        for (int j = 0; j < 3; j++)
            cout << Final_nodes[i].trans[j] + 1 << " ";
        cout << endl;
    }
    return (0);
}
