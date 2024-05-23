#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <fstream>
#include <unordered_set>
using namespace std;

class GraphNode {
public:
    string name;
    vector<GraphNode*> parents;
    vector<GraphNode*> children;

    GraphNode(string name) {
        this->name = name;
    }
};

class GraphTree {
private:
    unordered_map<string, GraphNode*> nodes;

    GraphNode* findCommonAncestor(GraphNode* node1, GraphNode* node2) {
        unordered_set<GraphNode*> ancestors;

        // Collect all ancestors of node1
        while (node1 != nullptr) {
            ancestors.insert(node1);
            if (node1->parents.empty()) break;
            node1 = node1->parents[0]; // Assume single parent for simplicity
        }

        // Find the first common ancestor in node2's lineage
        while (node2 != nullptr) {
            if (ancestors.find(node2) != ancestors.end()) {
                return node2;
            }
            if (node2->parents.empty()) break;
            node2 = node2->parents[0]; // Assume single parent for simplicity
        }

        return nullptr;
    }

    int findDistance(GraphNode* node, GraphNode* target) {
        int distance = 0;
        while (node != nullptr && node != target) {
            distance++;
            if (node->parents.empty()) break;
            node = node->parents[0]; // Assume single parent for simplicity
        }
        return distance;
    }

public:
    void addNode(string name) {
        if (nodes.find(name) == nodes.end()) {
            nodes[name] = new GraphNode(name);
        }
    }

    void addEdge(string parentName, string childName) {

        GraphNode* parent = nodes[parentName];
        GraphNode* child = nodes[childName];

        parent->children.push_back(child);
        child->parents.push_back(parent);
    }

    vector<GraphNode*> getParents(string name) {
        if (nodes.find(name) == nodes.end()) {
            return {};
        }
        return nodes[name]->parents;
    }

    vector<GraphNode*> getChildren(string name) {
        if (nodes.find(name) == nodes.end()) {
            return {};
        }
        return nodes[name]->children;
    }

    string findRelation(string name1, string name2) {
        if (nodes.find(name1) == nodes.end() || nodes.find(name2) == nodes.end()) {
            return "no relation";
        }

        GraphNode* node1 = nodes[name1];
        GraphNode* node2 = nodes[name2];

        // Check sibling relationship
        for (GraphNode* parent : node1->parents) {
            for (GraphNode* sibling : parent->children) {
                if (sibling == node2) {
                    return "sibling";
                }
            }
        }

        // Check cousin relationship
        GraphNode* commonAncestor = findCommonAncestor(node1, node2);
        if (commonAncestor != nullptr) {
            int distance1 = findDistance(node1, commonAncestor);
            int distance2 = findDistance(node2, commonAncestor);

            if (distance1 == 0)
            {
                if (distance2 == 1)
                {
                    return "parent";
                }
                else
                {
                    string great = "";
                    for (int i = 0; i < distance2 - 2; i++)
                    {
                        great += "great ";
                    }
                    return great + "grand parent";
                }
            }
            else if (distance2 == 0)
            {
                if (distance1 == 1)
                {
                    return "child";
                }
                else
                {
                    string great = "";
                    for (int i = 0; i < distance1 - 2; i++)
                    {
                        great += "great ";
                    }
                    return great + "grand child";
                }
            }

            int k = min(distance1 - 1, distance2 - 1);
            int removed = abs(distance1 - distance2);

            if (removed == 0)
                return to_string(k) + " cousin";

            return to_string(k) + " cousin removed " + to_string(removed);
        }

        return "no relation";
    }

    void printTree() {
        for (const auto& pair : nodes) {
            cout << "Node " << pair.first << ": ";
            cout << "Parents [";
            for (GraphNode* parent : pair.second->parents) {
                cout << parent->name << " ";
            }
            cout << "] Children [";
            for (GraphNode* child : pair.second->children) {
                cout << child->name << " ";
            }
            cout << "]" << endl;
        }
    }
};

int main()
{
    ifstream ifp("tree.inp");
    ofstream ofp("tree.out");

    GraphTree tree;

    string child, parent;
    unordered_set<string> family;
    vector<pair<string, string>> pair;

    while (true)
    {
        ifp >> child >> parent;

        if (child == "no.child")
            break;

        family.insert(child);
        family.insert(parent);
        pair.emplace_back(make_pair(child, parent));
    }

    for (const auto& n : family)
    {
        tree.addNode(n);
    }

    for (const auto& p : pair)
    {
        tree.addEdge(p.second, p.first);
    }

    string name1, name2;

    while (ifp >> name1 >> name2)
    {
        ofp << tree.findRelation(name1, name2) << endl;
    }

    //tree.printTree();

    ifp.close();
    ofp.close();

    return 0;
}
