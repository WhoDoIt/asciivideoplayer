//
// Created by Данил on 25.06.2023.
//

#include "my_label.h"
#include <QLabel>
#include <QSlider>
#include "ascii_parser.h"
#include <iostream>


MyLabel::MyLabel(QWidget *parent) : QLabel(parent) {
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setStyleSheet("background-color: rgb(0, 0, 0)");
    this->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
}

void MyLabel::draw_frame(const QPixmap &px) {
    this->setPixmap(px);
};

MyLabel::~MyLabel() = default;
