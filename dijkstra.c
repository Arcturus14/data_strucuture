// 다익스트라 알고리즘 구현
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 256
#define INF 9999

typedef struct GraphType {
    int n;                                    // 정점의 개수
    char vertex_label[MAX_VERTICES];          // 정점의 이름
    int adj_mat[MAX_VERTICES][MAX_VERTICES];  // 인접 행렬
} GraphType;

//==================================================
// 그래프 관련 함수들
int is_empty(GraphType* g) { return (g->n == 0); }
int is_full(GraphType* g) { return (g->n >= MAX_VERTICES); }

void init_graph(GraphType* g) {
    g->n = 0;

    for (int i = 0; i < MAX_VERTICES; i++)
        g->vertex_label[i] = '\0';

    for (int i = 0; i < MAX_VERTICES; i++)
        for (int j = 0; j < MAX_VERTICES; j++)
            g->adj_mat[i][j] = 0;
}

void insert_vertex(GraphType* g, char v_label) {
    if (is_full(g)) return;

    g->vertex_label[g->n] = v_label;
    g->n++;
}

void insert_edge(GraphType* g, int from, int to, int weight) {
    g->adj_mat[from][to] = weight;
}

void load_wgraph(GraphType* g) {
    int n;
    scanf("%d", &n);

    char v_label;
    int curr_v, to_v, weight;
    for (curr_v = 0; curr_v < n; curr_v++) {
        scanf(" %c", &v_label);
        insert_vertex(g, v_label);

        // 각 정점에 대한 가중치 정보 입력
        for (to_v = 0; to_v < n; to_v++) {
            scanf("%d", &weight);

            // 자기 자신이 아니고 weight가 0이면 INF로 설정
            if (curr_v != to_v && weight == 0)
                g->adj_mat[curr_v][to_v] = INF;
            else
                g->adj_mat[curr_v][to_v] = weight;
        }
    }
}
// 그래프 관련 함수들 끝
//==================================================

//==================================================
// Dijkstra 최단경로 관련 함수들
int path[MAX_VERTICES];
int dist[MAX_VERTICES];
int found[MAX_VERTICES];

void print_step(GraphType* g, int step) {
    printf(" Step%2d:", step);
    for (int i = 0; i < g->n; i++) {
        if (dist[i] == INF)
            printf("  INF");
        else
            printf("%5d", dist[i]);
    }
    printf("\n");
}

void print_shortest_path(GraphType* g, int start, int end) {
    printf("[Shortest Path: %c---%c] %c", g->vertex_label[end],
        g->vertex_label[start], g->vertex_label[end]);

    while (path[end] != start) {
        printf("-%c", g->vertex_label[path[end]]);
        end = path[end];
    }
    printf("-%c\n", g->vertex_label[path[end]]);
}

int choose_vertex(GraphType* g) {
    int min = INF;
    int minpos = -1;

    for (int i = 0; i < g->n; i++) {
        if (dist[i] < min && !found[i]) {
            min = dist[i];
            minpos = i;
        }
    }
    return minpos;
}

// Dijkstra의 최단경로
void shortest_path_dijkstra(GraphType* g, int start) {
    // 초기화
    for (int i = 0; i < g->n; i++) {
        dist[i] = g->adj_mat[start][i]; // start에서 i로 바로 가는 거리
        found[i] = 0;       // 최단 거리 확정 여부
        path[i] = start;    // i로 가기 직전의 경로
    }
    found[start] = 1;
    dist[start] = 0;

    // 정점 개수만큼 반복
    for (int i = 0; i < g->n - 1; i++) {
        int u = choose_vertex(g);   // 확정되지 않은 정점 중 최소 거리 정점을 찾음
        print_step(g, i);
        found[u] = 1;   // 찾은 정점은 경로 확정(최단거리 확정)

        // u를 거쳐서 갈 수 있는 w 거리 갱신
        for (int w = 0; w < g->n; w++)
            if (!found[w])
                if (dist[w] > g->adj_mat[u][w] + dist[u]) {
                    dist[w] = g->adj_mat[u][w] + dist[u];
                    path[w] = u;
                }
    }
}
// Dijkstra 최단경로 관련 함수들 끝
//==================================================

int main() {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));

    init_graph(g);
    load_wgraph(g);

    shortest_path_dijkstra(g, 0);

    for (int i = 1; i < g->n; i++) {
        print_shortest_path(g, 0, i);
    }

    free(g);
    return 0;
}
