#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model)
{
    // scale the floats to percentages
    start_x *= 0.01f;
    start_y *= 0.01f;
    end_x *= 0.01f;
    end_y *= 0.01f;

    // find the closest nodes to (start_x, start_y)
    start_node = &m_Model.FindClosestNode(start_x, start_y);

    // find the closest nodes to (end_x, end_y)
    end_node = &m_Model.FindClosestNode(end_x, end_y);
}

// this method iterates from the end node to start node and returns the path
// in reverse order. The rendering code expects the path to be in reverse order
std::vector<RouteModel::Node> RoutePlaner::ConstructFinalPath(RouteModel::Node *current_node)
{
    std::vector<RouteModel::Node> path_found{};
    distance = 0.0f;
    RouteModel::Node parent_node;

    while (current_node->parent != nullptr) {
        path_found.push_back(*current_node);
        parent_node = *(current_node->parent);
        distance += current_node->distance(parent_node);
        current_node = current_node->parent;
    }
    path_found.push_back(*current_node);
    distance *= m_Model.MetricScale();
    return path_found;
}
