#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

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


bool test(double a)
{
  return a > 5 ? true : false;
}

const char *const BoolToString(bool b)
{
  return b ? "true\n" : "false\n";
}

int getLength(struct Point p)
{
  return sizeof(p) / sizeof(p[0]);
}


int main() {
  printf("Enter point value:\n");
  struct Point square_room[] = {{0, 0}, {10, 0}, {10, 10}, {0, 10}};
  struct Point triangle_room[] = {{1.22, 0}, {4.9, 5.1}, {5, 0}};
  struct Point circle_room[] = {{0, 0}, {-3, 3}, {0, 6}, {3, 9}, {6, 6}, {9, 3}, {6, 0}, {3, -3}};
  // struct Point p = {1.22, -3};

  struct Point p;
  scanf("%lf", &(p.x));
  scanf("%lf", &(p.y));
  printf("p.x = %lf\n", p.x);
  printf("p.y = %lf\n", p.y);

  int n = getLength(&square_room);
  // int n = sizeof(square_room) / sizeof(square_room[0]);
  printf(BoolToString(isInside(square_room, n, p)));
  return 0;
}

