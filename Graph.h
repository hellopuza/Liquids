#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

template<typename Te>
struct Edge
{
    Edge() = default;
    Edge(const Te& value, size_t ind);

    Te data;
    size_t node_ind;
};

template<typename Tn, typename Te>
struct Node
{
    Node() = default;
    explicit Node(const Tn& value);

    Tn data;
    std::vector<Edge<Te>> edges;
};

template<typename Tn, typename Te>
struct Graph
{
    Graph() = default;

    size_t append(const Tn& value);
    size_t find(const Tn& value);

    std::vector<Node<Tn, Te>> nodes;
};

template<typename Te>
Edge<Te>::Edge(const Te& value, size_t ind) : data(value), node_ind(ind) {}

template<typename Tn, typename Te>
Node<Tn, Te>::Node(const Tn& value) : data(value) {}

template<typename Tn, typename Te>
size_t Graph<Tn, Te>::append(const Tn& value)
{
    nodes.emplace_back(value);
    return nodes.size() - 1;
}

template<typename Tn, typename Te>
size_t Graph<Tn, Te>::find(const Tn& value)
{
    for (size_t i = 0; i < nodes.size(); i++)
    {
        if (nodes[i].data == value)
        {
            return i;
        }
    }

    return -1;
}

#endif // GRAPH_H