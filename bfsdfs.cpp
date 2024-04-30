#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
const int MAX_N = 25;

void BFS(int G[MAX_N][MAX_N], int start, int n)
{
    int visited[MAX_N] = {0};
    queue<int> q;
    int i = start;
    #pragma omp critical
    {
        cout << i;
    }
    visited[i] = 1;
    q.push(i);
    while (!q.empty())
    {
        i = q.front();
        q.pop();
        for (int j = 0; j < n; j++)
        {
            if (G[i][j] == 1 && visited[j] == 0)
            {
                #pragma omp critical
                {
                    cout << j;
                }
                visited[j] = 1;
                q.push(j);
            }
        }
    }
}

void DFS(int G[MAX_N][MAX_N], int start, int n)
{
    int visited[MAX_N] = {0};
    stack<int> s;
    s.push(start);
    while (!s.empty())
    {
        int i = s.top();
        s.pop();
        if (visited[i] == 0)
        {
            #pragma omp critical
            {
                cout << i;
            }
            visited[i] = 1;
            for (int j = n - 1; j >= 0; j--)
            {
                if (G[i][j] == 1 && visited[j] == 0)
                {
                    s.push(j);
                }
            }
        }
    }
}

int main()
{
    int n;
    cout << "Enter n => ";
    cin >> n;
    if (n > MAX_N)
    {
        cout << "limit exceeded, try again !!";
        return 1;
    }
    int G[MAX_N][MAX_N];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> G[i][j];
        }
    }

    double start_time;
    double end_time;

    start_time = omp_get_wtime();
    BFS(G, 0, n);
    cout << endl;
    DFS(G, 0, n);
    cout << endl;
    end_time = omp_get_wtime();
    double sequential_time = end_time - start_time;
    cout << sequential_time << endl;

    start_time = omp_get_wtime();
#pragma omp parallel
    {
        #pragma omp single nowait
        {
            BFS(G, 0, n);
        }
        #pragma omp single nowait
        {
            DFS(G, 0, n);
        }
    }
    cout << endl;
    end_time = omp_get_wtime();
    double parallel_time = end_time - start_time;
    cout << parallel_time << endl;

    return 0;
}
