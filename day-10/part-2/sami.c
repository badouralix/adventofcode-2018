#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXPOINTS 500
#define MAXHEIGHT 20
#define MAXWIDTH 220

typedef struct {
    float x;
    float y;
    float vx;
    float vy;
} point_t;

point_t ps[MAXPOINTS];
int grid[MAXHEIGHT][MAXWIDTH];
int points;

void parse(char* s) {
    float x, y, vx, vy;
    char* buf = NULL;

    buf = strtok(s, "\n");
    while (buf != NULL) {
        sscanf(buf, "position=<%f,%f> velocity=<%f, %f>", &x, &y, &vx, &vy);
        ps[points++] = (point_t) {
            .x = x,
            .y = y,
            .vx = vx,
            .vy = vy,
        };
        buf = strtok(NULL, "\n");
    }
}

// Compute the center of all the points
point_t center() {
    point_t p = (point_t) {
        .x = 0,
        .y = 0,
        .vx = 0,
        .vy = 0,
    };

    for (int i = 0; i < points; ++i) {
        p.x += ps[i].x;
        p.y += ps[i].y;
        p.vx += ps[i].vx;
        p.vy += ps[i].vy;
    }

    if (points) {
        p.x /= points;
        p.y /= points;
        p.vx /= points;
        p.vy /= points;
    }

    return p;
}

float get_time() {
    // We want to minimize the variance for the points positions
    // Each point p_i is at p0_i + v_i * t at time t
    // If we try to minimize the distance between each of the points we find:
    // t = - (sum((vc-v_i) * (c0 - p0_i)) / sum((vc - v_i)^2))

    // We will return - a / b
    point_t c = center();
    point_t p;
    float a, b;
    a = b = 0.0;

    for (int i = 0; i < points; ++i) {
        p = ps[i];

        // Norm of (the center speed - the current point speed)
        b += (c.vx - p.vx) * (c.vx - p.vx) + (c.vy - p.vy) * (c.vy - p.vy);

        // Scalar product of (center speed - current point speed) and (center initial pos - current point initial pos)
        a += (c.vx - p.vx) * (c.x - p.x) + (c.vy - p.vy) * (c.y - p.y);
    }

    // If the first time does not work try increasing the offset #hacky
    int offset = 0;

    return offset - a / b;
}

// go to time t for the points
void skip(int t) {
    double minx, miny;
    minx = miny = 50000;

    for (int i = 0; i < points; ++i) {
        ps[i].x += t * ps[i].vx;
        ps[i].y += t * ps[i].vy;

        minx = ps[i].x < minx ? ps[i].x : minx;
        miny = ps[i].y < miny ? ps[i].y : miny;
    }

    for (int i = 0; i < points; ++i) {
        // Store the point in the grid
        grid[(int)(ps[i].y - miny)][(int)(ps[i].x - minx)] = 1;
    }
}

// Print the points
void print_points() {
    for (int i = 0; i < MAXHEIGHT; ++i) {
        for (int j = 0; j < MAXWIDTH; ++j) {
            if (grid[i][j])
                printf("#");
            else
                printf(".");
        }
        printf("\n");
    }
}

int run(char* s) {
    parse(s);
    skip((int)get_time());
    print_points();
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Missing one argument\n");
        exit(1);
    }

    clock_t start = clock();
    int answer = run(argv[1]);

    printf("_duration:%f\n%d\n",
        (float)(clock() - start) * 1000.0 / CLOCKS_PER_SEC, answer);
    return 0;
}
