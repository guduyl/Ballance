#ifndef BALLANCE_H
#define BALLANCE_H

#include <QWidget>

namespace Ui {
class Ballance;
}

class Ballance : public QWidget
{
    Q_OBJECT

public:
    explicit Ballance(QWidget *parent = 0);
    ~Ballance();

private:
    Ui::Ballance *ui;
};

#endif // BALLANCE_H
