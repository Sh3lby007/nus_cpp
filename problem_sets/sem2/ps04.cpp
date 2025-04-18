#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

/**************************
Point Class claude
**************************/
class Point {
 public:
  // Constructor is the make_point() equivalent in OOP approach
  Point(double x, double y) {
    p[0] = x;
    p[1] = y;
  }

  // Minor change to the name, instead of x_of() ==> get_x()
  virtual double get_x() const { return p[0]; }

  // Minor change to the name, instead of y_of() ==> get_y()
  virtual double get_y() const { return p[1]; }

  virtual void set_x(double val) { p[0] = val; }

  virtual void set_y(double val) { p[1] = val; }

  // Example to show interaction between objects of the same class
  virtual double distance_to(const Point& anotherPt) const {
    double x = p[0] - anotherPt.p[0];  // note that you can access the private
                                       // data of objects of the same class
    double y = p[1] - anotherPt.p[1];

    return sqrt(x * x + y * y);
  }

  // Return true if p has the same (x,y) as this object
  virtual bool equal(const Point& p) {
    return (this->get_x() == p.get_x() && this->get_y() == p.get_y());
  }

  // Minor change to the name, instead of display_point() ==> print()
  virtual void print(ostream& out) {
    out << "(" << get_x() << "," << get_y() << ")";
  }

 private:
  double p[2];
};

/*****************************
Line Class
*****************************/
class Line {
 public:
  // Constructor is the make_line() equivalent in OOP approach
  Line(const Point& s, const Point& e) : start(s), end(e) {}

  virtual Point get_start() const { return start; }

  virtual Point get_end() const { return end; }

  virtual double length() const { return start.distance_to(end); }

  // Return true if l has the same end points as this object
  // Note that the end points may be reversed for the two lines
  bool equal(const Line& l) {
    // Check if endpoints match directly
    if ((start.equal(l.get_start()) && end.equal(l.get_end())) ||
        // Check if endpoints match in reverse
        (start.equal(l.get_end()) && end.equal(l.get_start()))) {
      return true;
    }
    return false;
  }

 private:
  Point start, end;
};

/*****************************
Polygon Class
*****************************/
class Polygon {
 public:
  Polygon(const Point& p1, const Point& p2, const Point& p3) {
    // Initialize polygon with 3 points
    vertices.push_back(p1);
    vertices.push_back(p2);
    vertices.push_back(p3);
  }

  virtual bool add(Point& p) {
    // Check if point already exists in polygon
    for (size_t i = 0; i < vertices.size(); i++) {
      if (vertices[i].equal(p)) {
        return false;  // Duplicate point, cannot add
      }
    }

    // Add point to polygon
    vertices.push_back(p);
    return true;
  }

  virtual bool add(Line& exist, Point& p) {
    // Check if point already exists in polygon
    for (size_t i = 0; i < vertices.size(); i++) {
      if (vertices[i].equal(p)) {
        return false;  // Duplicate point, cannot add
      }
    }

    // Check if the line exists in the polygon
    bool lineFound = false;
    size_t startIdx = 0;
    size_t endIdx = 0;

    // Check each edge of the polygon
    for (size_t i = 0; i < vertices.size(); i++) {
      size_t nextIdx = (i + 1) % vertices.size();

      // Create a line from current vertex to next vertex
      Line currentLine(vertices[i], vertices[nextIdx]);

      // If line matches the one we're looking for
      if (currentLine.equal(exist)) {
        lineFound = true;
        startIdx = i;
        endIdx = nextIdx;
        break;
      }
    }

    if (!lineFound) {
      return false;  // Line doesn't exist in polygon
    }

    // Insert the new point between the two vertices of the existing line
    // If endIdx is 0 (meaning startIdx is the last vertex), we add to the end
    if (endIdx == 0) {
      vertices.push_back(p);
    } else {
      // Insert at position endIdx
      vertices.insert(vertices.begin() + endIdx, p);
    }

    return true;
  }

  virtual double perimeter() {
    double totalLength = 0.0;

    // Sum the lengths of all edges
    for (size_t i = 0; i < vertices.size(); i++) {
      size_t nextIdx = (i + 1) % vertices.size();
      totalLength += vertices[i].distance_to(vertices[nextIdx]);
    }

    return totalLength;
  }

  virtual void print(ostream& out) {
    // Handle empty polygon case
    if (vertices.empty()) {
      return;
    }

    // Print first vertex
    vertices[0].print(out);

    // Print remaining vertices with arrows
    for (size_t i = 1; i < vertices.size(); i++) {
      out << " -> ";
      vertices[i].print(out);
    }

    // Print arrow and first vertex again to close the polygon
    out << " -> ";
    vertices[0].print(out);
  }

 private:
  // Store polygon as a vector of points
  vector<Point> vertices;
};

int main() {
  Point p1(2, 2), p2(5, 2), p3(5, 6), p4(5, 2);

  // Part 1. Point

  //  Distance test
  cout << "Distance from p1 to p2 is ";
  cout << p1.distance_to(p2) << endl;

  //  Same point check: should be false
  cout << "Is p1 the same as p2 =  ";
  cout << p1.equal(p2) << endl;

  //  Same point check: should be true
  cout << "Is p2 the same as p4 =  ";
  cout << p2.equal(p4) << endl;

  // Part 2. Line
  Line l1(p1, p2), l2(p2, p1), l3(p1, p3);

  //  l1 is the same as l2, even though the points are reversed
  cout << "Is l1 the same as l2 =  ";
  cout << l1.equal(l2) << endl;

  //  l1 is the not the as l3
  cout << "Is l1 the same as l3 =  ";
  cout << l1.equal(l3) << endl;

  // Part 3. Polygon

  //  Use of constructor
  Polygon pg(p1, p2, p3);

  //  Basic test of print() and perimeter()
  pg.print(cout);
  cout << endl;
  cout << "Perimeter = " << pg.perimeter() << endl;

  //  Add duplicate point, i.e. should fail to add
  if (!pg.add(p1)) {
    cout << "Add p1 to polygon failed!\n";
  } else {
    cout << "Add p1 to polygon ok!\n";
    pg.print(cout);
    cout << endl;
    cout << "Perimeter = " << pg.perimeter() << endl;
  }

  //  Add point should be ok in this case
  Point p5(2, 6);

  if (!pg.add(p5)) {
    cout << "Add p5 to polygon failed!\n";
  } else {
    cout << "Add p5 to polygon ok!\n";
    pg.print(cout);
    cout << endl;
    cout << "Perimeter = " << pg.perimeter() << endl;
  }

  //  Use the alternative version of add point

  //  This case should fail as l6 is not an existing line in polygon pg
  Point p7(-1, 2);
  Line l6(p1, p3);

  if (!pg.add(l6, p7)) {
    cout << "Remove l6 and add p7 to polygon failed!\n";
  } else {
    cout << "Remove l6 and add p7 to polygon ok!\n";
    pg.print(cout);
    cout << endl;
    cout << "Perimeter = " << pg.perimeter() << endl;
  }

  //  This case should be ok as l5 is an existing line in polygon pg
  Point p6(-1, 6);
  Line l5(p1, p5);

  if (!pg.add(l5, p6)) {
    cout << "Remove l5 and add p6 to polygon failed!\n";
  } else {
    cout << "Remove l5 and add p6 to polygon ok!\n";
    pg.print(cout);
    cout << endl;
    cout << "Perimeter = " << pg.perimeter() << endl;
  }

  return 0;
}