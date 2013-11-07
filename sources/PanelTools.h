#ifndef PANELTOOLS_H
#define PANELTOOLS_H

#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <cassert>
#include <QSignalMapper>

class PanelTools : public QFrame {
	Q_OBJECT
	public:
		PanelTools(QWidget *wgt=0) : QFrame(wgt),N(6) {
			setFrameStyle(QFrame::WinPanel|QFrame::Raised);
			try {
			bt = new QPushButton* [N];
			bt[0] = new QPushButton("_",this);//drag&drop points
			bt[1] = new QPushButton("o",this);//create a point
			bt[2] = new QPushButton("x",this);//delete a point / delete selected points
			bt[3] = new QPushButton("-",this);//create a line between two points
			bt[4] = new QPushButton("~",this);//delete a line
			bt[5] = new QPushButton("[]",this);//select points
			btPlay = new QPushButton("|>",this);//play/pause
			btHelp = new QPushButton("?",this);//help
			} catch(std::bad_alloc) {assert(0);}
			for(int c=0;c<N;++c) {
				bt[c]->setGeometry(5,5+25*c,20,20);
				bt[c]->setCheckable(true);
				bt[c]->setChecked(false);
			}
			bt[1]->setChecked(true);
			btPlay->setGeometry(5,5+25*N,20,20);
			btHelp->setGeometry(5,5+25*(N+1),20,20);

			signalMapper = new QSignalMapper(this);
			for(int c=0;c<N;++c) {
				connect(bt[c],SIGNAL(clicked()),signalMapper,SLOT(map()));
				signalMapper->setMapping(bt[c],c);
			}
			connect(signalMapper,SIGNAL(mapped(int)),this,SLOT(click(int)));
			connect(btPlay,SIGNAL(clicked()),SLOT(slotPlay()));
			connect(btHelp,SIGNAL(clicked()),SIGNAL(sgnHelp()));

		}
		~PanelTools() {delete[] bt;}
	private:
		const int N;
		QPushButton **bt,*btPlay,*btHelp;
		QSignalMapper *signalMapper;
	private slots:
		void click(int i) {
			for(int c=0;c<N;++c) if(bt[c]->isChecked()) bt[c]->setChecked(false);
			emit sgnCmd(i);
			bt[i]->setChecked(true);
		}
		void slotPlay() {
			if(btPlay->text() == "|>") btPlay->setText("||");
			else btPlay->setText("|>");
			emit sgnPlay();
		}
	signals:
		void sgnCmd(int flag);
		void sgnPlay();
		void sgnHelp();
};
#endif
