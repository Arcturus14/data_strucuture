// Prim의 MST 알고리즘
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000000L

typedef struct GraphType {
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

// 그래프 초기화
void graph_init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++)
		for (int j = 0; j < MAX_VERTICES; j++) {
			// 같은 노드 간의 가중치는 0
			if (i == j) g->weight[i][j] = 0;
			// 다른 노드 간에는 INF로 설정
			else g->weight[i][j] = INF;
		}
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->weight[start][end] = w;
	g->weight[end][start] = w;
}

void load_wgraph(GraphType* g)
{
	int i, j, k, val, n;
	// 정점 개수 설정 부분 주의 (문제 입력 순서: 간선수 n, 정점수 g->n)
	scanf("%d %d", &n, &(g->n));
	for (k = 0; k < n; k++) {
		scanf("%d %d %d", &i, &j, &val);
		insert_edge(g, i, j, val);
	}
}

// 진행 단계별 상황출력
void print_step(int step, int vertex)
{
	printf("Step%2d:", step);
	printf("(%d) %d\n", vertex, distance[vertex]);
}

// 최소 dist[v] 값을 갖는 정점을 반환
int get_min_vertex(int n)
{
	/*** Fill the code START ***/
	int v, i;
	// 아직 선택되지 않은 정점 중 가장 작은 distance 값을 가진 정점을 찾습니다.
	// 초기값 설정: 유효한 정점을 찾을 때까지 반복
	v = -1;
	for (i = 0; i < n; i++) {
		if (!selected[i]) {
			// v가 -1이거나(아직 후보 없음), 더 작은 거리를 발견했을 때 갱신
			// 거리 갱신이 되지 않아 INF인 노드는 selected와 연결될 수 없다
			if (v == -1 || distance[i] < distance[v]) {
				v = i;
			}
		}
	}
	return v;
	/*** Fill the code END ***/
}
void prim(GraphType* g, int s)
{
	int i, u, v;

	// 초기화
	for (u = 0; u < g->n; u++) {
		distance[u] = INF;
		selected[u] = FALSE;
	}
	distance[s] = 0;    // 시작점 거리는 0

	/*** Fill the code START ***/
	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n);   // 방문하지 않은 정점 중 최소 거리(distance)를 가진 정점 u 선택

		if (u == -1 || distance[u] == INF) return;  // 만약 연결된 정점이 없다면 종료 (그래프가 끊겨있는 경우 예외처리)

		// 정점 u를 집합에 포함시킴
		selected[u] = TRUE;
		print_step(i, u);

		// 거리 갱신
		for (v = 0; v < g->n; v++)
			if (!selected[v] && g->weight[u][v] < distance[v])
				distance[v] = g->weight[u][v];
	}
}

int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	load_wgraph(g);

	prim(g, 0);
	free(g);

	return 0;
}