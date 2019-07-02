#include<vector>
#include<iterator>
#include<iostream>
#include<iomanip>
#include<string>
#include <fstream>

#include<boost/shared_ptr.hpp>

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Polygon_with_holes_2.h>
#include<CGAL/create_straight_skeleton_from_polygon_with_holes_2.h>

#include "dump_to_eps.h"
#include "bg_polygons.h"
#include <boost/foreach.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef K::Point_2                    Point;
typedef CGAL::Polygon_2<K>            Polygon_2;
typedef CGAL::Polygon_with_holes_2<K> Polygon_with_holes;
typedef CGAL::Straight_skeleton_2<K>  Straight_skeleton;

typedef boost::shared_ptr<Straight_skeleton> Straight_skeleton_ptr;

//全局变量 输出txt
std::string txtname = "test.skeleton.txt";
std::ofstream f(txtname.c_str());

template<class S>
void dump_to_txt(CGAL::Straight_skeleton_2<S> const& aSkeleton, std::ostream& rOut)
{
	typedef typename CGAL::Straight_skeleton_2<S>::Halfedge_const_iterator Halfedge_const_iterator;
	typedef typename CGAL::Straight_skeleton_2<S>::Halfedge_const_handle   Halfedge_const_handle;

	for (Halfedge_const_iterator hit = aSkeleton.halfedges_begin(); hit != aSkeleton.halfedges_end(); ++hit)
	{
		Halfedge_const_handle h = hit;

		int scale = 1;

		if (h->is_bisector() && ((h->id() % 2) == 0) && !h->has_infinite_time() && !h->opposite()->has_infinite_time())
		{

			f << scale * h->vertex()->point().x()
				<< " "
				<< scale * h->vertex()->point().y()
				<< "\n"
				<< scale * h->opposite()->vertex()->point().x()
				<< " "
				<< scale * h->opposite()->vertex()->point().y()
				<< "\n";
		}
	}
}

void show_straight_skeleton()
{
	Polygon_with_holes input;
	
	if (1)
	{
		std::string name = "test";
		std::cout << "Input file: " << name << std::endl;
		std::stringstream is;

		if (is)
		{
			mpolygon_t mp = getMpolygons();
			//可以指定计算到某个特定的多边形
			int q = 0,res_p = 0;
			//遍历所有mpolygon
			for (int i = 0; i < mp.size() - 1; i++) {

				polygon p = mp[i];
				//输入outer
				is << p.outer().size() << std::endl;
				BOOST_FOREACH(auto outer, p.outer()) {
					using boost::geometry::get;
					is << get<0>(outer) << " " << get<1>(outer) << std::endl;
				}
				//输入inners
				if (p.inners().size() > 0) {
					is << p.inners().size() << std::endl;
					BOOST_FOREACH(auto inner, p.inners()) {
						is << inner.size() << std::endl;
						BOOST_FOREACH(point in, inner) {
							using boost::geometry::get;
							is << get<0>(in) << " " << get<1>(in) << std::endl;
						}
					}
				}
				is << std::endl;
				//测试stringstream is有没有输出
				std::cout << is.str();

				//convert stringstream to "input"
				is >> input;
				Straight_skeleton_ptr ss = CGAL::create_interior_straight_skeleton_2(input);
				dump_to_txt(*ss, f);

				is.str("");
				is.clear();
				
				input.clear();
				ss.reset();

				q++;
				if (q == res_p)
					break;
			}			

			
			
			//输出到 txt
			//std::string  txt_name = name + ".skeleton.txt";
			
			
		//输出eps
		//	if (1)
		//	{
		//		std::string eps_name;
		//		if (0)
		//			eps_name = ".skeleton.eps";
		//		else eps_name = name + ".skeleton.eps";

		//		std::ofstream eps(eps_name.c_str());
		//		if (eps)
		//		{
		//			std::cerr << "Result: " << eps_name << std::endl;
		//			dump_to_eps(input, *ss, eps);
		//		}
		//		else
		//		{
		//			std::cerr << "Could not open result file: " << eps_name << std::endl;
		//		}
		//	}
		//	else
		//	{
		//		std::cerr << "ERROR creating interior straight skeleton" << std::endl;
		//	}

		}
		else
		{
			std::cerr << "Could not open input file: " << name << std::endl;
		}
	}
	else
	{
		std::cerr << "Computes the straight skeleton in the interior of a polygon with holes and draws it in an EPS file." << std::endl
			<< std::endl
			<< "Usage: show_straight_skeleton <intput_file> [output_eps_file]" << std::endl
			<< std::endl
			<< "       intput_file  Text file describing the input polygon with holes." << std::endl
			<< "         (See input_file_format.txt for details)" << std::endl
			<< "       output_file     [default='innput_file.skeleton.eps']" << std::endl;
	}
}