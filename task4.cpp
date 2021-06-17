#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 100;

struct Point
{
	int x, y;
};

inline bool cmpX(const Point &a, const Point &b)
{
	return a.x < b.x || a.x == b.x && a.y < b.y;
}

inline bool cmpY(const Point &a, const Point &b)
{
	return a.y < b.y;
}

inline void upd_ans(const Point &a, const Point &b, Point &firstPoint, Point &secondPoint, int &minDist)
{
	double dist = sqrt((a.x-b.x) * (a.x-b.x) + (a.y-b.y) * (a.y-b.y));
	if (dist < minDist)
    {
		minDist = dist;
        firstPoint = a;
        secondPoint = b;
    }
}

void rec(int l, int r, Point* a, Point &firstPoint, Point &secondPoint, int &minDist)
{
	if (r - l <= 3)
    {
		for (int i = l; i <= r; i++)
        {
			for (int j = i + 1; j <= r; j++)
            {
				upd_ans(a[i], a[j], firstPoint, secondPoint, minDist);
            }
        }
		sort(a + l, a + r + 1, &cmpY);
		return;
	}

	int m = (l + r) / 2;
	int midx = a[m].x;
	rec(l, m, a, firstPoint, secondPoint, minDist);
    rec(m + 1, r, a, firstPoint, secondPoint, minDist);
	static Point t[MAXN];
	merge(a + l, a + m + 1, a + m + 1, a + r + 1, t, &cmpY);
	copy(t, t + r - l + 1, a + l);

	int tsz = 0;
	for (int i = l; i <= r; i++)
    {
		if (abs(a[i].x - midx) < minDist)
        {
			for (int j = tsz - 1; j >= 0 && a[i].y - t[j].y < minDist; j--)
            {
				upd_ans(a[i], t[j], firstPoint, secondPoint, minDist);
            }
			t[tsz] = a[i];
            tsz++;
		}
    }
}

int main()
{
    Point a[MAXN];
    cout << "Enter a quantity of points: ";
    int n;
    cin >> n;
    cout << "Enter the points' coordinates separated by a space. Enter each point on new line:" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].x >> a[i].y;
    }

    Point firstPoint, secondPoint;
    sort(a, a + n, &cmpX);
    int minDist = INT_MAX;
    rec(0, n - 1, a, firstPoint, secondPoint, minDist);
    cout << "First  point coordinates: (" << firstPoint.x << "; " << firstPoint.y << ")" << endl;
    cout << "Second point coordinates: (" << secondPoint.x << "; " << secondPoint.y << ")" << endl;

    return 0;
}
