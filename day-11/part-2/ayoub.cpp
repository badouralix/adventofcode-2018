#include <iostream>
#include <string>
#include <ctime>
#include <climits>

#define N 300

using namespace std;

long value(long x, long y, long serial) {
    long h = x+10;
    h *= y;
    h += serial;
    h *= (x+10);
    h = (h % 1000)/100;
    h -= 5;
    return h;
}

string run(long serial) {
    long t[N][N], max = LONG_MIN, v, s;
    int max_x, max_y, max_r, R;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            v = value(i+1, j+1, serial);
            if (i == 0 && j == 0) t[i][j] = v;
            else if (i == 0) t[i][j] = v + t[i][j-1];
            else if (j == 0) t[i][j] = v + t[i-1][j];
            else t[i][j] = v + t[i-1][j] + t[i][j-1] - t[i-1][j-1];
            
            R = 1;
            while (i >= (R-1) && j >= (R-1)) {
                if (i == R-1 && j == R-1) s = t[i][j];
                else if (i == R-1) s = t[i][j] - t[i][j-R];
                else if (j == R-1) s = t[i][j] - t[i-R][j];
                else s = t[i][j] - t[i-R][j] - t[i][j-R] + t[i-R][j-R];
                if (s > max) {
                    max = s; max_x = (i-(R-1))+1; max_y = j-(R-1)+1; max_r = R;
                }
                R++;
            }
        }
    }

    char res[256];
    sprintf(res, "%d,%d,%d", max_x, max_y, max_r);

    return string(res);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Missing one argument" << endl;
        exit(1);
    }

    clock_t start = clock();
    auto answer = run(atol(argv[1]));
    
    cout << "_duration:" << float( clock () - start ) * 1000.0 /  CLOCKS_PER_SEC << "\n";
    cout << answer << "\n";
    return 0;
}
