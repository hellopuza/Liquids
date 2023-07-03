#include <iostream>
#include <vector>

#include "Graph.h"
#include "Liquids.h"

struct Tube
{
    Tube() = default;

    void init()
    {
        content.clear();
        for (int i = 0; i < TUBE_CAPACITY; i++)
        {
            #ifdef NUMBERS
            int id = 0;
            std::cin >> id;
            content.push_back(id);
            #else
            std::string word;
            std::cin >> word;
            content.push_back(getLiquidId(word));
            #endif
        }
    }

    bool operator==(const Tube& obj) const
    {
        return content == obj.content;
    }

    void transfuse(Tube& dest)
    {
        int top = content.back();

        while ((dest.content.size() < TUBE_CAPACITY) && (content.size() > 0) && (content.back() == top))
        {
            dest.content.push_back(content.back());
            content.pop_back();
        }
    }

    bool transfusable(const Tube& dest) const
    {
        return !content.empty() && (
            dest.content.empty() && !isPlain() ||
            !dest.content.empty() && (dest.content.size() < TUBE_CAPACITY) && (dest.content.back() == content.back())
        );
    }

    bool isPlain() const
    {
        for (const auto& part : content)
        {
            if (part != content.front())
            {
                return false;
            }
        }
        return true;
    }

    bool isDone() const
    {
        return content.empty() || (content.size() == TUBE_CAPACITY) && isPlain();
    }

    std::vector<int> content;
};

using IntPair = std::pair<int, int>;
using IntPairs = std::vector<IntPair>;

struct TubeSet
{
    TubeSet() = default;
    TubeSet(int K) : tubes(K + ADD_NUMBER) {}
    TubeSet(const TubeSet& set, IntPair trans) : tubes(set.tubes)
    {
        tubes[trans.first].transfuse(tubes[trans.second]);
    }

    void init()
    {
        for (int i = 0; i < tubes.size() - ADD_NUMBER; i++)
        {
            tubes[i].init();
        }
    }

    bool operator==(const TubeSet& obj) const
    {
        return tubes == obj.tubes;
    }

    void findSuitableTubes(IntPairs& pairs)
    {
        for (int i = 0; i < tubes.size(); i++)
        {
            for (int j = 0; j < tubes.size(); j++)
            {
                if ((i != j) && (tubes[i].transfusable(tubes[j])))
                {
                    pairs.push_back(std::make_pair(i, j));
                }
            }
        }
    }

    bool isDone() const
    {
        for (const auto& tube : tubes)
        {
            if (!tube.isDone())
            {
                return false;
            }
        }
        return true;
    }

    void print()
    {
        size_t i = 0;
        for (const auto& tube : tubes)
        {
            std::cout << "(" << i++ << ") ";
            for (const auto& part : tube.content)
            {
                std::cout << part << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    static const int ADD_NUMBER = 2;
    std::vector<Tube> tubes;
};

struct TubeSolver
{
    TubeSolver(const TubeSet& tube_set)
    {
        graph.nodes.emplace_back(tube_set);
    }

    bool solve(std::vector<Edge<IntPair>>& path)
    {
        std::unordered_map<size_t, Edge<IntPair>> parents;
        std::unordered_set<size_t> checked;
        std::vector<size_t> unchecked;
        unchecked.push_back(0);

        size_t found_ind = -1;
        while (!unchecked.empty())
        {
            size_t ind = unchecked.back();
            unchecked.pop_back();
            checked.insert(ind);

            if (graph.nodes[ind].data.isDone())
            {
                found_ind = ind;
                break;
            }
            appendNodes(ind);

            for (auto& edge : graph.nodes[ind].edges)
            {
                if (!checked.contains(edge.node_ind))
                {
                    unchecked.push_back(edge.node_ind);
                    parents[edge.node_ind] = Edge(edge.data, ind);
                }
            }
        }

        if (found_ind == -1)
        {
            return false;
        }

        size_t ind = found_ind;
        while (ind != 0)
        {
            path.push_back(Edge(parents[ind].data, ind));
            ind = parents[ind].node_ind;
        }

        return true;
    }

    void appendNodes(size_t ind)
    {
        IntPairs pairs;
        graph.nodes[ind].data.findSuitableTubes(pairs);

        for (const auto& pair : pairs)
        {
            TubeSet tube_set = TubeSet(graph.nodes[ind].data, pair);

            size_t existing_ind = graph.find(tube_set);
            if (existing_ind != -1)
            {
                graph.nodes[ind].edges.emplace_back(pair, existing_ind);
            }
            else
            {
                size_t new_ind = graph.append(tube_set);
                graph.nodes[ind].edges.emplace_back(pair, new_ind);
            }
        }
    }

    Graph<TubeSet, IntPair> graph;
};

int main()
{
    int K = 0;
    std::cin >> K;

    TubeSet tube_set(K);
    tube_set.init();

    TubeSolver solver(tube_set);
    std::vector<Edge<IntPair>> path;

    if (solver.solve(path))
    {
        for (auto it = path.rbegin(); it != path.rend(); it++)
        {
            std::cout << it->data.first << " -> " << it->data.second << '\n';

            #ifdef SHOW_TUBES
            solver.graph.nodes[it->node_ind].data.print();
            #endif
        }
    }
    else
    {
        std::cout << "Impossible";
    }

    return 0;
}