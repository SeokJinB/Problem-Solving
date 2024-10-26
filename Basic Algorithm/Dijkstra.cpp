#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

// ���ͽ�Ʈ�� �˰���
vector<int> dijkstra(int start, int N, const vector<vector<pair<int, int>>>& graph)
{
    vector<int> distances(N + 1, INF);
    distances[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, start); // (����ġ, ����)

    while (!pq.empty())
    {
        pair<int, int> current = pq.top(); // pair�� ���� ������ ����ġ�� ������
        pq.pop();

        int currentW = current.first; // ���� ����ġ
        int currentV = current.second; // ���� ����

        // ���� ���� ��ΰ� ���� �Ÿ����� ũ�� ����
        if (distances[currentV] < currentW)
        {
            continue;
        }

        // ���� ������ Ž��
        for (const pair<int, int>& edge : graph[currentV])
        {
            int nextW = edge.first; // ���� ����ġ
            int nextV = edge.second; // ���� ����
            int cost = currentW + nextW;

            // �� ª�� ��ΰ� �߰ߵǸ� ������Ʈ
            if (cost < distances[nextV])
            {
                distances[nextV] = cost;
                pq.emplace(cost, nextV);
            }
        }
    }

    return distances; // �ִ� �Ÿ� �迭 ��ȯ
}

int main()
{
    int N, M;
    cin >> N >> M;

    // ���� ����Ʈ�� ����Ͽ� �׷��� ǥ��
    vector<vector<pair<int, int>>> graph(N + 1);

    // �׷��� ���� �Է�
    for (int i = 0; i < M; i++)
    {
        int s, e, w;
        cin >> s >> e >> w;
        graph[s].emplace_back(w, e); // (���, ����)
    }

    // �����, ������
    int start, end;
    cin >> start >> end;

    vector<int> distances = dijkstra(start, N, graph);

    // ����� ������������ �ּ� ��� ���
    cout << distances[end] << endl;

    return 0;
}
