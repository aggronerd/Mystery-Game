/**
 * @file Polygon.cpp
 *
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "Polygon.h"

/**
 *
 */
Polygon::Polygon()
{
	_line_color = CL_Colorf(0.0f,0.0f,0.0f,1.0f);
}

/**
 * Draws the polygon on the graphics context.
 *
 * @param gc Graphics context to draw the polygon on.
 */
void Polygon::draw(CL_GraphicContext gc)
{

	//Only draw if more than one point exists.
	if(_points.size() > 1)
	{

		//CL_Vec4f green_color(1.0f, 1.0f, 1.0f, 1.0f);
		CL_Vec2i points_array[_points.size()];

		std::list<CL_Pointf>::iterator it_point;
		int n = 0;
		for(it_point = _points.begin(); it_point != _points.end(); ++it_point)
		{
			points_array[n] = static_cast<CL_Vec2i>(*(it_point));
			n++;
		}

		CL_PrimitivesArray poly(gc);
		poly.set_attributes(0, points_array);
		poly.set_attribute(1, _line_color);

		//scene->get_world()->get_gc()->get_polygon_rasterizer().set_face_fill_mode_front(cl_fill_polygon);

		gc.set_program_object(cl_program_color_only);
		gc.draw_primitives(cl_line_loop,n,poly);
		gc.reset_program_object();

	}

}

/**
 * Adds a point to the end of the polygon.
 *
 * @param point Point to add.
 */
void Polygon::add_point(CL_Pointf point)
{
	_points.push_back(point);
}

/**
 * Sets the colour of the line.
 *
 * @param colour
 */
void Polygon::set_line_color(CL_Colorf color)
{
	_line_color = color;
}

/**
 * Returns the line colour of the polygon.
 *
 * @return Polygon line colour.
 */
CL_Colorf Polygon::get_line_color()
{
	return(_line_color);
}
