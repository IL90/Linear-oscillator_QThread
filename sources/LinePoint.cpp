#include <iostream>
using std::cout;
using std::endl;

#include "LinePoint.h"
#include <cmath>
#include <cassert>
#include <list>
using std::list;
#include <iterator>
#include <QColor>
#include <QRgb>
class Line;
class Point;

inline double findR(Point *p1,Point *p2) {
	double dx[2];
	for(int c=0;c<2;++c) dx[c] = p1->getX(c) - p2->getX(c);
	return sqrt(dx[0]*dx[0]+dx[1]*dx[1]);
} 

Line::~Line() {
	for(int j=0;j<2;++j) (*_iP_lne[j])->getiL()->erase(_iiL_lne[j]);
	--_count;
}
void Line::setP(const list<Line*>::iterator &iL) {
	for(int j=0;j<2;++j) _iiL_lne[j] = (*_iP_lne[j])->pushLine(iL);
}

void Line::setLength() {_length=findR(*_iP_lne[0],*_iP_lne[1]);}
void Line::paint(QPainter *qp) {
	QColor qc;
	double r,E;
	r=findR(*_iP_lne[0],*_iP_lne[1]);
	E=(_length-r)*fabs(_length-r)/1000;//-1,+1
	if(E>1) E=1;
	else if(E<-1) E=-1;
	qc.setHsvF(0.5 + 0.4*E,fabs(E),1.0);
	qp->setPen(QPen(qc));
	qp->drawLine((*_iP_lne[0])->getX(0),(*_iP_lne[0])->getX(1),(*_iP_lne[1])->getX(0),(*_iP_lne[1])->getX(1));
}
int Line::_count=0;
double Line::_Kl=1;

void Point::eraseLineToPoint() {
	list<Line *>::iterator tmp;
	while(!_iL_pnt.empty()) {
		tmp = *_iL_pnt.begin(); delete *tmp;
		_pL_pnt->erase(tmp);
	}	
}
Point::~Point() {--_count;}
list< list<Line*>::iterator >::iterator Point::pushLine(const list<Line*>::iterator &iL) {
	_iL_pnt.push_back(iL);
	list< list<Line*>::iterator >::iterator iter_last;
	iter_last=_iL_pnt.end(); --iter_last;
	return iter_last;
}
list<Line*> *Point::_pL_pnt=0;
void Point::setpL(list<Line*> *pL) {_pL_pnt=pL;}
int Point::_count=0;
double lPoint::_Kl=0.1;
double sPoint::_Ks=0.02;
