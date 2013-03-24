// Toolbar.hpp

#ifndef TOOLBAR
#define TOOLBAR

#include <QtGui>
#include <iostream>

class Toolbar : public QMainWindow
{
    Q_OBJECT

private slots:
    void slotInsertLetter(){ 
        QString szLetter = "";
        QAction *action = qobject_cast< QAction* >(sender());
        if(action) szLetter = action->data().toString();
        // FIXME
        std::cout << "szLetter ist \""<< szLetter.toStdString() 
                  << "\" und sollte nun an genau an die Stelle gesetzt werden,"
                  << "wo der Curser gerade steht!\n";
        if (le1->hasFocus())
			le1->insert(szLetter); 
		else if(le2->hasFocus())
			le2->insert(szLetter);
		else
			;
			
/*
	Zumindest Frage zwei und drei lässt sich durch ein leichtes suchen in der Doku finden... 
		http://doc.trolltech.com/4.3/qlineedit.html

	Das gerade aktive QLineEdit rauszufinden ist etwas schwieriger, da, sobald man einen Button
	anklickt, das LineEdit ja nicht mehr aktiv ist... aber da das QLineEdit kurz bevor es den 
	Fokus verliert, ein Signal aussendet (void QLineEdit::editingFinished ()) sollte auch das kein
	Problem sein. (Christian81, QtForum.de)
//*/		
    };

private:
    QAction *act1, *act2, *act3;
    QLineEdit *le1, *le2;
    QToolBar *tb;

    void initGUI(){
        le1 = new QLineEdit();
        le2 = new QLineEdit();
        QVBoxLayout* layout = new QVBoxLayout();
        layout->addWidget(le1);
        layout->addWidget(le2);
        setCentralWidget(new QWidget());
        centralWidget()->setLayout(layout);
    };

    void createActions(){
        act1 = new QAction(tr("ä"), this);
        act1->setData("ä");
        connect(act1, SIGNAL(triggered()), this, SLOT(slotInsertLetter()));
        act2 = new QAction(tr("ö"), this);
        act2->setData("ö");
        connect(act2, SIGNAL(triggered()), this, SLOT(slotInsertLetter()));
        act3 = new QAction(tr("ü"), this); 
        act3->setData("ü");
        connect(act3, SIGNAL(triggered()), this, SLOT(slotInsertLetter()));
    };
    
    void createToolBar(){
        tb = addToolBar(tr("letters"));
        tb->addAction(act1);
        tb->addAction(act2);
        tb->addAction(act3);
    };
    
public:
    Toolbar(){
        initGUI();
        createActions();
        createToolBar();
    };
};
#endif
