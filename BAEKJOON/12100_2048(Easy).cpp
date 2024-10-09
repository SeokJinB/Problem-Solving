#include <iostream>
#include <vector>

using namespace std;

void moveUp(vector<vector<int>>& board)
{
    int n = board.size();
    vector<vector<bool>> combined(n, vector<bool>(n, false));

    while (true)
    {
        vector<vector<int>> temp(board);

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // 현재 행의 값과 이전 행의 값이 같고, 합져진 적이 없는 블록일 때 계산
                if (board[i - 1][j] == board[i][j] && board[i - 1][j] != 0 && !combined[i - 1][j] && !combined[i][j])
                {
                    board[i - 1][j] *= 2;
                    board[i][j] = 0;
                    combined[i - 1][j] = true;
                }
                // 현재 행의 값은 0이 아닌데 이전 행의 값이 0일 때 shift
                else if (board[i - 1][j] == 0 && board[i][j] != 0)
                {
                    board[i - 1][j] = board[i][j];
                    board[i][j] = 0;
                    combined[i - 1][j] = combined[i][j];
                }
            }
        }
        
        // 처음 상태와 달라진 게 없을 때 종료
        if (temp == board)
            return;
    }
}

void moveDown(vector<vector<int>>& board)
{
    int n = board.size();
    vector<vector<bool>> combined(n, vector<bool>(n, false));
    while (true)
    {
        vector<vector<int>> temp(board);
        for (int i = n - 1; i > 0; i--)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] != 0 && board[i][j] == board[i - 1][j] && !combined[i][j] && !combined[i - 1][j])
                {
                    board[i][j] *= 2;
                    board[i - 1][j] = 0;
                    combined[i][j] = true;
                }
                else if (board[i][j] == 0 && board[i - 1][j] != 0)
                {
                    board[i][j] = board[i - 1][j];
                    board[i - 1][j] = 0;
                    combined[i][j] = combined[i - 1][j];
                }
            }
        }
        if (temp == board)
            return;
    }
}

void moveLeft(vector<vector<int>>& board)
{
    int n = board.size();
    vector<vector<bool>> combined(n, vector<bool>(n, false));
    while (true)
    {
        vector<vector<int>> temp(board);

        for (int j = 1; j < n; j++)
        {
            for (int i = 0; i < n; i++)
            {
                if (board[i][j - 1] != 0 && board[i][j] == board[i][j - 1] && !combined[i][j - 1] && !combined[i][j])
                {
                    board[i][j - 1] *= 2;
                    board[i][j] = 0;
                    combined[i][j - 1] = true;
                }
                else if (board[i][j - 1] == 0 && board[i][j] != 0)
                {
                    board[i][j - 1] = board[i][j];
                    board[i][j] = 0;
                    combined[i][j - 1] = combined[i][j];
                }
            }
        }
        if (temp == board)
            return;
    }
}

void moveRight(vector<vector<int>>& board)
{
    int n = board.size();
    vector<vector<bool>> combined(n, vector<bool>(n, false));
    while (true)
    {
        vector<vector<int>> temp(board);

        for (int j = n - 1; j > 0; j--)
        {
            for (int i = 0; i < n; i++)
            {
                if (board[i][j] != 0 && board[i][j - 1] == board[i][j] && !combined[i][j] && !combined[i][j - 1])
                {
                    board[i][j] *= 2;
                    board[i][j - 1] = 0;
                    combined[i][j] = true;
                }
                else if (board[i][j] == 0 && board[i][j - 1] != 0)
                {
                    board[i][j] = board[i][j - 1];
                    board[i][j - 1] = 0;
                    combined[i][j] = combined[i][j - 1];
                }
            }
        }
        if (temp == board)
            return;
    }
}

int getMax(vector<vector<int>>& board)
{
    int n = board.size();
    int max = -1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (max < board[i][j])
                max = board[i][j];
        }
    }
    return max;
}

// 중복 순열 계산 (Backtracking)
void generatePermutations(vector<char>& arr, vector<char>& perm, int depth, int n, int m, vector<vector<char>>& result)
{
    if (depth == m)
    {
        result.push_back(perm);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        perm.push_back(arr[i]);
        generatePermutations(arr, perm, depth + 1, n, m, result);
        perm.pop_back();
    }
}

vector<vector<char>> getPermutations(vector<char>& arr, int n, int m)
{
    vector<vector<char>> result;
    vector<char> perm;
    generatePermutations(arr, perm, 0, n, m, result);
    return result;
}

int main()
{
    int N;
    cin >> N;
    vector<vector<int>> board(N, vector<int>(N));
    vector<char> udlr = { 'U','D','L','R' };
    vector<vector<char>> perm = getPermutations(udlr, 4, 5);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> board[i][j];
        }
    }
    vector<vector<int>> initBoard(board);

    int answer = -1;

    /*for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }*/

    for (vector<char> vec : perm)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                board[i][j] = initBoard[i][j];
            }
        }

        for (char c : vec)
        {
            switch (c)
            {
            case 'U':
                moveUp(board); break;
            case 'D':
                moveDown(board); break;
            case 'L':
                moveLeft(board); break;
            case 'R':
                moveRight(board); break;
            }
        }

        answer = max(answer, getMax(board));
    }

    cout << answer;

    return 0;
}