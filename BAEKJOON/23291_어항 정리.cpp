#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print(vector<vector<int>>& arr)
{
    for (vector<int> v : arr)
    {
        for (int i : v)
            cout << i << "\t";
        cout << endl;
    }
    cout << endl;
}

void shift(vector<vector<int>>& arr)
{
    int N = arr.size();

    int n = 0;
    while (true)
    {
        if (arr[N - 1][0] != 0 || n >= N)
        {
            return;
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 1; j < N; j++)
            {
                if (arr[i][j - 1] == 0 && arr[i][j] == 0)
                {
                    continue;
                }

                arr[i][j - 1] = arr[i][j];

                if (j == N - 1)
                    arr[i][j] = 0;
            }
        }

        n++;
    }
}

vector<vector<int>> adjust(vector<vector<int>>& arr)
{
    int N = arr.size();
    vector<vector<int>> result(arr);
    vector<vector<bool>> check(N, vector<bool>(N, false));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (arr[i][j] == 0)
                continue;

            int gap = 0;

            if (i - 1 >= 0 && arr[i - 1][j] != 0)
            {
                gap = abs(arr[i][j] - arr[i - 1][j]) / 5;

                if (arr[i][j] > arr[i - 1][j])
                {
                    result[i][j] -= gap;
                }
                else
                {
                    result[i][j] += gap;
                }
            }

            if (i + 1 < N && arr[i + 1][j] != 0)
            {
                gap = abs(arr[i][j] - arr[i + 1][j]) / 5;

                if (arr[i][j] > arr[i + 1][j])
                {
                    result[i][j] -= gap;
                }
                else
                {
                    result[i][j] += gap;
                }
            }

            if (j - 1 >= 0 && arr[i][j - 1] != 0)
            {
                gap = abs(arr[i][j] - arr[i][j - 1]) / 5;

                if (arr[i][j] > arr[i][j - 1])
                {
                    result[i][j] -= gap;
                }
                else
                {
                    result[i][j] += gap;
                }
            }

            if (j + 1 < N && arr[i][j + 1] != 0)
            {
                gap = abs(arr[i][j] - arr[i][j + 1]) / 5;

                if (arr[i][j] > arr[i][j + 1])
                {
                    result[i][j] -= gap;
                }
                else
                {
                    result[i][j] += gap;
                }
            }
        }
    }
    //print(result);
    return result;
}

vector<vector<int>> rotate90(vector<vector<int>>& arr)
{
    int n = arr.size();
    int m = arr[0].size();

    vector<vector<int>> result(m, vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            result[j][n - i - 1] = arr[i][j];
        }
    }
    return result;
}

int main()
{
    int N, K;
    int answer = 0;

    cin >> N >> K;
    vector<vector<int>> arr(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++)
    {
        cin >> arr[N - 1][i];
    }

    while (true)
    {
        int max = *max_element(arr[N - 1].begin(), arr[N - 1].end());
        int min = *min_element(arr[N - 1].begin(), arr[N - 1].end());

        if (max - min <= K)
            break;

        for (int i = 0; i < N; i++)
        {
            if (min == arr[N - 1][i])
            {
                arr[N - 1][i]++;
            }
        }

        arr[N - 2][1] = arr[N - 1][0];
        arr[N - 1][0] = 0;
        shift(arr);

        bool isPossible = true;
        vector<vector<int>> prev(arr);

        while (true)
        {
            int row, col;
            for (int i = 0; i < N; i++)
            {
                if (arr[i][0] != 0)
                {
                    row = i; break;
                }
            }

            for (int j = 0; j < N; j++)
            {
                if (arr[row][j] == 0)
                {
                    col = j; break;
                }
            }

            vector<vector<int>> temp(N - row, vector<int>(col));
            for (int i = row; i < N; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    temp[i - row][j] = arr[i][j];
                    arr[i][j] = 0;
                }
            }
            temp = rotate90(temp);

            shift(arr);

            for (int i = 0; i < temp.size(); i++)
            {
                for (int j = 0; j < temp[i].size(); j++)
                {
                    arr[N - temp.size() - 1 + i][j] = temp[i][j];
                }
            }
            
            bool quit = false;
            for (int j = 0; j < N; j++)
            {
                for (int i = N - 1; i > 0; i--)
                {
                    if (arr[i][j] == 0 && arr[i - 1][j] != 0)
                    {
                        arr = prev;
                        quit = true;
                        break;
                    }
                }
                if (quit)
                    break;
            }
            if (quit)
                break;

            prev = arr;
        }

        arr = adjust(arr);

        vector<int> newarr;
        for (int j = 0; j < N; j++)
        {
            for (int i = N - 1; i >= 0; i--)
            {
                if (arr[i][j] == 0)
                    break;
                newarr.emplace_back(arr[i][j]);
            }

            if (arr[N - 1][j] == 0)
                break;
        }
        
        for (int j = 0; j < N; j++)
        {
            arr[N - 1][j] = newarr[j];
        }

        for (int i = 0; i < N - 1; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (arr[i][j] == 0)
                    continue;
                arr[i][j] = 0;
            }
        }

        for (int i = 0; i < N / 2; i++)
        {
            arr[N - 2][N - 1 - i] = arr[N - 1][i];
            arr[N - 1][i] = 0;
        }
        shift(arr);

        vector<vector<int>> temp;
        for (int i = N - 2; i < N; i++)
        {
            vector<int> tmp;
            for (int j = 0; j < N / 4; j++)
            {
                tmp.emplace_back(arr[i][j]);
                arr[i][j] = 0;
            }
            temp.emplace_back(tmp);
        }

        shift(arr);
        temp = rotate90(temp);
        temp = rotate90(temp);

        for (int i = N - 4; i < N - 2; i++)
        {
            for (int j = 0; j < N / 4; j++)
            {
                arr[i][j] = temp[i - N + 4][j];
            }
        }
        //print(arr);
        arr = adjust(arr);

        vector<int> v2;
        for (int j = 0; j < N; j++)
        {
            for (int i = N - 1; i >= 0; i--)
            {
                if (arr[i][j] == 0)
                    break;
                v2.emplace_back(arr[i][j]);
            }
            if (arr[N - 1][j] == 0)
                break;
        }

        for (int i = 0; i < N; i++)
        {
            arr[N - 1][i] = v2[i];
        }

        for (int i = 0; i < N - 1; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (arr[i][j] == 0)
                    continue;

                arr[i][j] = 0;
            }
        }
        //print(arr);
        answer++;

    }

    cout << answer;
}