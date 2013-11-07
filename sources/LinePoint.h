#ifndef LINEPOINT_H
#define LINEPOINT_H
#include <QPainter>

#include <iostream>
using std::cout;
using std::endl;

#include <list>
using std::list;
#include <iterator>
#include <cassert>
class Line;
class Point;
	class lPoint;
	class sPoint;
	class nPoint;
	class fPoint;

class Line {
	public:
		Line() {++_count;}
		Line(const list<Point*>::iterator &iP_lne0,const list<Point*>::iterator &iP_lne1) {
			setPoints(iP_lne0,iP_lne1); ++_count;
		}
		~Line();
		void setPoints(const list<Point*>::iterator &iP_lne0,const list<Point*>::iterator &iP_lne1) {
			_iP_lne[0]=iP_lne0; _iP_lne[1]=iP_lne1; setLength();
		}
		list<Point*>::iterator getPoint(int i) {assert(i==0||i==1); return _iP_lne[i];}
		int getCount() const {return _count;}
		void setP(const list<Line*>::iterator &self);
		void paint(QPainter *qp);
		double getLength() const {assert(_length>0); return _length;}
		void setiiL(const list< list<Line*>::iterator >::iterator &iiL,Point *cpy) {
			if((*_iP_lne[0])==cpy) _iiL_lne[0]=iiL;
			else if((*_iP_lne[1])==cpy) _iiL_lne[1]=iiL;
			else assert(0);
		}
		static double getKl() {return _Kl;}
		list<list<Line *>::iterator >::iterator getiiL(int j) const {return _iiL_lne[j];}
	private:
		void setLength();
		list<Point*>::iterator _iP_lne[2];//итераторы списка P точек на концах линии
		list< list<Line*>::iterator >::iterator _iiL_lne[2];//итераторы списка итераторов _iL_pnt для этих точек, указывающие на эту линию
		double _length;//of the undeformed line 
		static double _Kl;//elastic coefficient
		static int _count;
};

class Point {
	public:
        Point(const double &mass,const double x[]) {_x[0]=x[0]; _x[1]=x[1]; initialize(mass);}
		void initialize(const double &mass) {_mass=mass; if(mass<=0) assert(0); _v[0]=_v[1]=0; ++_count;}
		Point(Point &cpy) {
			for(int c=0;c<2;++c) {
				_x[c] = cpy.getX(c);
				_v[c] = cpy.getV(c);
			}
			_mass = cpy.getMass();
			_J=cpy.getJ();
			_iL_pnt = cpy.getcopyiL();
			list< list<Line*>::iterator >::iterator it;
			for(it=_iL_pnt.begin(); it!=_iL_pnt.end();++it) (**it)->setiiL(it,&cpy);
			++_count;
		}
		void eraseLineToPoint();
		virtual ~Point();
		double getX(const int &c) const { assert(c==0||c==1); return _x[c];}
		double getV(const int &c) const { assert(c==0||c==1); return _v[c];}
		void setX(const double x[]) {_x[0]=x[0]; _x[1]=x[1];}
		void setX(const double &x0,const double &x1) {_x[0]=x0; _x[1]=x1;}
		void setV(const double v[]) {_v[0]=v[0]; _v[1]=v[1];}
		void setV(const double &v0,const double &v1) {_v[0]=v0; _v[1]=v1;}
		int getCount() const {return _count;}
		int getJ() const {return _J;}
		void setJ(const int &J) {assert(J>=0); _J=J;}
		virtual void paint(QPainter *qp) {
			qp->setPen(QPen(Qt::gray));
		}
		list< list<Line*>::iterator >::iterator pushLine(const list<Line*>::iterator &iL);
		list< list<Line*>::iterator > *getiL() {return &_iL_pnt;}
		list< list<Line*>::iterator > getcopyiL() const {return _iL_pnt;}
		double getMass() const {return _mass;}
		static void setpL(list<Line*> *pL);
	protected:
		double _x[2];//coords
		double _v[2];//velocity
		double _mass;
		int _J;//index
		list< list<Line*>::iterator > _iL_pnt;//список итераторов списка L линий, соединенных с этой точкой 
		static int _count;
		static list<Line*> *_pL_pnt;//pointer to L
};


class lPoint: public Point {
	public:
		lPoint(const double &mass,const double x[]) : Point(mass,x) {}
		lPoint(Point &cpy) : Point(cpy) {}
		~lPoint() {}
		void paint(QPainter *qp) {
			Point::paint(qp);
			qp->setBrush(QBrush(Qt::red));
			qp->drawEllipse(_x[0]-5,_x[1]-5,10,10);
		}
		static double getKl() {return _Kl;}//linear coefficient
	private:
		static double _Kl;
};

class sPoint: public Point {
	public:
		sPoint(const double &mass,const double x[]) : Point(mass,x) {}
		sPoint(Point &cpy) : Point(cpy) {}
		~sPoint() {}
		void paint(QPainter *qp) {
			Point::paint(qp);
			qp->setBrush(QBrush(Qt::green));
			qp->drawEllipse(_x[0]-4,_x[1]-4,8,8);
		}
		static double getKs() {return _Ks;}//quadratic coefficient
	private:
		static double _Ks;
};
class fPoint: public Point {
	public:
		fPoint(const double &mass,const double x[]) : Point(mass,x) {}
		fPoint(Point &cpy) : Point(cpy) {}
		~fPoint() {}
		void paint(QPainter *qp) {
			Point::paint(qp);
			qp->setBrush(QBrush(Qt::blue));
			qp->drawEllipse(_x[0]-3,_x[1]-3,6,6);
		}
	private:
};
class nPoint: public Point {
	public:
		nPoint(const double &mass,const double x[]) : Point(mass,x) {}
		nPoint(Point &cpy) : Point(cpy) {}
		~nPoint() {}
		void paint(QPainter *qp) {
			Point::paint(qp);
			qp->setBrush(QBrush(Qt::white));
			qp->drawEllipse(_x[0]-3,_x[1]-3,6,6);		
		}
	private:
};
#endif
