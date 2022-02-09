#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#define INF 10000

struct Point
{
  double x;
  double y;
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

  // char *token = strtok(rule_input_data, ",;", );
  // int switcher = 0;

  // while (token != NULL)
  // {
  //   struct Point tempPoint;
  //   printf("token = %s\n", token);
  //   if (switcher == 0) {
  //     printf("%lf\n", atof(token));
  //     tempPoint.x = atof(token);
  //     switcher++;
  //   } else {

  //     printf("%lf\n", atof(token));
  //     tempPoint.y = atof(token);
  //     switcher = 0;
  //     room[i] = tempPoint;
  //     i++;
  //   }
  //   token = strtok(NULL, ",;");
  // }


int main() {
  // struct Point square_room[] = {{0, 0}, {10, 0}, {10, 10}, {0, 10}};
  bool result;
  char rule_input_data[]= "1,2.666;7.823,99.22;3.2,1.1;4.22,2.7;4.78,2.7;-142.583,999";

  struct Point current_point;
  struct Point room[100] = {0};

  int len = strlen(rule_input_data);
  int switcher = 1;
  int state = 0;
  int roomCount = 0;
  struct Point tempPoint;

  for (int i = 0; i <= len; i++) {
    if (rule_input_data[i] == ',' || rule_input_data[i] == ';' || i == len) {
      int q = i - state;
      char tempStr[q + 1] = "";
      // memcpy(tempStr, &rule_input_data[state], q);
      strncpy(tempStr, &rule_input_data[state], q);

      printf("tmpstr = %s\n", tempStr);
      if (switcher % 2 != 0) {
        tempPoint.x = atof(tempStr);
      } else {
        tempPoint.y = atof(tempStr);
        // printf("---------\n");
        // printf("%lf\n", tempPoint.x);
        // printf("%lf\n", tempPoint.y);
        // printf("---------\n");
        printf("%i\n", roomCount);
        // room = realloc(room, sizeof(tempPoint));
        room[roomCount] = tempPoint;
        roomCount++;
        memset(&tempPoint, 0, sizeof(tempPoint));
      }
      switcher++;
      state = i + 1;
    }
  }

  printf("\n\n");
  printf("!!!!!!!!!!!\n");

  printf("%lf\n", room[0].x);
  printf("%lf\n", room[0].y);

  printf("--------------------\n");

  printf("%lf\n", room[1].x);
  printf("%lf\n", room[1].y);

  printf("--------------------\n");

  printf("%lf\n", room[2].x);
  printf("%lf\n", room[2].y);

  printf("--------------------\n");

  printf("%lf\n", room[3].x);
  printf("%lf\n", room[3].y);

  printf("--------------------\n");

  printf("%lf\n", room[4].x);
  printf("%lf\n", room[4].y);

  printf("--------------------\n");

  printf("%lf\n", room[5].x);
  printf("%lf\n", room[5].y);


  // char *istr;
  // istr = strtok(rule_input_data,sep);

  // while (istr != NULL)
  // {
  //   printf("%s\n",istr);
  //   // printf("%s\n",zzz);
  //   char *my;
  //   strcpy(istr, my);
  //   // arr[iterator] = my;
  //   // iterator++;
  //   printf("%s\n", my);
  //   istr = strtok(NULL,sep);
  // }
  // // printf("%i\n", sizeof(arr));

  // Parse input_data and push
  // rule_input_data.split('{'})
  // room.push(input_data.map(i => i))

  // int n = sizeof(room) / sizeof(room[0]);
  // result = isInside(room, n, current_point);

  // if (result == true) {
  //   // printf("Hey you");
  //   // os_strdup("true", lf->result);
  //   // os_strdup("zzzz", lf->protocol);
  // } else {
  //   // os_strdup("false", lf->result);
  //   // printf("another");
  // }
  // // return (NULL);

  // struct Point square_room[] = {{0, 0}, {10, 0}, {10, 10}, {0, 10}};
  // struct Point triangle_room[] = {{1.22, 33}, {4.9, 5.1}, {5, 0}};
  // struct Point circle_room[] = {{0, 0}, {-3, 3}, {0, 6}, {3, 9}, {6, 6}, {9, 3}, {6, 0}, {3, -3}};

  // scanf("%lf", &(p.x));
  // scanf("%lf", &(p.y));

  // struct Point p;
  // scanf("%lf", &(p.x));
  // scanf("%lf", &(p.y));
  // printf("p.x = %lf\n", p.x);
  // printf("p.y = %lf\n", p.y);

  // printf(sizeof(square_room[0]));
  // printf(sizeof(triangle_room[0]));
  // printf(sizeof(circle_room[0]));

  // int n = getLength(&square_room);


  // printf("%i\n", sizeof(triangle_room));
  // printf("%i\n", sizeof(circle_room[0]));
  // printf("%i\n", sizeof(n));

  // printf("%lf\n", square_room[1].y);
  // printf("%lf\n", triangle_room[1].x);
  // printf("%lf\n", circle_room[1].x);

  // printf(BoolToString(isInside(square_room, n, p)));

  return 0;
}

