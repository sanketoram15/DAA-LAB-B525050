#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 100005
#define MAX_L 11
#define HASH_SIZE 262147

char words[MAX_N][MAX_L];

int wordCount = 0;
int L;

int hashTable[HASH_SIZE];
int distA[MAX_N], distB[MAX_N];
int queueA[MAX_N], queueB[MAX_N];

unsigned int hashWord(const char *s)
{
unsigned int h = 5381;


while (*s)
{
    h = ((h << 5) + h) + (unsigned char)*s;
    s++;
}

return h % HASH_SIZE;

}

int findWord(const char *s)
{
unsigned int h = hashWord(s);
unsigned int start = h;


while (hashTable[h] != -1)
{
    int id = hashTable[h];

    if (strcmp(words[id], s) == 0)
        return id;

    h++;

    if (h == HASH_SIZE)
        h = 0;

    if (h == start)
        break;
}

return -1;

}

int insertWord(int id)
{
unsigned int h = hashWord(words[id]);
unsigned int start = h;


while (hashTable[h] != -1)
{
    h++;

    if (h == HASH_SIZE)
        h = 0;

    if (h == start)
        return 0;
}

hashTable[h] = id;
return 1;

}

int addWord(const char *s)
{
int id = findWord(s);


if (id != -1)
    return id;

if (wordCount >= MAX_N)
    return -1;

strcpy(words[wordCount], s);

if (!insertWord(wordCount))
    return -1;

return wordCount++;


}

int expandLevel(
int *queue,
int *head,
int *tail,
int *distThis,
int *distOther
)
{
int levelEnd = *tail;

while (*head < levelEnd)
{
    int u = queue[(*head)++];

    for (int pos = 0; pos < L; pos++)
    {
        char original = words[u][pos];

        for (char c = 'a'; c <= 'z'; c++)
        {
            if (c == original)
                continue;

            words[u][pos] = c;

            int v = findWord(words[u]);

            if (v != -1)
            {
                if (distThis[v] == -1)
                {
                    distThis[v] = distThis[u] + 1;
                    queue[(*tail)++] = v;
                }

                if (distOther[v] != -1)
                {
                    int answer = distThis[v] + distOther[v];

                    words[u][pos] = original;
                    return answer;
                }
            }
        }

        words[u][pos] = original;
    }
}

return -1;


}

int bidirectionalBFS(int start, int target)
{
if (start == target)
return 0;

for (int i = 0; i < wordCount; i++)
{
    distA[i] = -1;
    distB[i] = -1;
}

int headA = 0, tailA = 0;
int headB = 0, tailB = 0;

queueA[tailA++] = start;
queueB[tailB++] = target;

distA[start] = 0;
distB[target] = 0;

while (headA < tailA && headB < tailB)
{
    int result;

    if (tailA - headA <= tailB - headB)
    {
        result = expandLevel(
            queueA, &headA, &tailA, distA, distB
        );
    }
    else
    {
        result = expandLevel(
            queueB, &headB, &tailB, distB, distA
        );
    }

    if (result != -1)
        return result;
}

return -1;


}

int main(void)
{
int N;
char A[MAX_L], B[MAX_L];


if (scanf("%d", &N) != 1 || N <= 0 || N >= MAX_N)
{
    printf("-1\n");
    return 0;
}

for (int i = 0; i < HASH_SIZE; i++)
    hashTable[i] = -1;

wordCount = 0;

for (int i = 0; i < N; i++)
{
    char temp[MAX_L];

    if (scanf("%10s", temp) != 1)
    {
        printf("-1\n");
        return 0;
    }

    int len = (int)strlen(temp);

    if (i == 0)
        L = len;

    if (len != L || L == 0)
    {
        printf("-1\n");
        return 0;
    }

    for (int j = 0; j < len; j++)
    {
        if (temp[j] < 'a' || temp[j] > 'z')
        {
            printf("-1\n");
            return 0;
        }
    }

    if (addWord(temp) == -1)
    {
        printf("-1\n");
        return 0;
    }
}

if (scanf("%10s %10s", A, B) != 2)
{
    printf("-1\n");
    return 0;
}

if ((int)strlen(A) != L || (int)strlen(B) != L)
{
    printf("-1\n");
    return 0;
}

int start = findWord(A);
int target = findWord(B);

if (start == -1 || target == -1)
{
    printf("-1\n");
    return 0;
}

printf("%d\n", bidirectionalBFS(start, target));

return 0;

}
