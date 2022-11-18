#include "GrayLevelImage2D.hpp"

GrayLevelImage2D::Iterator::Iterator( GrayLevelImage2D& image, int x, int y )
: Container::iterator( image.m_data.begin() + image.index( x, y ) ) {}

GrayLevelImage2D::Iterator GrayLevelImage2D::start(int x, int y) {
	return Iterator(*this, x, y);
}

GrayLevelImage2D::Iterator GrayLevelImage2D::begin() {
	return start(0,0);
}

GrayLevelImage2D::Iterator GrayLevelImage2D::end() {
	return start(m_width-1, m_height-1);
}

std::string readline(std::istream &input) {
	std::string str;
	do {
		std::getline( input, str );
	} while (str != ""  && str[0]=='#');
	return str;
}

bool GrayLevelImage2D::importPGM(std::istream &input) {
	if ( ! input.good() ) return false;
	std::string format = readline(input);
	std::cout << "TEST" << std::endl;
	std::string line = readline(input);
	std::string delim = " ";
	m_width = std::stoi(line.substr(0, line.find(delim)));
	line.erase(0, line.find(delim) + delim.length());
	m_height = std::stoi(line);
	std::cout << m_width << " " << m_height << " " << format << std::endl;
	std::cout << readline(input) << std::endl; // grayscale range
	fill(0);
	if (format == "P5") {
		input >> std::noskipws;
		unsigned char v;
		for ( Iterator it = begin(), itE = end(); it != itE; ++it ) {
			input >> v;
			*it = v;
		}
	} else {
		input >> std::skipws;
		int v;
		for ( Iterator it = begin(), itE = end(); it != itE; ++it ) {
			input >> v;
			*it = v;
		}
	}
	return true;
}

bool GrayLevelImage2D::exportPGM(std::ostream &output, bool ascii) {
	output << (ascii ? "P2" : "P5") << std::endl;
	output << m_width << ' ' << m_height << std::endl;
	output << "255" << std::endl;
	if (ascii) {
		for ( Iterator it = begin(), itE = end(); it != itE; ++it ) {
			output << (int)*it << ' ';
		}
	} else {
		output << std::noskipws;
		for ( Iterator it = begin(), itE = end(); it != itE; ++it ) {
			output << *it;
		}
	}
	return true;
}