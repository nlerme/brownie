#ifndef __RANDOM_WALK_H__
#define __RANDOM_WALK_H__

#include "window.h"
#include "geometry.h"
#include "obstacles_manager.h"
#include <map>


struct comparator
{
	bool operator () ( const point2i & p1, const point2i & p2 ) const
	{
		return (p1.x<p2.x || (p1.x==p2.x && p1.y<p2.y));
	}
};

class CRandomWalk
{
     public :
	typedef std::map<point2i, float, comparator> TNeighborhood;
	typedef TNeighborhood::iterator              TNeighborhoodIt;
	typedef TNeighborhood::const_iterator        TNeighborhoodCIt;

     private :
	point2i m_StartPos;
	point2i m_PreviousPos;
	point2i m_CurrentPos;
	color4f m_Color;
	int m_StepLength;
	TNeighborhood m_Neighborhood;

	void normalize_distribution();

     public :
	CRandomWalk( const point2i & start_pos, 
		     const color4f & color, 
		     const int step_length, 
		     const TNeighborhood & neighborhood );
	void step_length( const int sl );
	const int & step_length() const;
	void start_position( const point2i & sp );
	const point2i & start_position() const;
	void reinit();
	void set_neighborhood( const TNeighborhood & n );
	point2i get_point() const;
	void update( const int iteration );
	void render( IWindow *window ) const;
};

#endif //__RANDOM_WALK_H__
