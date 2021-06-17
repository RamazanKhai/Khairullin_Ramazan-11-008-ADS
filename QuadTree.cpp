#include <iostream>
#include <vector>
using namespace std;

struct Point
{
    int x, y;

    string getString()
    {
        return "(" + to_string(x) + "; " + to_string(y) + ")";
    }

    Point(int _x, int _y)
    {
        x = _x; y = _y;
    }
};

struct Rectangle
{
    Point *topLeft;
    Point *bottomRight;

    Rectangle(Point *_topLeft, Point *_bottomRight)
    {
        topLeft = _topLeft;
        bottomRight = _bottomRight;
    }
    
    bool containsPoint(Point *point)
    {
        return (topLeft->x <= point->x && point->x <= bottomRight->x && topLeft->y >= point->y && point->y >= bottomRight->y);
    }

    string getString()
    {
        Point *topRight = new Point(bottomRight->x, topLeft->y);
        Point *bottomLeft = new Point(topLeft->x, bottomRight->y);
        return topLeft->getString() + " " + topRight->getString() + " " + bottomLeft->getString() + " " + bottomRight->getString();
    }
};

class QuadTree
{
private:
    Rectangle *boundary;
    vector<Point*> points;
    int qtNodeCapacity;

    QuadTree *northWest = nullptr;
    QuadTree *northEast = nullptr;
    QuadTree *southWest = nullptr;
    QuadTree *southEast = nullptr;

    void subdivide()
    {
        Point *center = new Point((boundary->topLeft->x + boundary->bottomRight->x) / 2,
                                  (boundary->topLeft->y + boundary->bottomRight->y) / 2);
        northWest = new QuadTree(new Rectangle(boundary->topLeft, center), qtNodeCapacity);
        northEast = new QuadTree(new Rectangle(new Point(center->x, boundary->topLeft->y),
                                               new Point(boundary->bottomRight->x, center->y)), qtNodeCapacity);
        southWest = new QuadTree(new Rectangle(new Point(boundary->topLeft->x, center->y),
                                               new Point(center->x, boundary->bottomRight->y)), qtNodeCapacity);
        southEast = new QuadTree(new Rectangle(center, boundary->bottomRight), qtNodeCapacity);
        for (int i = 0; i < qtNodeCapacity; i++)
        {
            if (northWest->insertPoint(points[i])) continue;
            if (northEast->insertPoint(points[i])) continue;
            if (southWest->insertPoint(points[i])) continue;
            if (southEast->insertPoint(points[i])) continue;
        }
    }
    
    void deepFirstTraversal(int &nodeCounter)
    {
        cout << nodeCounter << " node borders: " << boundary->getString() << ". ";
        if (points.size() > 0)
        {
            cout << "Points: ";
            for (int i = 0; i < points.size() - 1; i++)
                cout << points[i]->getString() << ", ";
            cout << points[points.size() - 1]->getString();
        }
        else
            cout << "There is no points in this Rectangle";
        cout << endl;
        nodeCounter++;
        if (northWest != nullptr)
        {
            northWest->deepFirstTraversal(nodeCounter);
            northEast->deepFirstTraversal(nodeCounter);
            southWest->deepFirstTraversal(nodeCounter);
            southEast->deepFirstTraversal(nodeCounter);
        }
    }

public:
    QuadTree(Rectangle *_boundary, int _qtNodeCapacity)
    {
        boundary = _boundary;
        qtNodeCapacity = _qtNodeCapacity;
    }

    bool insertPoint(Point *point)
    {
        if (!boundary->containsPoint(point))
            return false;

        if (points.size() < qtNodeCapacity)
        {
            points.push_back(point);
            return true;
        }

        if (northWest == nullptr)
            subdivide();

        if (northWest->insertPoint(point)) return true;
        if (northEast->insertPoint(point)) return true;
        if (southWest->insertPoint(point)) return true;
        if (southEast->insertPoint(point)) return true;

        return false;
    }

    void deepFirstTraversal()
    {
        int nodeCounter = 1;
        deepFirstTraversal(nodeCounter);
    }
};

int main()
{
    int X, K, N;
    cout << "Enter X: ";
    cin >> X;
    cout << "Enter K: ";
    cin >> K;
    cout << "Enter N: ";
    cin >> N;
    QuadTree *qt = new QuadTree(new Rectangle(new Point(0, X), new Point(X, 0)), K);
    cout << "Enter N points' coordinates separated by a space. Enter each point on new line:" << endl;
    for (int i = 0; i < N; i++)
    {
        int x, y;
        cin >> x >> y;
        qt->insertPoint(new Point(x, y));
    }

    qt->deepFirstTraversal();

    return 0;
}
