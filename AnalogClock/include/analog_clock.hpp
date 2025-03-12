#ifndef ANALOG_CLOCK_C86C4AFF_D567_4175_B282_3928F1C34C5B
#define ANALOG_CLOCK_C86C4AFF_D567_4175_B282_3928F1C34C5B

#include <QWidget>

class AnalogClock : public QWidget
{
	Q_OBJECT  // NOLINT

 public:
	explicit AnalogClock(QWidget *parent = nullptr);

 protected:
	void paintEvent(QPaintEvent *event) override;

 private:
};





#endif /* ANALOG_CLOCK_C86C4AFF_D567_4175_B282_3928F1C34C5B */
