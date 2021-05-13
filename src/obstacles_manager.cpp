#include "obstacles_manager.h"


CObstaclesManager::CObstaclesManager() : CScopeLogger(__FUNCTION__)
{
	int nb_obs = 7;
	int area_size_x = 600;
	int area_size_y = 600;

	for( int i=1; i<=nb_obs; i++ )
	{
		for( int j=1; j<=i; j++ )
		{
			int x = (CConfig::WindowWidth/2-area_size_x/2+(i-1)*(area_size_x/(nb_obs-1)));
			int y = (CConfig::WindowHeight/2-area_size_y/2+j*(area_size_y/(i+1)));
			m_Obstacles.push_back(new CCircularObstacle(point2i(x, y), 34));
		}
	}

	/*for( int i=1; i<=nb_obs; i++ )
	{
		for( int j=1; j<=nb_obs; j++ )
		{
			int x = (CConfig::WindowWidth/2-area_size_x/2+(i-1)*(area_size_x/(nb_obs-1)));
			int y = (CConfig::WindowHeight/2-area_size_y/2+(j-1)*(area_size_y/(nb_obs-1)));
			m_Obstacles.push_back(new CCircularObstacle(point2i(x, y), 34));
		}
	}*/
}

CObstaclesManager::~CObstaclesManager()
{
	for( uint k=0; k<m_Obstacles.size(); k++ )
		delete m_Obstacles[k], m_Obstacles[k]=NULL;
}

void CObstaclesManager::render( IWindow *window )
{
	for( uint k=0; k<m_Obstacles.size(); k++ )
		m_Obstacles[k]->render(window);
}

void CObstaclesManager::update( const int iteration ){}

bool CObstaclesManager::is_inside( const point2i & p ) const
{
	for( TObstaclesCIt it=m_Obstacles.begin(); it!=m_Obstacles.end(); it++ )
		if( (*it)->is_inside(p) )
			return true;
	return false;
}
