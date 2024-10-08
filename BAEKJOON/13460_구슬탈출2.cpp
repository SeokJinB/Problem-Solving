#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Ball
{
public:
	int rx, ry, bx, by, dist;
};

int bfs(vector<vector<char>> board, Ball& ball)
{
	int answer = -1;
	queue<Ball> q;
	bool visited[10][10][10][10] = { false };
	int updown[4] = { -1,1,0,0 };
	int leftright[4] = { 0,0,1,-1 };
	
	q.push(ball);
	visited[ball.rx][ball.ry][ball.bx][ball.by] = true;

	while (!q.empty())
	{
		Ball current = q.front();
		q.pop();

		// 1. 이동이 10번을 초과: return -1
		if (current.dist > 10)
		{
			break;
		}

		// 2. red가 구멍에 들어가고 blue가 구멍에 안 들어가면 dist 반환
		if (board[current.rx][current.ry] == 'O' && board[current.bx][current.by] != 'O')
		{
			answer = current.dist;
			break;
		}

		// 3. 한 칸씩 이동
		for (int i = 0; i < 4; i++)
		{
			int nrx = current.rx;
			int nry = current.ry;
			int nbx = current.bx;
			int nby = current.by;
			
			while (true)
			{
				// 3-1. red의 위치가 벽 또는 구멍이 아니면 이동
				if (board[nrx][nry] != '#' && board[nrx][nry] != 'O')
				{
					nrx += updown[i];
					nry += leftright[i];
				}
				else
				{
					if (board[nrx][nry] == '#')
					{
						nrx -= updown[i];
						nry -= leftright[i];
					}
					break;
				}
			}

			while (true)
			{
				// 3-2. blue의 위치가 벽 또는 구멍이 아니면 이동
				if (board[nbx][nby] != '#' && board[nbx][nby] != 'O')
				{
					nbx += updown[i];
					nby += leftright[i];
				}
				else
				{
					if (board[nbx][nby] == '#')
					{
						nbx -= updown[i];
						nby -= leftright[i];
					}
					break;
				}
			}
			
			// 4. red와 blue가 같은 위치일 때 더 많이 움직인 공의 위치를 원상태로 복구
			if (nrx == nbx && nry == nby)
			{
				if (board[nrx][nry] != 'O')
				{
					int rdist = abs(nrx - current.rx) + abs(nry - current.ry);
					int bdist = abs(nbx - current.bx) + abs(nby - current.by);
					
					if (rdist > bdist)
					{
						nrx -= updown[i];
						nry -= leftright[i];
					}
					else
					{
						nbx -= updown[i];
						nby -= leftright[i];
					}
				}
			}

			if (!visited[nrx][nry][nbx][nby])
			{
				Ball next;
				next.rx = nrx;
				next.ry = nry;
				next.bx = nbx;
				next.by = nby;
				next.dist = current.dist + 1;

				q.push(next);
				visited[nrx][nry][nbx][nby] = true;
			}
		}
	}
	return answer;
}

int main()
{
	Ball ball;
	int n, m;
	cin >> n >> m;

	vector<vector<char>> board(n, vector<char>(m));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> board[i][j];

			if (board[i][j] == 'R')
			{
				ball.rx = i;
				ball.ry = j;
			}

			if (board[i][j] == 'B')
			{
				ball.bx = i;
				ball.by = j;
			}
		}
		ball.dist = 0;
	}

	int answer = bfs(board, ball);
	cout << answer << "\n";
}