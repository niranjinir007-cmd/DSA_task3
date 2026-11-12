/* Student Record Search using Binary Search Tree (BST)
   Compile: gcc bst_student.c -o bst
   Run    : ./bst                                              */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"

typedef struct Node {
    Student data;
    struct Node *left, *right;
} Node;

Node *create_node(Student s) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = s;
    n->left = n->right = NULL;
    return n;
}

Student make_student(int i) {
    Student s;
    s.reg_no = KEYS[i];
    strcpy(s.name, NAMES[i]);
    strcpy(s.dept, DEPTS[i % 5]);
    return s;
}

/* ---------- Insertion (comps = number of comparisons) ---------- */
Node *insert(Node *root, Student s, int *comps) {
    *comps = 0;
    Node *n = create_node(s);
    if (root == NULL) return n;

    Node *cur = root;
    while (1) {
        (*comps)++;
        if (s.reg_no == cur->data.reg_no) {
            printf("Duplicate key %d ignored\n", s.reg_no);
            free(n);
            return root;
        }
        if (s.reg_no < cur->data.reg_no) {
            if (cur->left == NULL) { cur->left = n; break; }
            cur = cur->left;
        } else {
            if (cur->right == NULL) { cur->right = n; break; }
            cur = cur->right;
        }
    }
    return root;
}

/* ---------- Searching ---------- */
Node *search(Node *root, int key, int *comps, int path[], int *plen) {
    Node *cur = root;
    *comps = 0;
    *plen = 0;
    while (cur != NULL) {
        (*comps)++;
        path[(*plen)++] = cur->data.reg_no;
        if (key == cur->data.reg_no) return cur;
        cur = (key < cur->data.reg_no) ? cur->left : cur->right;
    }
    return NULL;
}

/* ---------- Height (levels; empty tree = 0) ---------- */
int height(Node *root) {
    if (root == NULL) return 0;
    int l = height(root->left), r = height(root->right);
    return 1 + (l > r ? l : r);
}

/* ---------- Traversals ---------- */
void inorder(Node *r)   { if (r) { inorder(r->left);  printf("%d ", r->data.reg_no); inorder(r->right); } }
void preorder(Node *r)  { if (r) { printf("%d ", r->data.reg_no); preorder(r->left); preorder(r->right); } }
void postorder(Node *r) { if (r) { postorder(r->left); postorder(r->right); printf("%d ", r->data.reg_no); } }

int main(void) {
    Node *root = NULL;
    int comps, plen, path[64];
    int total_ins = 0, i;

    printf("============================================================\n");
    printf(" STUDENT RECORD SEARCH - BINARY SEARCH TREE (BST)\n");
    printf("============================================================\n");

    for (i = 0; i < N; i++) {
        root = insert(root, make_student(i), &comps);
        total_ins += comps;
    }
    printf("Inserted %d records\n", N);
    printf("Total comparisons during insertion : %d\n", total_ins);
    printf("Tree height (levels)               : %d\n", height(root));

    printf("\n--- Traversals (Register Numbers) ---\n");
    printf("Inorder (sorted): "); inorder(root);   printf("\n");
    printf("Preorder        : "); preorder(root);  printf("\n");
    printf("Postorder       : "); postorder(root); printf("\n");

    printf("\n--- Successful Search (all %d keys) ---\n", N);
    int sum = 0, max = 0, min = 1000;
    for (i = 0; i < N; i++) {
        search(root, KEYS[i], &comps, path, &plen);
        sum += comps;
        if (comps > max) max = comps;
        if (comps < min) min = comps;
    }
    printf("Average comparisons : %.2f\n", (double)sum / N);
    printf("Maximum comparisons : %d\n", max);
    printf("Minimum comparisons : %d\n", min);

    printf("\n--- Unsuccessful Search ---\n");
    sum = 0;
    for (i = 0; i < N_UNSUCC; i++) {
        Node *r = search(root, UNSUCC_KEYS[i], &comps, path, &plen);
        sum += comps;
        printf("Key %d: %s | comparisons = %d | path = ", UNSUCC_KEYS[i],
               r ? "FOUND" : "NOT FOUND", comps);
        for (int j = 0; j < plen; j++) printf("%d ", path[j]);
        printf("\n");
    }
    printf("Average comparisons : %.2f\n", (double)sum / N_UNSUCC);

    printf("\n--- Insertion of a new record ---\n");
    Student ns = {NEW_KEY, "Viva Student", "CSE"};
    root = insert(root, ns, &comps);
    printf("Inserted %d with %d comparisons. New height = %d\n", NEW_KEY, comps, height(root));

    printf("\n--- Viva demo: search any key ---\n");
    int key;
    printf("Enter Register Number to search (0 to skip): ");
    if (scanf("%d", &key) == 1 && key != 0) {
        Node *r = search(root, key, &comps, path, &plen);
        printf("Path followed: ");
        for (i = 0; i < plen; i++) printf("%d ", path[i]);
        if (r) printf("\nFOUND: %d | %s | %s | comparisons = %d\n", r->data.reg_no, r->data.name, r->data.dept, comps);
        else   printf("\nNOT FOUND | comparisons = %d\n", comps);
    }
    return 0;
}
