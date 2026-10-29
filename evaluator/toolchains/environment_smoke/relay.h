#pragma once
#include <QObject>
class Relay : public QObject {
  Q_OBJECT
public:
  void send(int value) { emit changed(value); }
signals:
  void changed(int value);
};
