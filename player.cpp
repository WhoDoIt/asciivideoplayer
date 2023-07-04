//
// Created by Данил on 03.07.2023.
//

#include "player.h"
#include "ascii_parser.h"
#include "ascii_drawer.h"
#include <QObject>
#include <QTimer>

Player::Player(MyLabel *label, AsciiParser *parser, QObject *parent) : QObject(parent), label(label), parser(parser) {
    timer = new QTimer();
    timer->setInterval(1000 / 25);

    QObject::connect(timer, &QTimer::timeout, this, &Player::update_frame);
    timer->start();
}


void Player::update_frame() {
//    printf("update: %i", current_frame);
    auto frame = parser->get_frame(current_frame);
    if (frame.h <= 0 && current_frame > 0)
        return;
    if (frame.h == 0) {
        current_frame += 1;
        return;
    }
    int h = label->height();
    int w = frame.w * h / frame.h;
    label->draw_frame(AsciiDrawer::DrawFrame(frame.str, frame.w, frame.h, w, h));
    current_frame += 1;
}

Player::~Player() {
    QObject::~QObject();
    delete timer;
}
