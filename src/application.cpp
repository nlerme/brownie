#include <iostream>
#include "config.h"
#include "random_walks_manager.h"
#include "obstacles_manager.h"
#include "application.h"
#include "obstacle.h"

using std::cout;
using std::cerr;
using std::endl;


CApplication::CApplication() : CScopeLogger(__FUNCTION__), m_Iteration(0)
{
	// Help on keys
	std::cout << "[ Keys / mouse gestures ]\n";
	std::cout << "-------------------------\n";
	std::cout << "key s       -> start / stop simulation\n";
	std::cout << "key f       -> windowed / fullscreen mode\n";
	std::cout << "key r       -> restart\n";
	std::cout << "keys w/x    -> increase/decrease the number of random walks\n";
	std::cout << "keys a/z    -> increase/decrease the step length\n";
	std::cout << "key 1       -> increase probability to go to the down left corner\n";
	std::cout << "key 2       -> increase probability to go down\n";
	std::cout << "key 3       -> increase probability to go to the down right corner\n";
	std::cout << "key 4       -> increase probability to go to the left\n";
	std::cout << "key 6       -> increase probability to go to the right\n";
	std::cout << "key 7       -> increase probability to go to the upper left corner\n";
	std::cout << "key 8       -> increase probability to go to the up\n";
	std::cout << "key 9       -> increase probability to go to the upper right corner\n";
	std::cout << "key g       -> show distribution\n";
	std::cout << "key esc     -> quit\n";
	std::cout << "left button -> set location of random walks\n\n";

	pause();
}

CApplication::~CApplication(){}

void CApplication::begin()
{
	window()->clear(CConfig::BackgroundColor);
}

void CApplication::mouse_motion( const int x, const int y ){}

void CApplication::mouse_button_up( const int x, const int y, const EMouseButton & button ){}

void CApplication::mouse_button_down( const int x, const int y, const EMouseButton & button )
{
	if( button == MOUSE_BUTTON_LEFT )
	{
		//window()->clear(color4f(color3f::white, 1.0f));
		CRandomWalksManager::instance()->set_start_position(point2i(x, y));
	}
}

void CApplication::key_down( const int key )
{
	switch( key )
	{
		case SDLK_ESCAPE :
			quit();
			break;

		case 'f' :
			window()->toggle_fullscreen();
			break;

		case 's' :
			pause();
			break;

		case 'r' :
			window()->clear(CConfig::BackgroundColor);
			CRandomWalksManager::instance()->reinit();
			m_Iteration = 0;
			break;

		case 'g' :
			CRandomWalksManager::instance()->show_distribution();
			break;

		case 'w' :
			CRandomWalksManager::instance()->add_random_walk();
			break;

		case 'x' :
			CRandomWalksManager::instance()->remove_random_walk();
			break;

		case 'a' :
			CRandomWalksManager::instance()->increase_step_length();
			break;

		case 'z' :
			CRandomWalksManager::instance()->decrease_step_length();
			break;

		case SDLK_KP4 :
			CRandomWalksManager::instance()->increase_left();
			break;

		case SDLK_KP6 :
			CRandomWalksManager::instance()->increase_right();
			break;

		case SDLK_KP8 :
			CRandomWalksManager::instance()->increase_up();
			break;

		case SDLK_KP2 :
			CRandomWalksManager::instance()->increase_down();
			break;

		case SDLK_KP1 :
			CRandomWalksManager::instance()->increase_down_left();
			break;

		case SDLK_KP3 :
			CRandomWalksManager::instance()->increase_down_right();
			break;

		case SDLK_KP7 :
			CRandomWalksManager::instance()->increase_up_left();
			break;

		case SDLK_KP9 :
			CRandomWalksManager::instance()->increase_up_right();
			break;
	}
}

void CApplication::key_up( const int key ){}

void CApplication::render() const
{
	CRandomWalksManager::instance()->render(window());
	CObstaclesManager::instance()->render(window());
}

void CApplication::update()
{
	CRandomWalksManager::instance()->update(m_Iteration);
	CObstaclesManager::instance()->update(m_Iteration++);
}

void CApplication::end(){}
