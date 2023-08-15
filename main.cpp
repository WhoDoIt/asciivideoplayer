#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QTimer>
#include <QObject>
#include <QMainWindow>
#include <thread>
#include "ascii_parser.h"
#include "my_label.h"
#include "ascii_drawer.h"
#include "player.h"

AsciiParser *ap;

int main(int argc, char **argv) {
    ap = new AsciiParser(argv[1]);
    ap->start();

    QApplication app (argc, argv);
    QWidget window;
    window.setMinimumSize(800, 800);

    auto slider = new QSlider(Qt::Horizontal, &window);
    slider->setMinimum(0);
    slider->setMaximum(ap->duration);
    slider->setStyleSheet("QSlider::groove:horizontal {\n"
                          "    border-radius: 1px;       \n"
                          "    height: 7px;              \n"
                          "    margin: -1px 0;           \n"
                          "}\n"
                          "QSlider::handle:horizontal {\n"
                          "    background-color: rgb(255, 123, 172);\n"
                          "    border: 2px solid rgb(77, 77, 77);\n"
                          "    height: 14px;     \n"
                          "    width: 12px;\n"
                          "    margin: -4px 0;     \n"
                          "    border-radius: 7px  ;\n"
                          "    padding: -4px 0px;  \n"
                          "}\n"
                          "QSlider::add-page:horizontal {\n"
                          "    background: rgb(122, 201, 67);\n"
                          "}\n"
                          "QSlider::sub-page:horizontal {\n"
                          "    background: rgb(63, 169, 245);\n"
                          "}");
    slider->setMaximumHeight(70);
    slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    auto layout = new QVBoxLayout(&window);
    layout->setSpacing(0);

    MyLabel label( &window);

    layout->addWidget(&label);
    layout->addWidget(slider);


    Player player(&label, slider, ap, &window);
    QObject::connect(slider, &QSlider::valueChanged, &player, &Player::set_frame);

    window.show();


    return app.exec();
}
