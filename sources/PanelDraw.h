/*
* This source file is part of Linear-oscillator_QThread.
*
* Copyright (c) 2013 Linear-oscillator_QThread <https://github.com/IL90/Linear-oscillator_QThread>
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*/
#ifndef PANELDRAW_H
#define PANELDRAW_H
#include <QWidget>
#include <QFrame>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QTimer>

#include <iostream>
using std::cout;
using std::endl;

#include <cmath>
#include <vector>
#include <list>
using std::list;
#include <iterator>
#include <QThread>
#include "LinePoint.h"

class PanelDraw;

class MyThread : public QThread {
	Q_OBJECT
	public:
		void pushPnt(list<Point *>::iterator pnt_) {crp.push_back(pnt_);}
		void clearCrp() {crp.clear();}
		void run();
		static void setK(const int &k_) {k=k_;}
		static void setI(const int &i_) {I=i_; isFindP=0;}
		static int  getK() {return k;}
		static void setParent(PanelDraw *pr_) {pr=pr_;}
		static void setMx(double mx[]) {for(int c=0;c<2;++c) xmt[c]=mx[c];}
		static bool findPoint(list<Point *>::iterator &FP) {
			if(isFindP) FP=iFindPoint; 
			return isFindP;
		}
		static list<Point *>::iterator iFindPoint;
	private:
		std::vector< list<Point *>::iterator > crp;
		static int k;
		static int I;
		static PanelDraw *pr;
		static bool isFindP;
		static double xmt[2];
};

class PanelDraw : public QFrame {
	Q_OBJECT
	friend class MyThread;
	public:
		PanelDraw(QWidget *wgt=0);
		virtual ~PanelDraw();
	protected:
		virtual void paintEvent(QPaintEvent *e);
		virtual void mousePressEvent(QMouseEvent *pe);
		virtual void mouseReleaseEvent(QMouseEvent* pe);
		virtual void mouseMoveEvent(QMouseEvent* pe);
	private:
		bool check();
		void replacetype(list<Point*>::iterator it);
		void allocX();
		void freeX();
		void reallocX() {freeX(); allocX();}
		bool findMouseX(list<Point*>::iterator &iP,double mx_[]);
		list<Point*> P;
		list<Line*> L;
		list< list<Point*>::iterator > SelP;//selected Points
		list<Point*>::iterator curP1,curP2;
		int flagTools;//button,tools
		double mx[2],mx2[2];//coords mouse
		int pressMB;//0-left button mouse,1-right
		int press;
		QTimer *ptimer;
		const double dt;//time step
		const double RCUR;//click radius
		const int CntTh;//thread count
		double *x[4],*delta[4],*f[4][4],*mass;
		int N;
		MyThread *th;
		bool isEmptyX;
	public slots:
		void slotFlagTools(int i);
		void slotPlayPD();
		void slotNextStep();
		void slotChangePCount();
	signals:
		void sgnChangePCount();
};                
#endif           