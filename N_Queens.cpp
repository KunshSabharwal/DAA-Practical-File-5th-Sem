#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <ctime>
using namespace std;

unordered_set<int> cols;
unordered_set<int> posDiag; // (r + c)
unordered_set<int> negDiag; // (r - c)

void backtrack(vector<vector<string>> &result, int n, vector<string> &board, int row)
{
    if (row == n)
    {
        result.push_back(board);
        return;
    }

    for (int col = 0; col < n; col++)
    {
        if (cols.count(col) || posDiag.count(row + col) || negDiag.count(row - col))
            continue;

        cols.insert(col);
        posDiag.insert(row + col);
        negDiag.insert(row - col);
        board[row][col] = 'Q';

        backtrack(result, n, board, row + 1);

        cols.erase(col);
        posDiag.erase(row + col);
        negDiag.erase(row - col);
        board[row][col] = '.';
    }
}

vector<vector<string>> solveNQueens(int n)
{
    vector<vector<string>> result;
    vector<string> board(n, string(n, '.'));
    cols.clear();
    posDiag.clear();
    negDiag.clear();
    backtrack(result, n, board, 0);
    return result;
}

int main()
{
    vector<int> sizes = {4, 8, 12};

    for (int n : sizes)
    {
        clock_t start = clock();
        vector<vector<string>> solutions = solveNQueens(n);
        clock_t end = clock();

        double time_taken = double(end - start) / CLOCKS_PER_SEC;

        cout << "N = " << n << "\n";
        cout << "Total Solutions: " << solutions.size() << "\n";
        cout << "Time Taken: " << time_taken << " sec\n";

        if (!solutions.empty())
        {
            cout << "Example Solution:\n";
            for (const string &row : solutions[0])
                cout << row << "\n";
        }
        cout << "-----------------------------\n";
    }

    return 0;
}
