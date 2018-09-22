#include <stdio.h>
#include <queue>

using namespace std;

FILE *in = fopen("input.txt", "r");
FILE *out = fopen("output.txt", "w");
queue<int> nedostack;

int connections[10000][10000]; // ATTENTION 100000 x 100000 not supported
int length[10000];
int temp1, temp2;
int find1, find2;
int lines, dots;

// Recursive BFS
void bfs() {
    if (!nedostack.empty()){
        int prev = nedostack.front();
        nedostack.pop();

        for (int i = 0 ; i < dots ; i++)
            if ((length[i] < 0) && (connections[prev][i] == 1) && (i != prev)){
                length[i] = length[prev] + 1;
                nedostack.push(i);
            }

        bfs();
    }
}

int main()
{
    // INPUT.TXT
    // int(lines_count) int(dots_count)
    // int(dot1) int(dot2) ... and to last line
    // int(findFromDot) int(findToDot)

    // OUTPUT.TXT
    // int(bestLengthToDot2FromDot1InSearchLine)

    // Reading
    fscanf(in, "%i %i", &lines, &dots);
    for (int i = 0 ; i < lines ; i++){
        fscanf(in, "%i %i", &temp1, &temp2);
        temp1--; temp2--;
        connections[temp1][temp2] = 1;
        connections[temp2][temp1] = 1;
    }
    fscanf(in, "%i %i", &find1, &find2);
    find1--; find2--;

    // Initializing
    for (int i = 0 ; i < dots ; i++)
        length[i] = -1;

    // Finding best length array
    length[find1] = 0;
    nedostack.push(find1);
    bfs();

    // Print out answer
    fprintf(out, "%i\n", length[find2]);

    return 0;
}
