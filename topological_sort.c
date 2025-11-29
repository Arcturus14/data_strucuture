#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 256

//==================================================
// 그래프 관련 자료구조 및 함수들
typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
    int n;  // 정점의 개수
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

void init_graph(GraphType* g) {
    g->n = 0;
    for (int v = 0; v < MAX_VERTICES; v++)
        g->adj_list[v] = NULL;
}

void insert_edge(GraphType* g, int from, int to) {
    GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = to;
    node->link = g->adj_list[from];
    g->adj_list[from] = node;
}

void free_graph(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        GraphNode* node = g->adj_list[i];
        while (node != NULL) {
            GraphNode* temp = node;
            node = node->link;
            free(temp);
        }
    }
}

void load_graph(GraphType* g) {
    int edge_count;
    scanf("%d %d", &g->n, &edge_count);

    for (int i = 0; i < edge_count; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        insert_edge(g, from, to);
    }
}
// 그래프 관련 함수들 끝
//==================================================

//==================================================
// 스택 관련 자료구조 및 함수들
#define MAX_STACK_SIZE 100
typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} StackType;

void init_stack(StackType* s) { s->top = -1; }

int is_empty_stack(StackType* s) { return (s->top == -1); }

int is_full_stack(StackType* s) { return (s->top == (MAX_STACK_SIZE - 1)); }

void push(StackType* s, int item) {
    if (is_full_stack(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    s->data[++(s->top)] = item;
}

int pop(StackType* s) {
    if (is_empty_stack(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    return s->data[(s->top)--];
}
// 스택 관련 함수들 끝
//==================================================

//==================================================
// 위상 정렬 관련 함수들
void topo_sort(GraphType* g) {
    StackType s;
    init_stack(&s);

    // 1. 모든 정점의 진입 차수 계산
    int* in_degree = (int*)malloc(g->n * sizeof(int));
    for (int i = 0; i < g->n; i++)
        in_degree[i] = 0;

    // TODO: 각 정점의 진입 차수 계산
    // 모든 정점의 인접 리스트를 순회하며 진입 차수를 증가시킨다
    for (int i = 0; i < g->n; i++) {
        GraphNode* node = g->adj_list[i];
        while (node != NULL) {
            in_degree[node->vertex]++;
            node = node->link;
        }
    }

    // 2. 진입 차수가 0인 정점을 스택에 삽입
    // TODO: 진입 차수가 0인 정점을 스택에 push
    for (int i = 0; i < g->n; i++)
        if (in_degree[i] == 0)
            push(&s, i);

    // 3. 위상 순서 생성
    while (!is_empty_stack(&s)) {
        int w = pop(&s);
        printf("%2d ", w);

        // TODO: 출력한 정점과 연결된 간선 제거 및 진입 차수 갱신
        GraphNode* node = g->adj_list[w];
        while (node != NULL) {
            int u = node->vertex;
            in_degree[u]--; // 진입 차수 감소
            if (in_degree[u] == 0) {
                push(&s, u); // 진입 차수가 0이 되면 스택에 추가
            }
            node = node->link;
        }
        // 스택에 남은 원소가 있다면 화살표 출력
        if (!is_empty_stack(&s)) printf("->");
    }
    printf("\n");
    free(in_degree);
}
// 위상 정렬 관련 함수들 끝
//==================================================

int main() {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));

    init_graph(g);
    load_graph(g);

    topo_sort(g);

    free_graph(g);
    free(g);

    return 0;
}