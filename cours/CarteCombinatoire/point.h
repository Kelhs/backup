#ifndef POINT_H
#define POINT_H

class Point
{

public:
	// constructeurs
	Point() : d_x{0},d_y{0},d_z{0} {}
	//Point(double x, double y) : d_x{x},d_y{y} {}

    Point(double d, double d1, double d2): d_x{d},d_y{d1},d_z{d2} {};

// accesseurs
    double x() const {return d_x;}
    double y() const {return d_y;}
    double z() const {return d_z;}


    // renvoie 1, -1 ou 0 selon que le point auquel la m�thode est appliqu�e est
	// � gauche de, � droite de, ou sur la droite (ab) orient�e de a vers b.
	int aGauche(const Point &a, const Point &b) const;


    int dansCercle(const Point &a, const Point &b, const Point &c) const;

private:
    // coordonn�es
	double d_x, d_y, d_z;

};

#endif
