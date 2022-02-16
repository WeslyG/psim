#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#define INF 10000


#define CHUNK 1024 /* read 1024 bytes at a time */
// struct Point parse_point(char *data)
// {
//     char search_string []="point=\"";
//     char *istr;
//     int length = 0;
//     struct Point result;

//     istr = strstr(data,search_string);
//     char *point = malloc(sizeof(char) * (strlen(istr) + 1));

//     for (int i = strlen(search_string); i < strlen(istr); i++) {
//       if (istr[i] == '"') {
//         break;
//       }
//       if (istr[i] == ' ') {
//         continue;
//       }
//       point[length] = istr[i];
//       length++;
//     }
//     length = 0;

//     for(int i = 0; i < strlen(point); i++) {
//       if (point[i] == ';') {
//         length = i;
//       }
//     }

//     char x[length+1];
//     memset(&x, 0, sizeof(x));
//     strncpy(x, &point[0], length);

//     int z = strlen(point) - length;
//     char y[z];
//     memset(&y, 0, sizeof(y));
//     strncpy(y, &point[length+1], z);

//     // printf("%s\n", x);
//     // printf("%s\n", y);
//     result.x = atof(x);
//     result.y = atof(y);
//     free(point);
//     // printf("%lf\n", result.x);
//     // printf("%lf\n", result.y);
//     return result;
// }

// char *parse_user(char *data) {
//     int length = 0;
//     char *user = malloc(sizeof(char) * (strlen(data) + 1));
//     for (int i = 6; i < strlen(data); i++) {
//       if (data[i] == '"') {
//         break;
//       }
//       user[length] = data[i];
//       length++;
//     }
//     return user;
// }

struct Point
{
  double x;
  double y;
};

struct PsimConfig
{
  char *user;
  struct Point room[100];
};


bool onSegment(struct Point p, struct Point q, struct Point r)
{
  if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
      q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
    return true;
  return false;
}

int orientation(struct Point p, struct Point q, struct Point r)
{
  int val = (q.y - p.y) * (r.x - q.x) -
            (q.x - p.x) * (r.y - q.y);

  if (val == 0)
    return 0;               // collinear
  return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool doIntersect(struct Point p1, struct Point q1, struct Point p2, struct Point q2)
{
  // Find the four orientations needed for general and
  // special cases
  int o1 = orientation(p1, q1, p2);
  int o2 = orientation(p1, q1, q2);
  int o3 = orientation(p2, q2, p1);
  int o4 = orientation(p2, q2, q1);

  // General case
  if (o1 != o2 && o3 != o4)
    return true;

  // Special Cases
  // p1, q1 and p2 are collinear and p2 lies on segment p1q1
  if (o1 == 0 && onSegment(p1, p2, q1))
    return true;

  // p1, q1 and p2 are collinear and q2 lies on segment p1q1
  if (o2 == 0 && onSegment(p1, q2, q1))
    return true;

  // p2, q2 and p1 are collinear and p1 lies on segment p2q2
  if (o3 == 0 && onSegment(p2, p1, q2))
    return true;

  // p2, q2 and q1 are collinear and q1 lies on segment p2q2
  if (o4 == 0 && onSegment(p2, q1, q2))
    return true;

  return false; // Doesn't fall in any of the above cases
}

bool isInside(struct Point polygon[], int n, struct Point p)
{
  // There must be at least 3 vertices in polygon[]
  if (n < 3)
    return false;

  // Create a point for line segment from p to infinite
  struct Point extreme = {INF, p.y};

  // Count intersections of the above line with sides of polygon
  int count = 0, i = 0;
  do
  {
    int next = (i + 1) % n;

    if (doIntersect(polygon[i], polygon[next], p, extreme))
    {
      if (orientation(polygon[i], p, polygon[next]) == 0)
        return onSegment(polygon[i], p, polygon[next]);

      count++;
    }
    i = next;
  } while (i != 0);

  // Return true if count is odd, false otherwise
  return count & 1; // Same as (count%2 == 1)
}


int main (void)
{
    // struct PsimConfig config[100] = {0};

    // printf("test = %s, %s \n", "one" "two");
    char *a = "tree";
    char *b = "two";
    char *c = "one";

    char *ress = (char*)malloc(sizeof(a) + sizeof(b) * sizeof(char));
    sprintf(ress, "x=%s, y=%s", a, b);
    printf("%s", ress);

    // char *str = "test string123123123";
    // char buf[50] = {0};

    // printf("строка: \"%s\"\n\n", str);
    // printf("буфер перед копированием: \"%s\"\n", buf);

    // printf("%i\n", sizeof(buf));
    // strncpy(buf, str, sizeof(buf) + 1);

    // str = NULL;

    // printf("буфер после копирования:  \"%s\"\n", buf);
    // printf("оригинальная строка:  \"%s\"\n", str);

    // char *test[] = {"vasya", "petya"};
    // struct PsimConfig config[] = {
    //     {
    //       user: "vasya",
    //       room: {{0, 0}, {10, 0}, {10, 10}, {0, 10}}
    //     },
    //     {
    //       user: "petya",
    //       room: {{10, 10}, {20, 10}, {20, 20}, {10, 20}}
    //     },
    //   };

    // int n = sizeof(config) / sizeof(config[0]);
    // for (int i = 0; i < n; i++) {
    //   config2[i] = config[i];
    // }

    // config2[0].user = test[0];
    // config2[1].user = test[1];

    // printf("user1 = %s\n", config2[0].user);
    // printf("user2 = %s\n", config2[1].user);

    // char *test = "rules";
    // if (strcmp(test, "rules") == 0) {
    //   printf("test test test");
    // } else {
    //   printf("else");
    // }

    // #define CHUNK 1024 /* read 1024 bytes at a time */
    // char buf[CHUNK];
    // FILE *file;
    // size_t nread;

    // file = fopen("./rule.xml", "r");
    // if (file) {
    //     while ((nread = fread(buf, 1, sizeof buf, file)) > 0)
    //         fwrite(buf, 1, nread, stdout);
    //     if (ferror(file)) {
    //         printf("Test");
    //     }
    //     fclose(file);
    // }

    // char str1 []="user=\"vasya\" point=\"-4.256;6.121231239\" 123123 ";
    // struct PsimConfig config[] = {
    //     {
    //       user: "vasya",
    //       room: {{0, 0}, {10, 0}, {10, 10}, {0, 10}}
    //     },
    //     {
    //       user: "petya",
    //       room: {{10, 10}, {20, 10}, {20, 20}, {10, 20}}
    //     },
    //   };
    // // printf("%d\n", sizeof(config));
    // // int n = sizeof(config)/sizeof(config[0]);
    // // for (int i = 0; i < n; i++) {
    // //   printf("%s\n", config[i].user);
    // // }
    // struct Point current_point = {1,10};

    // int n = sizeof(config[0].room) / sizeof(config[0].room[0]);
    // bool result;
    // result = isInside(config[0].room, n, current_point);
    // printf("%s", result ? "true" : "false");
    return 0;
}
