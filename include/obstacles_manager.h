#ifndef __OBSTACLES_MANAGER_H__
#define __OBSTACLES_MANAGER_H__

#include <vector>
#include <cmath>
#include "logger.h"
#include "singleton_manager.h"
#include "obstacle.h"
#include "config.h"
#include "window.h"
#include "geometry.h"


class CObstaclesManager : public CSingleton<CObstaclesManager>, public CScopeLogger
{
     friend class CSingleton<CObstaclesManager>;

     public :
	typedef std::vector<IObstacle*>    TObstacles;
	typedef TObstacles::iterator       TObstaclesIt;
	typedef TObstacles::const_iterator TObstaclesCIt;

     private :
	std::vector<IObstacle*> m_Obstacles;

	CObstaclesManager();
	~CObstaclesManager();

     public :
	void render( IWindow *window );
	void update( const int iteration );
	bool is_inside( const point2i & p ) const;
};

#endif //__OBSTACLES_MANAGER_H__
