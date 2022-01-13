// Editor.cpp

#include <QtGui>

class Editor : public QDialog
{
  QPushButton *bt1, *bt2, *bt3, *bt4, *bt5, *bt6;
  QLineEdit *le1, *le2, *le3, *le4;
  QLabel *lb1, *lb2, *lb3, *lb4;
  QListWidget *listWidget;

public:
  Editor() { initGUI(); };

  void initGUI()
  {
    // buttons
    bt1 = new QPushButton(tr("#1"));
    bt2 = new QPushButton(tr("#2"));
    bt3 = new QPushButton(tr("#3"));
    bt4 = new QPushButton(tr("#4"));
    bt5 = new QPushButton(tr("#5"));
    bt6 = new QPushButton(tr("#6"));

    le1 = new QLineEdit(tr("le1"));
    //        le1->setMinimumWidth(200); // FIXME ???
    le1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    le2 = new QLineEdit(tr("le2"));
    le3 = new QLineEdit(tr("le3"));
    le4 = new QLineEdit(tr("le4"));

    lb1 = new QLabel(tr("lb1"));
    lb2 = new QLabel(tr("lb2"));
    lb3 = new QLabel(tr("lb3"));
    lb4 = new QLabel(tr("lb4"));

    // list(PROBLEM)widget
    listWidget = new QListWidget();
    //        listWidget->setMaximumWidth(100); // FIXME: ???
    listWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QGridLayout *gloEditor = new QGridLayout;
    gloEditor->addWidget(listWidget, 0, 0, 6, 1);
    gloEditor->addWidget(lb1, 0, 2, 1, 1);
    gloEditor->addWidget(le1, 0, 3, 1, 3);
    gloEditor->addWidget(lb2, 1, 2, 1, 1);
    gloEditor->addWidget(le2, 1, 3, 1, 3);
    gloEditor->addWidget(lb3, 2, 2, 1, 1);
    gloEditor->addWidget(le3, 2, 3, 1, 3);
    gloEditor->addWidget(lb4, 3, 2, 1, 1);
    gloEditor->addWidget(le4, 3, 3, 1, 3);
    gloEditor->addWidget(bt1, 0, 6, 1, 1);
    gloEditor->addWidget(bt2, 1, 6, 1, 1);
    gloEditor->addWidget(bt3, 2, 6, 1, 1);
    gloEditor->addWidget(bt4, 3, 6, 1, 1);
    gloEditor->addWidget(bt5, 5, 5, 1, 1);
    gloEditor->addWidget(bt6, 5, 6, 1, 1);
    setLayout(gloEditor);

    // window
    setWindowTitle(tr("Editor"));
    setFixedSize(sizeHint().width(), sizeHint().height());
  };
};


int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  Editor *dialog = new Editor();
  dialog->show();
  return app.exec();
};
