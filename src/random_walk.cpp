#include "random_walk.h"


void CRandomWalk::normalize_distribution()
{
	float sum(0.0f);


	for( TNeighborhoodCIt it=m_Neighborhood.begin(); it!=m_Neighborhood.end(); it++ )
		sum += it->second;

	for( TNeighborhoodIt it=m_Neighborhood.begin(); it!=m_Neighborhood.end(); it++ )
		it->second /= sum;
}

CRandomWalk::CRandomWalk( const point2i & start_pos, 
			  const color4f & color, 
			  const int step_length, 
			  const TNeighborhood & neighborhood ) : m_StartPos(start_pos), 
								 m_PreviousPos(start_pos), 
								 m_CurrentPos(start_pos), 
								 m_Color(color), 
								 m_StepLength(step_length)
{
	set_neighborhood(neighborhood);
}

void CRandomWalk::step_length( const int sl )
{
	m_StepLength = std::max(sl, 1);
}

const int & CRandomWalk::step_length() const
{
	return m_StepLength;
}

void CRandomWalk::start_position( const point2i & sp )
{
	m_StartPos = sp;
}

const point2i & CRandomWalk::start_position() const
{
	return m_StartPos;
}

void CRandomWalk::reinit()
{
	m_PreviousPos = m_StartPos;
	m_CurrentPos  = m_StartPos;
}

void CRandomWalk::set_neighborhood( const TNeighborhood & n )
{
	m_Neighborhood = n;
	normalize_distribution();
}

point2i CRandomWalk::get_point() const
{
	TNeighborhoodCIt it(m_Neighborhood.begin());
	float p(uniform<float>());
	float c(0.0f);


	while( it != m_Neighborhood.end() )
	{
		if( p >= c && p < (c+it->second) )
			break;

		c += it->second;
		it++;
	}

	return it->first;
}

void CRandomWalk::update( const int iteration )
{
	point2i p, tmp;

	m_PreviousPos = m_CurrentPos;

	do
	{
		p     = get_point();
		tmp.x = m_CurrentPos.x+p.x*m_StepLength;
		tmp.y = m_CurrentPos.y+p.y*m_StepLength;
	}
	while( p == m_PreviousPos || CObstaclesManager::instance()->is_inside(tmp) );

	m_CurrentPos = tmp;
}

void CRandomWalk::render( IWindow *window ) const
{
	if( window->is_inside(m_CurrentPos.x, m_CurrentPos.y) )
		window->draw_line(m_PreviousPos.x, m_PreviousPos.y, m_CurrentPos.x, m_CurrentPos.y, m_Color);
}
