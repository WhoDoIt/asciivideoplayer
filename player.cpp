//
// Created by Данил on 03.07.2023.
//

#include "player.h"
#include "ascii_parser.h"
#include "ascii_drawer.h"
#include <QObject>
#include <QTimer>

Player::Player(MyLabel *label, QSlider *slider, AsciiParser *parser, QObject *parent) : QObject(parent), label(label), slider(slider), parser(parser) {
    timer = new QTimer();
    timer->setInterval(1000 / 25);

    QObject::connect(timer, &QTimer::timeout, this, &Player::update_frame);
    timer->start();
}


void Player::update_frame() {
//    printf("update: %i", current_frame);
    current_frame += set_frame(current_frame);
}

Player::~Player() {
    QObject::~QObject();
    delete timer;
}

int Player::set_frame(int curr) {
    auto frame = parser->get_frame(curr);
    current_frame = curr;
    if (frame.h <= 0 && curr > 0)
        return 0;
    if (frame.h == 0) {
        return 1;
    }
    {
        QSignalBlocker blocker(slider);
        slider->setValue(curr);
    }
    int h = label->height();
    int w = frame.w * h / frame.h;
    label->draw_frame(AsciiDrawer::DrawFrame(frame.str, frame.w, frame.h, w, h));
    return 1;
}
