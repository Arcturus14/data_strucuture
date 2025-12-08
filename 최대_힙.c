#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_HEAP_SIZE 10000

typedef struct {
    int key;
} HeapElement;

typedef struct {
    HeapElement elements[MAX_HEAP_SIZE];
    int size;
} Heap;  // 최대 힙

// 초기화 함수
void init_heap(Heap* heap) { heap->size = 0; }

// 삽입 함수
void insert_heap(Heap* heap, HeapElement item) {
    int current = ++(heap->size);
    //  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
    while (current > 1 && item.key > heap->elements[current / 2].key) {
        // 추가한 위치에 부모 노드 내리기
        heap->elements[current] = heap->elements[current / 2];
        current /= 2;    // 추가한 노드 커서 올리기
        /*** Fill the code ***/
    }
    heap->elements[current] = item;  // 새로운 위치에 저장
}

// 최대 힙의 최대 원소를 삭제하는 함수
HeapElement delete_heap(Heap* heap) {
    int parent, child;
    HeapElement item, temp;

    item = heap->elements[1];    // 삭제할 노드
    temp = heap->elements[(heap->size)--];    // 위로 올릴 노드 (마지막노드)

    parent = 1;
    child = 2;

    while (child <= heap->size) {
        /*** Fill the code ***/
        if ((child < heap->size) &&
            (heap->elements[child].key < heap->elements[child + 1].key))
            child++;    // 비교 대상을 오른쪽 자식으로 변경
        if (temp.key >= heap->elements[child].key)
            break;  // temp가 child보다 크면 break
        heap->elements[parent] = heap->elements[child];
        // 부모 노드를 자식 노드로 덮어쓴다

        parent = child; // 방금 올린 자식이 새로운 부모가 됨
        child *= 2;     // 그 부모의 왼쪽 자식으로 자식 인덱스 이동
    }
    /*** Fill the code ***/
    heap->elements[parent] = temp;
    return item;
}

void print_heap(Heap* heap) {
    int i, level;
    for (i = 1, level = 2; i <= heap->size; i++) {
        if (i == level) {
            printf("\n");
            level *= 2;
        }
        printf("%d ", heap->elements[i].key);
    }
    printf("\n");
}

int main() {
    char c[16];
    int T;
    int key;
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    HeapElement e;

    init_heap(heap);

    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        scanf("%s", c);
        if (strcmp(c, "insert_heap") == 0) {
            scanf("%d", &key);
            e.key = key;
            insert_heap(heap, e);
        }
        else if (strcmp(c, "delete_heap") == 0) {
            printf("%d\n", delete_heap(heap).key);
        }
        else if (strcmp(c, "print_heap") == 0) {
            print_heap(heap);
        }
    }

    free(heap);
    return 0;
}

