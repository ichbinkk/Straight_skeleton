//#include "Show_straight_skeleton.hpp"
//
//template<class S>
//void dump_to_txt(CGAL::Straight_skeleton_2<S> const& aSkeleton, std::ostream& rOut)
//{
//	typedef typename CGAL::Straight_skeleton_2<S>::Halfedge_const_iterator Halfedge_const_iterator;
//	typedef typename CGAL::Straight_skeleton_2<S>::Halfedge_const_handle   Halfedge_const_handle;
//
//	for (Halfedge_const_iterator hit = aSkeleton.halfedges_begin(); hit != aSkeleton.halfedges_end(); ++hit)
//	{
//		Halfedge_const_handle h = hit;
//
//		int scale = 1;
//
//		if (h->is_bisector() && ((h->id() % 2) == 0) && !h->has_infinite_time() && !h->opposite()->has_infinite_time())
//		{
//
//			rOut << scale * h->vertex()->point().x()
//				<< " "
//				<< scale * h->vertex()->point().y()
//				<< "\n"
//				<< scale * h->opposite()->vertex()->point().x()
//				<< " "
//				<< scale * h->opposite()->vertex()->point().y()
//				<< "\n";
//		}
//	}
//}
