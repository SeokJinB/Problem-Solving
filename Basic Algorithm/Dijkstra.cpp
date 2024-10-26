#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

// 다익스트라 알고리즘
vector<int> dijkstra(int start, int N, const vector<vector<pair<int, int>>>& graph)
{
    vector<int> distances(N + 1, INF);
    distances[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, start); // (가중치, 정점)

    while (!pq.empty())
    {
        pair<int, int> current = pq.top(); // pair로 현재 정점과 가중치를 가져옴
        pq.pop();

        int currentW = current.first; // 현재 가중치
        int currentV = current.second; // 현재 정점

        // 현재 꺼낸 경로가 기존 거리보다 크면 무시
        if (distances[currentV] < currentW)
        {
            continue;
        }

        // 인접 정점들 탐색
        for (const pair<int, int>& edge : graph[currentV])
        {
            int nextW = edge.first; // 다음 가중치
            int nextV = edge.second; // 다음 정점
            int cost = currentW + nextW;

            // 더 짧은 경로가 발견되면 업데이트
            if (cost < distances[nextV])
            {
                distances[nextV] = cost;
                pq.emplace(cost, nextV);
            }
        }
    }

    return distances; // 최단 거리 배열 반환
}

int main()
{
    int N, M;
    cin >> N >> M;

    // 인접 리스트를 사용하여 그래프 표현
    vector<vector<pair<int, int>>> graph(N + 1);

    // 그래프 정보 입력
    for (int i = 0; i < M; i++)
    {
        int s, e, w;
        cin >> s >> e >> w;
        graph[s].emplace_back(w, e); // (비용, 도착)
    }

    // 출발점, 도착점
    int start, end;
    cin >> start >> end;

    vector<int> distances = dijkstra(start, N, graph);

    // 출발점 도착점까지의 최소 비용 출력
    cout << distances[end] << endl;

    return 0;
}
