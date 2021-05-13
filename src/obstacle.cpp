#include "obstacle.h"


//--------------------------------------------------------------------------------------------------
IObstacle::IObstacle(){}

IObstacle::~IObstacle(){}

//--------------------------------------------------------------------------------------------------
CCircularObstacle::CCircularObstacle( const point2i & c, const int r ) : m_Center(c), m_Radius(r){}

bool CCircularObstacle::is_inside( const point2i & p ) const
{
	return (squared_distance(p, m_Center) <= sq(m_Radius));
}

void CCircularObstacle::render( IWindow *window ) const
{
	window->fill_circle(m_Center.x, m_Center.y, m_Radius, color4f(color3f::black, 1.0f));
}

void CCircularObstacle::move( const point2i & p )
{
	m_Center.x += p.x;
	m_Center.y += p.y;
}

//--------------------------------------------------------------------------------------------------
CSquareObstacle::CSquareObstacle( const point2i & ulc, const int w, const int h ) : m_UpperLeftCorner(ulc), m_Width(w), m_Height(h){}

bool CSquareObstacle::is_inside( const point2i & p ) const
{
	return (is_between(p.x, m_UpperLeftCorner.x, m_UpperLeftCorner.x+m_Width) && 
		is_between(p.y, m_UpperLeftCorner.y, m_UpperLeftCorner.y+m_Height));
}

void CSquareObstacle::render( IWindow *window ) const
{
	window->fill_rectangle(m_UpperLeftCorner.x, m_UpperLeftCorner.y, m_Width, m_Height, color4f(color3f::black, 1.0f));
}

void CSquareObstacle::move( const point2i & p )
{
	m_UpperLeftCorner.x += p.x;
	m_UpperLeftCorner.y += p.y;
}
