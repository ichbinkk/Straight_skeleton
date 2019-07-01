#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include <boost/geometry/index/rtree.hpp>

#include <boost/geometry/arithmetic/cross_product.hpp>

#include <cmath>
#include <vector>
#include <iostream>
#include <boost/foreach.hpp>


//定义需要的数据结构
namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;
namespace bgd = boost::geometry::detail;


//typedef bg::model::point<float, 2, bg::cs::cartesian> point;
typedef bg::model::d2::point_xy<float> point;
typedef bg::model::box<point> box;
typedef bg::model::polygon<point, false> polygon; // ccw, open polygon
typedef std::pair<box, unsigned> value;
typedef std::vector<polygon> myPolygons;
typedef std::vector<int> indexOfPolygons;
typedef std::vector<int> numOfPoints;
typedef bg::model::multi_polygon<polygon> mpolygon_t; /*< Clockwise, closed multi_polygon. >*/


	
myPolygons getPolygons();
mpolygon_t getMpolygons();

indexOfPolygons getIndexOfPolygons();
numOfPoints getNumOfPoints();

void toOuter(mpolygon_t &t, polygon &p);
void toInners(mpolygon_t &t, polygon &p);

bool isIncluded(point &ppt);
bool isClockWise(polygon &p);