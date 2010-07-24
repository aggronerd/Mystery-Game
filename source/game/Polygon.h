/**
 * @file Polygon.h
 *
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef POLYGON_H_
#define POLYGON_H_

#include <list>
#include <ClanLib/core.h>
#include <ClanLib/display.h>

/**
 * Class for simplified storage and rendering of
 * polygons.
 */
class Polygon
{

	public:
		Polygon();
		virtual	~Polygon() {};
		virtual void draw(CL_GraphicContext);
		virtual void add_point(CL_Pointf);
		virtual void set_line_color(CL_Colorf);
		virtual CL_Colorf get_line_color(void);

	protected:
		std::list<CL_Pointf> _points;
		CL_Colorf _line_color;

};

#endif /* POLYGON_H_ */
