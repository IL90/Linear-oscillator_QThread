#include <QApplication>
#include <QWidget>
#include <QFrame>
#include <iostream>
using std::cout;
using std::endl;

#include <cmath>
#include "PanelDraw.h"
#include "LinePoint.h"

#include <QPaintEvent>
#include <QPainter>
#include <list>
using std::list;
#include <iterator>
#include <QMouseEvent>
#include <QCursor>
#include <QTimer>
#include <typeinfo>
#include <QPalette>
#include <QResizeEvent>
#include <QPalette>
#include <QThread>
#include <QWaitCondition>
class PanelDraw;

PanelDraw::PanelDraw(QWidget *wgt) : QFrame(wgt),dt(0.5),RCUR(5.0),CntTh(QThread::idealThreadCount()),isEmptyX(1) {
	setFrameStyle(QFrame::WinPanel|QFrame::Raised);
	QPalette pal;
	pal.setColor(this->backgroundRole(),Qt::black);
	this->setPalette(pal);
	this->setAutoFillBackground(true);	
	flagTools=1; press=-1;
	this->setCursor(Qt::PointingHandCursor); 
	Point::setpL(&L);
	try { ptimer = new QTimer(this);
	} catch(std::bad_alloc) {assert(0);}
	connect(ptimer,SIGNAL(timeout()),SLOT(slotNextStep()));	
	MyThread::setParent(this);
	MyThread::setK(0);
	th = new MyThread[CntTh];

	connect(this,SIGNAL(sgnChangePCount()),SLOT(slotChangePCount()));

	//create grid
	const int nx=30,ny=30;
	list<Line*>::iterator iter_last;
	list<Point*>::iterator ar[nx];
	list<Point*>::iterator tmp,tmp2;
	int i,j;
	double X[2];
	for(j=0;j<ny;++j) {
		X[1]=20+j*20;
		for(i=0;i<nx;++i) {
			X[0]=20+i*20;
			try {
			if(i==0||i==nx-1||j==0||j==ny-1) P.push_back(new fPoint(1,X));
			else P.push_back(new nPoint(1,X));
			if(i==0) {tmp=P.end(); --tmp;}
			else {
				tmp2=P.end(); --tmp2;
				L.push_back(new Line(tmp,tmp2));
				iter_last=L.end();
				L.back()->setP(--iter_last);
				tmp=tmp2;
			}
			if(j==0) ar[i]=tmp;
			else {
				L.push_back(new Line(ar[i],tmp));
				iter_last=L.end();
				L.back()->setP(--iter_last);
				ar[i]=tmp;
			}
			} catch(std::bad_alloc) {assert(0);}
			assert(!check());
		}
	}
	emit sgnChangePCount();
	curP1=curP2=P.begin();
}

void PanelDraw::allocX() {
	int c,j,J;
	list<Point*>::iterator iP;
	if(!isEmptyX) freeX();
	N=P.size();
	if(N) {
		try {
		for(c=0;c<4;++c) {
			x[c] = new double [N];//x[0]=x, x[1]=y, x[2]=vx, x[3]=vy
			delta[c] = new double [N];
			for(j=0;j<4;++j) f[j][c] = new double [N];
		}
		mass = new double [N];
		} catch(std::bad_alloc) {assert(0);}
		for(iP=P.begin(),J=0;iP!=P.end();++iP,++J) {
			(*iP)->setJ(J);
			mass[J]=(*iP)->getMass();
			for(c=0;c<4;++c) delta[c][J]=0;
		}

		for(j=0;j<CntTh;++j) th[j].clearCrp();
		for(iP=P.begin(),j=0; iP!=P.end(); ++iP,++j) {
			if(j>=CntTh) j-=CntTh;
			th[j].pushPnt(iP);
		}
		isEmptyX=0;
	}
}
void PanelDraw::freeX() {
	int c,j;
	if(!isEmptyX) {
		for(c=0;c<4;++c) {
			delete[] x[c];
			delete[] delta[c];
			for(j=0;j<4;++j) delete[] f[j][c];
		}
		delete[] mass;
		isEmptyX=1;
	}
}
PanelDraw::~PanelDraw() {
	list<Point*>::iterator iP;
	list<Line*>::iterator iL;
	while(!L.empty()) {iL=L.begin(); delete *iL; L.erase(iL);}	
	while(!P.empty()) {iP=P.begin(); delete *iP; P.erase(iP);}
	SelP.clear();
	freeX();
}
void PanelDraw::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing,true);
	list<Point*>::iterator iP;
	list<Line*>::iterator iL;
	list< list<Point*>::iterator >::iterator iiP;
	int c;
	double x[2];
	for(iP=P.begin();iP!=P.end();++iP) (*iP)->paint(&painter);
	for(iL=L.begin();iL!=L.end();++iL) (*iL)->paint(&painter);
	
	if(press==3) {//creating of line
		painter.setPen(QPen(Qt::gray)); painter.drawLine((*curP1)->getX(0),(*curP1)->getX(1),mx2[0],mx2[1]);
	}
	if(press==5) {//selecting
		painter.setPen(QPen(Qt::gray,1,Qt::DotLine)); painter.setBrush(Qt::NoBrush);
		painter.drawRect(mx[0],mx[1],mx2[0]-mx[0],mx2[1]-mx[1]);
	}
	//selected points
	painter.setPen(QPen(Qt::gray)); painter.setBrush(Qt::NoBrush);
	for(iiP=SelP.begin();iiP!=SelP.end();++iiP) {
		for(c=0;c<2;++c) x[c]=(**iiP)->getX(c);
		painter.drawRect(x[0]-5,x[1]-5,10,10);
	}
}
bool PanelDraw::findMouseX(list<Point*>::iterator &iP,double mx_[]) {
	int j;
	bool fp=0;
	MyThread::setI(2);
	MyThread::setMx(mx_);
	for(j=0;j<CntTh;++j) th[j].start();

	for(j=0;j<CntTh;++j) {
		th[j].wait();	
	}
	fp=MyThread::findPoint(iP);
	return fp;
}
void PanelDraw::mousePressEvent(QMouseEvent *pe) {
	mx[0]=pe->x(); mx[1]=pe->y();
	if(pe->buttons() & Qt::LeftButton) {
		pressMB=0;//LeftMouseButton
		if(flagTools==0) {//drug point
			list<Point*>::iterator iP;
			if(SelP.empty() || ptimer->isActive()) {
				if(findMouseX(iP,mx)) {
					press=0; 
					curP1=iP;
					(*curP1)->setV(0,0);
				}
			}
			else if(!ptimer->isActive()) {
				list< list<Point*>::iterator >::iterator iiP;
				for(iiP=SelP.begin();iiP!=SelP.end();++iiP) {
					(**iiP)->setV(0,0);
				}
				press=0;
			}
		}
		else if(flagTools==1) {//create nPoint
			press=1;
			try {P.push_back(new nPoint(1,mx));
			} catch(std::bad_alloc) {assert(0);}
			assert(!check());
			emit sgnChangePCount();
			if(!(ptimer->isActive())) update();
		}
		else if(flagTools==2) {//delete Point
			press=2;
			list<Point*>::iterator iP;
			if(SelP.empty()) {
				if(findMouseX(iP,mx)) {
					curP1=iP;
					(*curP1)->eraseLineToPoint();
					delete *curP1;
					P.erase(curP1);
				}
			}
			else {
				list< list<Point*>::iterator >::iterator iiP;
				for(iiP=SelP.begin();iiP!=SelP.end();++iiP) 
				if((fabs(mx[0] - (**iiP)->getX(0))<RCUR) && (fabs(mx[1] - (**iiP)->getX(1))<RCUR)) {
					while(!SelP.empty()) {
						iiP=SelP.begin();
						curP1=(*iiP);
						(*curP1)->eraseLineToPoint();
						delete *curP1;
						P.erase(curP1);
						SelP.erase(iiP);
					}
					break;
				}
			}
			emit sgnChangePCount();

			assert(!check());
			if(!(ptimer->isActive())) update();
		}
		else if(flagTools==3) {//create Line
			list<Point*>::iterator iP;
			if(findMouseX(iP,mx)) {
				curP1=iP; press=3; mx2[0]=mx[0]; mx2[1]=mx[1]; 
			}
		}
		else if(flagTools==4) {//delete Line
			press=4;
			int i,c;
			list<Line*>::iterator iL;
			list<Point*>::iterator pnt[2];
			double x[2][2];
			double d,var[2];
			for(iL=L.begin();iL!=L.end();++iL) {
				for(i=0;i<2;++i) pnt[i]=(*iL)->getPoint(i);
				for(i=0;i<2;++i) for(c=0;c<2;++c) x[i][c]=(*pnt[i])->getX(c);
				if((x[0][0]-RCUR<mx[0]&&mx[0]<x[1][0]+RCUR)||(x[1][0]-RCUR<mx[0]&&mx[0]<x[0][0]+RCUR))
				if((x[0][1]-RCUR<mx[1]&&mx[1]<x[1][1]+RCUR)||(x[1][1]-RCUR<mx[1]&&mx[1]<x[0][1]+RCUR)) {
					for(c=0;c<2;++c) var[c]=x[1][c]-x[0][c];
					d=fabs(var[1]*(x[0][0]-mx[0])-var[0]*(x[0][1]-mx[1]))/sqrt(var[1]*var[1]+var[0]*var[0]);
					if(d<RCUR) {
						delete *iL;
						L.erase(iL);
						break;
					}
				}
			}
			assert(!check());
			update();
		}
		else if(flagTools==5) {//select Points
			press=5;
			mx2[0]=mx[0]; mx2[1]=mx[1];
		}
	}
	else if(pe->buttons() & Qt::RightButton) {
		pressMB=1;
		if(SelP.empty()) {
			list<Point*>::iterator iP;
			if(findMouseX(iP,mx)) {
				replacetype(iP);
			}
		}
		else {
			list<list<Point*>::iterator>::iterator iiP;
			for(iiP=SelP.begin();iiP!=SelP.end();++iiP) {
				replacetype(*iiP);
			}
		}
		assert(!check());
		update();
	}
}
void PanelDraw::mouseReleaseEvent(QMouseEvent* pe) {
	if(pressMB==0) {
		if(press==0||press==3||press==5) {
			if(press==3||press==5) {
				mx2[0]=pe->x(); mx2[1]=pe->y();
				list<Point*>::iterator iP;
				if(press==3) {//create Line
					if(findMouseX(iP,mx2)) {
						curP2=iP;
						if((*curP2)!=(*curP1)) {
							list<Line*>::iterator iter_last;
							try {L.push_back(new Line(curP1,curP2));
							} catch(std::bad_alloc) {assert(0);}
							iter_last=L.end();
							L.back()->setP(--iter_last);
						}
					}
				}
				else if(press==5) {//select Points
					double var;
					int c;
					SelP.clear();
					for(c=0;c<2;++c) if(mx[c]>mx2[c]) {var=mx2[c]; mx2[c]=mx[c]; mx[c]=var;}
					for(iP=P.begin();iP!=P.end();++iP) {
						if(mx[0] < (*iP)->getX(0) && (*iP)->getX(0) < mx2[0])
						if(mx[1] < (*iP)->getX(1) && (*iP)->getX(1) < mx2[1]) {
							SelP.push_back(iP);
						}
					}
				}
			}
			if(!(ptimer->isActive())) update();
		}
		press=-1;
	}
}
void PanelDraw::mouseMoveEvent(QMouseEvent* pe) {
	if(pressMB==0) {
		if(press==0||press==3||press==5) {
			mx2[0]=pe->x(); mx2[1]=pe->y();
			if(press==0) {
				if(SelP.empty() || ptimer->isActive()) {
					(*curP1)->setX(mx2);
				}
				else if(!ptimer->isActive()) {
					double x0[2];
					list< list<Point*>::iterator >::iterator iiP;
					for(iiP=SelP.begin();iiP!=SelP.end();++iiP) {
						for(int c=0;c<2;++c) {x0[c]=(**iiP)->getX(c) + (mx2[c]-mx[c]); }
						(**iiP)->setX(x0);
					}
					for(int c=0;c<2;++c) mx[c]=mx2[c];
				}
			}
			if(!(ptimer->isActive())) update();
		}
	}
}
void PanelDraw::replacetype(list<Point*>::iterator it) {
    Point *tmp=0;
	try {
		if(typeid(**it)==typeid(nPoint))      tmp = new lPoint(**it);
		else if(typeid(**it)==typeid(lPoint)) tmp = new sPoint(**it);
		else if(typeid(**it)==typeid(sPoint)) tmp = new fPoint(**it);
		else if(typeid(**it)==typeid(fPoint)) tmp = new nPoint(**it);
		else assert(0);
	} 
	catch(std::bad_alloc) {assert(0);}
	delete *it; *it = tmp;
}
void PanelDraw::slotFlagTools(int i) {
	flagTools=i;
	if(i==1||i==3) setCursor(Qt::PointingHandCursor);
	else setCursor(Qt::ArrowCursor);
}
void PanelDraw::slotPlayPD() {
	if(ptimer->isActive()) ptimer->stop();
	else ptimer->start(50);
}
void MyThread::run() {
	std::vector<list<Point *>::iterator >::iterator iicrp;
	int c;
	int J;//Point index
	
	if(I==0) {
		list<list<Line *>::iterator > *liL;
		list<list<Line *>::iterator >::iterator iiL;
		int j;
		double a[2];//acceleration
		double l,r;
		double KLine=Line::getKl(),KFl=lPoint::getKl(),KFs=sPoint::getKs();
		double dx[2];
		Point *pnt[2];

		for(iicrp=crp.begin();iicrp!=crp.end();++iicrp) {
			J=(**iicrp)->getJ();
			if(pr->press!=0 || ((**iicrp)!=(*pr->curP1))) {
				a[0]=a[1]=0;
				for(c=0;c<2;++c) {pr->x[c][J]=(**iicrp)->getX(c);}
				if(typeid(*(**iicrp))!=typeid(fPoint)) {
					for(c=0;c<2;++c) {pr->x[c+2][J]=(**iicrp)->getV(c);}
					liL = (**iicrp)->getiL();
					for(iiL=liL->begin();iiL!=liL->end();++iiL) {
						l=(**iiL)->getLength();
						for(j=0;j<2;++j) pnt[j]=*(**iiL)->getPoint(j);
						if(pnt[0]==(**iicrp)) j=1;
						else if(pnt[1]==(**iicrp)) j=0;
						else assert(0);
						for(c=0;c<2;++c) {dx[c] = pnt[j]->getX(c)+pr->delta[c][pnt[j]->getJ()] - (pr->x[c][J]+pr->delta[c][J]);}
						
						r=sqrt(dx[0]*dx[0]+dx[1]*dx[1]);
						if(r!=0 && r!=l) 
							for(c=0;c<2;++c) a[c]+=KLine*(r-l)*dx[c]/(l*r*pr->mass[J]);
					}
					for(c=0;c<2;++c) dx[c]=pr->x[c+2][J]+pr->delta[c+2][J];
					r=sqrt(dx[0]*dx[0]+dx[1]*dx[1]);
					if(typeid(*(**iicrp))==typeid(lPoint)) for(c=0;c<2;++c) a[c]-=KFl*pr->x[c+2][J]/pr->mass[J];
					else if(typeid(*(**iicrp))==typeid(sPoint)) for(c=0;c<2;++c) a[c]-=KFs*r*pr->x[c+2][J]/pr->mass[J];
				}
				else for(c=2;c<4;++c) pr->x[c][J]=0;//velocity=0

				for(c=0;c<2;++c) {
		 			pr->f[k][c][J]=pr->x[c+2][J]+pr->delta[c+2][J];
					pr->f[k][c+2][J]=a[c];
				}
			}
			else for(c=2;c<4;++c) pr->x[c][J]=0;//velocity=0
		}
	}
	else if(I==1) {
		for(iicrp=crp.begin();iicrp!=crp.end();++iicrp) {
			J=(**iicrp)->getJ();
			if(pr->press!=0 || ((**iicrp)!=(*pr->curP1))) {
				if(k<3) {
					for(c=0;c<4;++c) pr->delta[c][J]=pr->dt*pr->f[k][c][J];
					if(k==0||k==1) for(c=0;c<4;++c) pr->delta[c][J]*=0.5;
				}
				else if(k==3) {
					for(c=0;c<4;++c) pr->delta[c][J]=pr->dt/6*(pr->f[0][c][J]+2*pr->f[1][c][J]+2*pr->f[2][c][J]+pr->f[3][c][J]);
					(**iicrp)->setX(pr->x[0][J]+pr->delta[0][J],pr->x[1][J]+pr->delta[1][J]);
					(**iicrp)->setV(pr->x[2][J]+pr->delta[2][J],pr->x[3][J]+pr->delta[3][J]);
				}
			}
		}
	}
	else if(I==2) {
		for(iicrp=crp.begin();iicrp!=crp.end();++iicrp) {
			if(isFindP) break;
			if((fabs(xm - (**iicrp)->getX(0))<pr->RCUR) && (fabs(ym - (**iicrp)->getX(1))<pr->RCUR)) {
				isFindP=1;
				iFindPoint=(*iicrp);
				break;
			}
		}
	}
}
void PanelDraw::slotChangePCount() {
	int j;
	list<Point*>::iterator iP;
	reallocX();
	for(j=0;j<CntTh;++j) th[j].clearCrp();
	for(iP=P.begin(),j=0; iP!=P.end(); ++iP,++j) {
		if(j>=CntTh) j-=CntTh;
		th[j].pushPnt(iP);
	}
}
void PanelDraw::slotNextStep() {
	int k,j;
	for(k=0;k<4;++k) {
		MyThread::setI(0);
		MyThread::setK(k);
		for(j=0;j<CntTh;++j) th[j].start();
		for(j=0;j<CntTh;++j) th[j].wait();
		MyThread::setI(1);
		for(j=0;j<CntTh;++j) th[j].start();
		for(j=0;j<CntTh;++j) th[j].wait();
	}
	repaint();
}
bool PanelDraw::check() {
	list<Point *>::iterator iP;//итератор списка P
	list< list<Line *>::iterator > *liL;//список liL итераторов списка P для конкретной точки
	list< list<Line *>::iterator >::iterator iiL;//итератор списка liL 
	int j;
	Point *pnt[2];

	for(iP=P.begin();iP!=P.end();++iP) {
		if((*iP)==0) {return 1;}
		liL = (*iP)->getiL(); if(liL==0) return 2;
		for(iiL=liL->begin();iiL!=liL->end();++iiL) {
			if((**iiL)==0) return 3;
			for(j=0;j<2;++j) pnt[j] = *(**iiL)->getPoint(j);
			if( (*iP)==pnt[0] && (*iP)!=pnt[1] ) j=0;
			else if( (*iP)!=pnt[0] && (*iP)==pnt[1] ) j=1;
			else if( (*iP)==pnt[0] && (*iP)==pnt[1] ) return 4;
			else if( (*iP)!=pnt[0] && (*iP)!=pnt[1] ) return 5;
			else return 6;
			if((**iiL)!=(**(**iiL)->getiiL(j))) return 7;
		}
	}
	return 0;
}

PanelDraw *MyThread::pr=0;
int MyThread::k=0;
int MyThread::I=0;
list<Point *>::iterator tmp;
list<Point *>::iterator MyThread::iFindPoint=tmp;
bool MyThread::isFindP=0;
double MyThread::xm=0;
double MyThread::ym=0;

