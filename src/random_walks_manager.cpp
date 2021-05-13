#include "random_walks_manager.h"


CRandomWalksManager::CRandomWalksManager() : CScopeLogger(__FUNCTION__)
{
	m_Neighborhood.insert(std::make_pair( (m_LeftP = point2i(-1,  0)), 2.0f));
	m_Neighborhood.insert(std::make_pair((m_RightP = point2i(+1,  0)), 10.0f));
	m_Neighborhood.insert(std::make_pair(   (m_UpP = point2i( 0, -1)), 10.0f));
	m_Neighborhood.insert(std::make_pair( (m_DownP = point2i( 0, +1)), 1.0f));

	m_Neighborhood.insert(std::make_pair(   (m_UpLeftP = point2i(-1, -1)), 3.0f));
	m_Neighborhood.insert(std::make_pair(  (m_UpRightP = point2i(+1, -1)), 7.0f));
	m_Neighborhood.insert(std::make_pair( (m_DownLeftP = point2i(-1, +1)), 3.0f));
	m_Neighborhood.insert(std::make_pair((m_DownRightP = point2i(+1, +1)), 7.0f));

	for( uint k=0; k<DEFAULT_NB_RANDOM_WALKS; k++ )
		m_RandomWalks.push_back(new CRandomWalk(point2i(DEFAULT_START_POS_X, DEFAULT_START_POS_Y), color4f::random(), DEFAULT_STEP_LENGTH, m_Neighborhood));
}

CRandomWalksManager::~CRandomWalksManager()
{
	for( uint k=0; k<m_RandomWalks.size(); k++ )
		delete m_RandomWalks[k], m_RandomWalks[k]=NULL;
}

void CRandomWalksManager::shuffle()
{
	int i(0), j, size(m_Neighborhood.size());
	std::vector<point2i> keys(size);
	float wi, wj;

	for( CRandomWalk::TNeighborhoodCIt it=m_Neighborhood.begin(); it!=m_Neighborhood.end(); it++ )
		keys[i++] = it->first;

	for( i=(size-1); i>=1; i-- )
	{
		j = uniform<int>(0, i+1);
		wi = m_Neighborhood[keys[i]];
		wj = m_Neighborhood[keys[j]];
		m_Neighborhood[keys[i]] = wj;
		m_Neighborhood[keys[j]] = wi;
	}

	for( uint k=0; k<m_RandomWalks.size(); k++ )
		m_RandomWalks[k]->set_neighborhood(m_Neighborhood);
}

void CRandomWalksManager::render( IWindow *window )
{
	for( uint k=0; k<m_RandomWalks.size(); k++ )
		m_RandomWalks[k]->render(window);

	window->draw_circle(m_RandomWalks[0]->start_position().x, m_RandomWalks[0]->start_position().y, 20, color4f(color3f::black, 0.5f));
	window->draw_circle(m_RandomWalks[0]->start_position().x, m_RandomWalks[0]->start_position().y, 23, color4f(color3f::black, 0.5f));
	window->set_pixel(m_RandomWalks[0]->start_position().x, m_RandomWalks[0]->start_position().y, color4f(color3f::black, 0.5f));
}

void CRandomWalksManager::update( const int iteration )
{
	//if( iteration % 200 == 0 )
	//	shuffle();

	for( uint k=0; k<m_RandomWalks.size(); k++ )
		m_RandomWalks[k]->update(iteration);
}

void CRandomWalksManager::set_start_position( const point2i & p )
{
	for( uint k=0; k<m_RandomWalks.size(); k++ )
	{
		m_RandomWalks[k]->start_position(p);
		m_RandomWalks[k]->reinit();
	}
}

void CRandomWalksManager::add_random_walk()
{
	m_RandomWalks.push_back(new CRandomWalk(m_RandomWalks[0]->start_position(), color4f::random(), m_RandomWalks[0]->step_length(), m_Neighborhood));
}

void CRandomWalksManager::remove_random_walk()
{
	if( m_RandomWalks.size() > 1 )
	{
		delete m_RandomWalks[m_RandomWalks.size()-1];
		m_RandomWalks.pop_back();
	}
}

void CRandomWalksManager::reinit()
{
	for( uint k=0; k<m_RandomWalks.size(); k++ )
		m_RandomWalks[k]->reinit();
}

void CRandomWalksManager::show_distribution()
{
	float sum(0.0f);

	std::cout << "\n[ distribution of probabilities ]\n";

	for( CRandomWalk::TNeighborhoodCIt it=m_Neighborhood.begin(); it!=m_Neighborhood.end(); it++ )
		sum += it->second;

	for( CRandomWalk::TNeighborhoodCIt it=m_Neighborhood.begin(); it!=m_Neighborhood.end(); it++ )
		std::cout << it->first << " -> " << (it->second/sum) << '\n';

	std::cout << '\n';
}

void CRandomWalksManager::increase_step_length()
{
	for( uint k=0; k<m_RandomWalks.size(); k++ )
		m_RandomWalks[k]->step_length(m_RandomWalks[k]->step_length()+1);
}

void CRandomWalksManager::decrease_step_length()
{
	for( uint k=0; k<m_RandomWalks.size(); k++ )
		m_RandomWalks[k]->step_length(m_RandomWalks[k]->step_length()-1);
}

void CRandomWalksManager::increase_left()
{
	m_Neighborhood[m_LeftP]++;

	for( uint k=0; k<m_RandomWalks.size(); k++ )
		m_RandomWalks[k]->set_neighborhood(m_Neighborhood);
}

void CRandomWalksManager::increase_right()
{
	m_Neighborhood[m_RightP]++;

	for( uint k=0; k<m_RandomWalks.size(); k++ )
		m_RandomWalks[k]->set_neighborhood(m_Neighborhood);
}

void CRandomWalksManager::increase_up()
{
	m_Neighborhood[m_UpP]++;

	for( uint k=0; k<m_RandomWalks.size(); k++ )
		m_RandomWalks[k]->set_neighborhood(m_Neighborhood);
}

void CRandomWalksManager::increase_down()
{
	m_Neighborhood[m_DownP]++;

	for( uint k=0; k<m_RandomWalks.size(); k++ )
		m_RandomWalks[k]->set_neighborhood(m_Neighborhood);
}

void CRandomWalksManager::increase_up_left()
{
	m_Neighborhood[m_UpLeftP]++;

	for( uint k=0; k<m_RandomWalks.size(); k++ )
		m_RandomWalks[k]->set_neighborhood(m_Neighborhood);
}

void CRandomWalksManager::increase_up_right()
{
	m_Neighborhood[m_UpRightP]++;

	for( uint k=0; k<m_RandomWalks.size(); k++ )
		m_RandomWalks[k]->set_neighborhood(m_Neighborhood);
}

void CRandomWalksManager::increase_down_left()
{
	m_Neighborhood[m_DownLeftP]++;

	for( uint k=0; k<m_RandomWalks.size(); k++ )
		m_RandomWalks[k]->set_neighborhood(m_Neighborhood);
}

void CRandomWalksManager::increase_down_right()
{
	m_Neighborhood[m_DownRightP]++;

	for( uint k=0; k<m_RandomWalks.size(); k++ )
		m_RandomWalks[k]->set_neighborhood(m_Neighborhood);
}
