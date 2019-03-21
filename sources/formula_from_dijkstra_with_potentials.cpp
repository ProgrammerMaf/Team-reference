new_dist = dist[v] + edges[ind].cost + p[v] - p[u];
for (int i = 0; i < size; i++) p[i] += dist[i];