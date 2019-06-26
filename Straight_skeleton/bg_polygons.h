#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include <boost/geometry/index/rtree.hpp>

#include <cmath>
#include <vector>
#include <iostream>
#include <boost/foreach.hpp>

//namespace bgp {
	//定义需要的数据结构
	namespace bg = boost::geometry;
	namespace bgi = boost::geometry::index;

	typedef bg::model::point<float, 2, bg::cs::cartesian> point;
	typedef bg::model::box<point> box;
	typedef bg::model::polygon<point, false, false> polygon; // ccw, open polygon
	typedef std::pair<box, unsigned> value;
	typedef std::vector<polygon> myPolygons;



	myPolygons getPolygons();
//}