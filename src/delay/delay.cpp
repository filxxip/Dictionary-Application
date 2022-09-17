#include "delay.h"

void delay(int delay_miliseconds) {
  auto current = QTime::currentTime();
  auto die_time = current.addMSecs(delay_miliseconds);
  while (QTime::currentTime() < die_time) {
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
  }
}
