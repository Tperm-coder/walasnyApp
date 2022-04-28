#include "Path.h"
#include <bits/stdc++.h>
using namespace std;

Path* Dijkstra(Node *from, Node *to) {
    vector<Node*> parent(N);
    vector<int> cost(N, INF);
    priority_queue<pair<int, Node*>> pq;

    cost[from->id] = 0;
    parent[from->id] = NULL;
    pq.emplace(0, from);

    while(pq.size())
    {
        auto curNode = pq.top();
        int curNodeCost = -curNode.first;
        int curNodeId = curNode.second->id;

        set<pair<Node*, int>>::iterator nextNode;

        pq.pop();

        if (curNodeCost > cost[curNodeId])
            continue;

        for(nextNode = curNode.second->links.begin(); nextNode != curNode.second->links.end(); nextNode++)
        {
            int nextNodeId = nextNode->first->id;
            int nextNodeCost = nextNode->second + curNodeCost;

            if(nextNodeCost < cost[nextNodeId])
            {
                cost[nextNodeId] = nextNodeCost;
                parent[nextNodeId] = curNode.second;
                pq.emplace(-cost[nextNodeId], nextNode->first);
            }
        }
    }

    vector<Node*> path;
    Node *curNode = to;
    while (parent[curNode->id] != NULL) {
        path.push_back(curNode);
        curNode = parent[curNode->id];
    }
    path.push_back(from);
    reverse(path.begin(), path.end());

    if (cost[to->id] == INF)
        cost[to->id] = -1;

    return new Path(from, to, path, cost[to->id]);
}

