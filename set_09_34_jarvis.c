#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct {
    int x, y;
} Point;

Point p0; // global pivot for sorting

// Utility: swap two points
void swap(Point *a, Point *b) {
    Point t = *a;
    *a = *b;
    *b = t;
}

// Square of distance between two points
int distSq(const Point *a, const Point *b) {
    int dx = a->x - b->x;
    int dy = a->y - b->y;
    return dx*dx + dy*dy;
}

// Orientation of ordered triplet (a, b, c).
// returns 0 -> collinear, 1 -> clockwise, 2 -> counterclockwise
int orientation(const Point *a, const Point *b, const Point *c) {
    long long val = (long long)(b->y - a->y) * (c->x - b->x)
                  - (long long)(b->x - a->x) * (c->y - b->y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// Compare function for qsort: sort by polar angle with p0,
// if same angle, the closer point comes first.
int compare(const void *vp1, const void *vp2) {
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    int o = orientation(&p0, p1, p2);
    if (o == 0) {
        // collinear: keep the closer one first
        int d1 = distSq(&p0, p1);
        int d2 = distSq(&p0, p2);
        return (d1 < d2) ? -1 : (d1 > d2);
    }
    return (o == 2) ? -1 : 1; // p1 before p2 if counterclockwise
}

// Return index of the bottom-most (and leftmost if tie) point
int bottomMost(Point pts[], int n) {
    int ymin = pts[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        if (pts[i].y < ymin || (pts[i].y == ymin && pts[i].x < pts[min].x)) {
            ymin = pts[i].y;
            min = i;
        }
    }
    return min;
}

// Graham scan: compute convex hull and print it.
// Points in pts[0..n-1]. Assumes n >= 0.
void convexHull(Point pts[], int n) {
    if (n < 3) {
        printf("Convex hull is not defined for fewer than 3 points.\n");
        for (int i = 0; i < n; ++i)
            printf("(%d, %d)\n", pts[i].x, pts[i].y);
        return;
    }

    // Find bottom-most point (or leftmost if tie) and place it at first position
    int min = bottomMost(pts, n);
    swap(&pts[0], &pts[min]);
    p0 = pts[0];

    // Sort the remaining n-1 points by polar angle with p0
    qsort(&pts[1], n-1, sizeof(Point), compare);

    // Remove points that are collinear and keep the farthest of collinear points
    int m = 1; // index of last unique-angle point in modified array
    for (int i = 1; i < n; ++i) {
        // keep skipping while same angle with p0 as next point
        while (i < n-1 && orientation(&p0, &pts[i], &pts[i+1]) == 0)
            i++;
        pts[m] = pts[i];
        m++;
    }

    if (m < 3) {
        // All points are collinear or less than 3 distinct directions
        printf("Convex hull is the line segment endpoints (all points collinear)\n");
        printf("Hull:\n");
        for (int i = 0; i < m; ++i)
            printf("(%d, %d)\n", pts[i].x, pts[i].y);
        return;
    }

    // Create an array as stack and process points
    Point *stack = (Point *)malloc(m * sizeof(Point));
    int top = -1;

    // push first three points
    stack[++top] = pts[0];
    stack[++top] = pts[1];
    stack[++top] = pts[2];

    for (int i = 3; i < m; ++i) {
        // Keep removing while the turn formed by points next-to-top, top, pts[i] is not counterclockwise
        while (top >= 1 && orientation(&stack[top-1], &stack[top], &pts[i]) != 2)
            top--;
        stack[++top] = pts[i];
    }

    // Print stack as convex hull vertices
    printf("Convex Hull (counterclockwise order):\n");
    for (int i = 0; i <= top; ++i)
        printf("(%d, %d)\n", stack[i].x, stack[i].y);

    free(stack);
}

int main() {
    int n;
    printf("Enter number of points N: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input for N.\n");
        return 0;
    }

    Point *pts = (Point *)malloc(n * sizeof(Point));
    printf("Enter the points as x y each on a new line:\n");
    for (int i = 0; i < n; ++i) {
        if (scanf("%d %d", &pts[i].x, &pts[i].y) != 2) {
            printf("Invalid point input.\n");
            free(pts);
            return 0;
        }
    }

    convexHull(pts, n);

    free(pts);
    return 0;
}
