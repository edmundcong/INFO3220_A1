#ifndef DIALOG_H
#define DIALOG_H

#include <list>
#include <QDialog>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

#include "cluster.h"
#include "galaxy.h"
#include "solarsystem.h"
#include "body.h"
#include "config.h"

namespace Ui {
  class Dialog;
}

/*
 * Represents a Qt Dialog
 */
class Dialog : public QDialog
{

  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = 0);
  std::string getStructure(vector<Cluster*>, vector<Galaxy>,
                           vector<solarSystem>);

  void setZodiac(bool val) { m_zodiac = val; }
  bool getZodiac() { return m_zodiac; }

  virtual ~Dialog();

public slots:
  void nextFrame();

protected:
  void paintEvent(QPaintEvent*);
  void keyPressEvent(QKeyEvent* event);


private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

private:
  Ui::Dialog* ui;
  std::list<Body*> m_bodies;
  std::vector<Body*> m_bodiesVector;
  Config* m_config;
  // Whether or not the simulation is currently paused
  bool paused;
  // Whether or not zodiac lines appear
  bool m_zodiac;

};

#endif // DIALOG_H
