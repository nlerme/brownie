#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "window.h"
#include "geometry.h"
#include "utils.h"


struct IObstacle
{
	IObstacle();
	virtual ~IObstacle();
	virtual bool is_inside( const point2i & p ) const = 0;
	virtual void render( IWindow *window ) const = 0;
	virtual void move( const point2i & p ) = 0;
};

class CCircularObstacle : public IObstacle
{
     private :
	point2i m_Center;
	int m_Radius;

     public :
	CCircularObstacle( const point2i & c, const int r );
	virtual bool is_inside( const point2i & p ) const;
	virtual void render( IWindow *window ) const;
	virtual void move( const point2i & p );
};

struct CSquareObstacle : public IObstacle
{
     private :
	point2i m_UpperLeftCorner;
	int m_Width, m_Height;

     public :
	CSquareObstacle( const point2i & ulc, const int w, const int h );
	virtual bool is_inside( const point2i & p ) const;
	virtual void render( IWindow *window ) const;
	virtual void move( const point2i & p );
};

#endif //__OBSTACLE_H__
