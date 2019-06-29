#include "bg_polygons.h"
#include <fstream>

//������Ҫ�����ݽṹ
//namespace bg = boost::geometry;
//namespace bgi = boost::geometry::index;

//typedef bg::model::point<float, 2, bg::cs::cartesian> point;
//typedef bg::model::box<point> box;
//typedef bg::model::polygon<point, false, false> polygon; // ccw, open polygon
//typedef std::pair<box, unsigned> value;
//typedef std::vector<polygon> myPolygons;

//����ȫ�ֱ���
indexOfPolygons IBO;
numOfPoints NOP;

//���ļ���ȡ�Ķ��������
int ii = 0;
//���϶���ε�����
int index_mpolygon = 0;
//���϶���ε�����һ������ε��ڻ�����
int index_inners = 0;

myPolygons polygons;
mpolygon_t mpoly; /*< Default-construct a multi_polygon. >*/


//bool isClockWise(point3 const &p1, point3 const &p2) {
//	
//	point3 result = bgd::cross_product(p1,p2);
//}

myPolygons getPolygons()
{
		
	// create some polygons
	//for (unsigned i = 0; i < 10; ++i)
	//{
	//	// create a polygon
	//	polygon p;
	//	for (float a = 0; a < 6.28316f; a += 1.04720f)
	//	{
	//		float x = i + int(10 * ::cos(a))*0.1f;
	//		float y = i + int(10 * ::sin(a))*0.1f;
	//		p.outer().push_back(point(x, y));
	//	}

	//	// add polygon
	//	polygons.push_back(p);			
	//}

	// create polygons from *.txt file
	std::ifstream in;
	in.open("1", std::ios::in);
	std::string buff,res;		
	polygon p;
	//int l = 0; //�����е���ų�ʼΪ0
	//��ʼ���ж�ȡ
	while (std::getline(in ,buff)) {
		//ÿ���ַ������ո��ȡ
		std::stringstream input(buff);
		//std::cout << "line_info: "<< buff << std::endl;
			
		float t[2] = {0};
		int i = 0;
			
		while (input >> res) {
				float res_f;
				res_f = atof(res.c_str());
				t[i++] = res_f;
			if (res_f < 100 && !p.outer().empty()){
					// add polygon to polygons
					polygons.push_back(p);
					//����polygon���һ�����ڵ��к͵���
					IBO.push_back(p.outer().size()*3);
					NOP.push_back(p.outer().size());
					//clear added polygon
					p.outer().clear();
			}				
		}
			
		//l++;
		//if (l > 683) {
		//	std::cout << l << std::endl;
		//}

		//�������С��2 ��������ѭ��������һ��ѭ��
		if (t[0] < 100)
			continue;
		p.outer().push_back(point(t[0]/1000, t[1]/1000));
			
	}
	//������һ�������
	// add polygon to polygons
	polygons.push_back(p);
	//����polygon���һ�����ڵ��к͵���
	IBO.push_back(p.outer().size()*3);
	NOP.push_back(p.outer().size());
	
	
	//����multi_polygon
	//�����һ����Ϊ�������
	mpoly.resize(index_mpolygon + 1);	
	toOuter(mpoly, polygons[0]);	
	ii++;
	//����еڶ���,���Ϊ�ڻ����������⻷	
	if (ii < polygons.size()) {
		mpoly[index_mpolygon].inners().resize(index_inners + 1);
		toInners(mpoly, polygons[1]);
		index_inners++;
		ii++;
	}
	//����е��������жϵ������������������ڻ�������һ������ε��ڻ�
	while(ii < polygons.size()) {
		polygon p = polygons[ii];
		point ppt = p.outer()[0];
		//�����������Ϊ˳ʱ�룬���ڻ�
		if (isClockWise(p)) {
			//�����֮ǰ�Ļ����������ڻ����ڻ�
			if (!isIncluded(ppt)) {
				mpoly[index_mpolygon].inners().resize(index_inners + 1);
				toInners(mpoly, p);
				
				index_inners++;
				ii++;
			}
			else
				break;
			
			//�����֮ǰ�Ļ����룬��ͬ���ڻ�
			//else {
			//index_mpolygon++;				
		/*	mpoly.resize(index_mpolygon + 1);
			index_inners = 0;*/
			//	index_inners++;
			//	mpoly[index_mpolygon].inners().resize(index_inners + 1);
			//	
			//	toInners(mpoly, p);								
			//}
		}
		else
			break;
	}
	/////����ָ����ȷλ��
	if (ii < polygons.size()) {
		index_mpolygon++;
		mpoly.resize(index_mpolygon + 1);
		index_inners = 0;
	}
	//�ܽ������ѭ���ı��ǵڶ���ȫ�µĶ����
	while (ii < polygons.size()) {
		polygon p = polygons[ii];
		//�˴�����Ҫ�жϻ��뻷�İ�����ϵ
		//point ppt = p.outer()[0];
		//�ڻ�
		if (isClockWise(p)) {
			mpoly[index_mpolygon].inners().resize(index_inners + 1);
			toInners(mpoly, p);

			index_inners++;
		}
		//һ������ε��⻷���ұ������һ����ӣ������Ǹ��µ�
		else {
			mpoly.resize(index_mpolygon + 1);
			toOuter(mpoly, p);

			index_inners = 0;
			index_mpolygon++;
		}
		ii++;
	}


	//for (auto it = polygons.begin(); it != polygons.end(); ++it) {
	//	polygon p = *it;
	//	std::vector< point > pointList;
	//	BOOST_FOREACH(point pt, p.outer()) {
	//		pointList.push_back(pt);
	//	}
	//	bg::assign_points(p,pointList);
	//}

	// display polygons
	std::cout << "generated polygons:" << std::endl;
	BOOST_FOREACH(polygon const& p, polygons)
		std::cout << bg::wkt<polygon>(p) << std::endl;

	//////////////����������������////////////
	//polygon a = polygons[0];
	////BOOST_FOREACH(point const& p, a)
	////	std::cout << bg::wkt<point>(p) << std::endl;

	//for (auto it = a.outer().begin(); it != a.outer().end(); ++it) {
	//	point p = *it;
	//	using boost::geometry::get;
	//	std::cout << "x = " << get<0>(p) << " y = " << get<1>(p) << std::endl;
	//}


	// create the rtree using default constructor
	//////////Ĭ�Ϲ��캯������ Rtree/////////////
	bgi::rtree< value, bgi::rstar<16, 4> > rtree;

	// fill the spatial index
	for (unsigned i = 0; i < polygons.size(); ++i)
	{
		// calculate polygon bounding box
		box b = bg::return_envelope<box>(polygons[i]);
		// insert new value
		rtree.insert(std::make_pair(b, i));
	}

	//��ѯһ��box��λ��
	// find values intersecting some area defined by a box
	box query_box(point(0, 0), point(80, 60));
	std::vector<value> result_s;
	rtree.query(bgi::intersects(query_box), std::back_inserter(result_s));

	//��ѯһ������polygons��λ��
	// find 5 nearest values to a point
	std::vector<value> result_n;
	rtree.query(bgi::nearest(point(100, 100), 3), std::back_inserter(result_n));

	// note: in Boost.Geometry the WKT representation of a box is polygon box����polygon
	// note: the values store the bounding boxes of polygons
	// the polygons aren't used for querying but are printed

	// display results
	std::cout << "spatial query box:" << std::endl;
	std::cout << bg::wkt<box>(query_box) << std::endl;
	std::cout << "spatial query result:" << std::endl;
	BOOST_FOREACH(value const& v, result_s)
		std::cout << bg::wkt<polygon>(polygons[v.second]) << std::endl;

	std::cout << "knn query point:" << std::endl;
	std::cout << bg::wkt<point>(point(0, 0)) << std::endl;
	std::cout << "knn query result:" << std::endl;
	BOOST_FOREACH(value const& v, result_n)
		std::cout << bg::wkt<polygon>(polygons[v.second]) << std::endl;

	return polygons;
}
	
indexOfPolygons getIndexOfPolygons()
{		
	return IBO;
}

numOfPoints getNumOfPoints()
{
	return NOP;
}

bool isClockWise(polygon &p)
{
	point pp1 = p.outer()[0];
	point pp2 = p.outer()[1];
	point pp3 = p.outer()[2];
	
	using boost::geometry::get;
	float x1 = get<0>(pp1);
	float y1 = get<1>(pp1);
	float x2 = get<0>(pp2);
	float y2 = get<1>(pp2);
	float x3 = get<0>(pp3);
	float y3 = get<1>(pp3);

	float xx1 = x2 - x1;
	float yy1 = y2 - y1;
	float xx2 = x3 - x2;
	float yy2 = y3 - y2;

	return (xx1*yy2-xx2*yy1 < 0);
}

bool isIncluded(point &ppt)
{
	//�ж�b�ǲ�����a��
	return bg::within(ppt, polygons[ii-1]);
}

void toOuter(mpolygon_t &t, polygon &p)
{
	BOOST_FOREACH(point pt, p.outer()) {
		using boost::geometry::get;
		t[index_mpolygon].outer().push_back(point(get<0>(pt), get<1>(pt)));
	}
}

void toInners(mpolygon_t &t, polygon &p)
{
	BOOST_FOREACH(point pt, p.outer()) {
		using boost::geometry::get;
		t[index_mpolygon].inners()[index_inners].push_back(point(get<0>(pt), get<1>(pt)));
	}
}
