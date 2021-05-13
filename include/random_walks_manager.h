#ifndef __RANDOM_WALKS_MANAGER_H__
#define __RANDOM_WALKS_MANAGER_H__

#include <vector>
#include "logger.h"
#include "random_walk.h"
#include "config.h"
#include "singleton_manager.h"

#define DEFAULT_STEP_LENGTH     3
#define DEFAULT_NB_RANDOM_WALKS 1000
#define DEFAULT_START_POS_X     0.1f*CConfig::WindowWidth
#define DEFAULT_START_POS_Y     0.8f*CConfig::WindowHeight


class CRandomWalksManager : public CSingleton<CRandomWalksManager>, public CScopeLogger
{
     friend class CSingleton<CRandomWalksManager>;

     private :
	std::vector<CRandomWalk*> m_RandomWalks;
	CRandomWalk::TNeighborhood m_Neighborhood;
	point2i m_LeftP, m_RightP, m_UpP, m_DownP;
	point2i m_UpLeftP, m_UpRightP, m_DownLeftP, m_DownRightP;

	CRandomWalksManager();
	~CRandomWalksManager();
	void shuffle();

     public :
	void render( IWindow *window );
	void update( const int iteration );
	void set_start_position( const point2i & p );
	void add_random_walk();
	void remove_random_walk();
	void reinit();
	void show_distribution();

	void increase_step_length();
	void decrease_step_length();

	void increase_left();
	void increase_right();
	void increase_up();
	void increase_down();

	void increase_up_left();
	void increase_up_right();
	void increase_down_left();
	void increase_down_right();
};

#endif //__RANDOM_WALKS_MANAGER_H__
