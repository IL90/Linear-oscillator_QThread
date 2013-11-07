#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QResizeEvent>
#include <QCloseEvent>
#include <cassert>

#include "PanelTools.h"
#include "PanelDraw.h"

class PanelTools;
class PanelDraw;

class HelpWindow : public QFrame {
	public:
		HelpWindow(QWidget *wgt=0) : QFrame(wgt) {
			setWindowFlags(Qt::Window|Qt::WindowStaysOnTopHint);
			setFixedSize(340,280);
			QString str;
			str =" _ - drag&drop points / selected points if pause\n";
			str+=" o - create a point\n";
			str+=" x - delete a point / delete selected points\n";
			str+=" - - create a line between two points\n";
			str+=" ~ - delete a line\n";
			str+=" [] - select points\n";
			str+=" \\>/|| - play/pause\n";
			str+=" ? - help\n\n";
			str+=" right mouse button - change a point type:\n";
			str+="   white - no friction\n";
			str+="   red - friction increases proportionate \n";
			str+="     to the velocity\n";
			str+="   green - friction increases proportionate \n";
			str+="     to the square of the velocity\n";
			str+="   blue - fixed";
			try { lbl= new QLabel(str,this);
			} catch(std::bad_alloc) {assert(0);}
			lbl->move(10,10);
		}
		virtual void closeEvent(QCloseEvent *) {hide();}
	private:
		QLabel *lbl;
};

class MainWindow : public QFrame {
	Q_OBJECT
	public:
		MainWindow(QWidget *wgt=0) : QFrame(wgt),Wtools(30) {
			setWindowTitle("Linear oscillator");
			resize(650,650);
			try {
			pt = new PanelTools(this);
			pd = new PanelDraw(this);
			hw = new HelpWindow(0);
			} catch(std::bad_alloc) {assert(0);}
			hw->hide();
			pt->setGeometry(0,0,Wtools,height());
			pd->setGeometry(Wtools,0,width()-Wtools,height());
			connect(pt,SIGNAL(sgnCmd(int)),pd,SLOT(slotFlagTools(int)));
			connect(pt,SIGNAL(sgnPlay()),pd,SLOT(slotPlayPD()));
			connect(pt,SIGNAL(sgnHelp()),SLOT(slotHelpPD()));
			
		}
		~MainWindow() {}
	protected:
		virtual void closeEvent(QCloseEvent *) {delete hw;}
		virtual void resizeEvent(QResizeEvent *re) {
			pd->resize(re->size().width()-Wtools,re->size().height());
			pt->resize(Wtools,re->size().height());
		}
	private:
		PanelTools *pt;
		PanelDraw  *pd;
		HelpWindow *hw;
		const int Wtools;

	public slots:
		void slotHelpPD() {if(!hw->isVisible()) hw->show();}
};
#endif