// kruskal의 MST 알고리즘
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000000000

int parent[MAX_VERTICES];       // 부모 노드
int node_n;                     // 정점의 갯수

struct Edge {           // 간선을 나타내는 구조체
    int start, end, weight;
};

typedef struct GraphType {
    int n;  // 간선의 개수
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

// 초기화
void set_init(int n)
{   //fill the code
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }
}

// curr가 속하는 집합을 반환한다.
int set_find(int curr) // fill the code
{
    if (parent[curr] == -1)
        return curr;
    while (parent[curr] != -1)    curr = parent[curr];
    return curr;
}

// 두개의 원소가 속한 집합을 합친다.
void set_union(int a, int b) // fill the code
{
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2) {
        parent[root1] = root2;
    }
}

// 그래프 초기화
void graph_init(GraphType* g)
{
    g->n = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w)
{
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;
}

// qsort()에 사용되는 함수
int compare(const void* a, const void* b)
{
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);
}

void print_step(int step, struct Edge* e)
{
    printf("Step%2d:", step);
    printf("(%d,%d) %d\n", e->start, e->end, e->weight);
}

// kruskal의 최소 비용 신장 트리 프로그램
void kruskal(GraphType* g)
{
    int edge_accepted = 0;  // 현재까지 선택된 간선의 수
    int uset, vset;         // 정점v, u의 집합 번호
    struct Edge* e;

    set_init(g->n);

    // 간선 정렬
    qsort(g->edges, g->n, sizeof(struct Edge), compare);

    for (int i = 0; i < g->n; i++) {
        // 간선이 n-1개가 되어 신장트리 조건 만족 시 끝
        if (edge_accepted >= node_n - 1) break;

        e = &g->edges[i];

        uset = set_find(e->start);
        vset = set_find(e->end);

        // 같은 집합이 아니면(사이클이 안 생기면) 두 집합 합친다
        if (uset != vset) {
            print_step(edge_accepted, e);
            set_union(uset, vset);
            edge_accepted++;
        }
    }
}

void load_wgraph(GraphType* g)
{
    int i, j, k, val, n;

    // 첫 줄 입력: 간선 수(n), 정점 수(node_n)
    scanf("%d %d", &n, &node_n);

    // 간선 정보 입력
    for (k = 0; k < n; k++) {
        scanf("%d %d %d", &i, &j, &val);
        insert_edge(g, i, j, val);
    }
}

int main()
{
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    load_wgraph(g);

    kruskal(g);

    free(g);
    return 0;
}