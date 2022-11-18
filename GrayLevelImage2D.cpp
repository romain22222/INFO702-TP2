#include "GrayLevelImage2D.hpp"

GrayLevelImage2D::GrayLevelImage2D()
: m_width(0), m_height(0), m_data(Container()) {}

GrayLevelImage2D::GrayLevelImage2D(int w, int h, GrayLevel g)
: m_width(w), m_height(h), m_data(Container(w*h, g)) {}

int GrayLevelImage2D::index(int x, int y) const {
	return y*m_width+x;
}

GrayLevel &GrayLevelImage2D::at(int i, int j) {
	return m_data.at(index(i,j));
}

GrayLevel GrayLevelImage2D::at(int i, int j) const {
	return m_data.at(index(i,j));
}