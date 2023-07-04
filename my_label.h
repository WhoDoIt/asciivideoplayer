//
// Created by Данил on 25.06.2023.
//

#ifndef ASCIIVIDEOPLAYER_MY_LABEL_H
#define ASCIIVIDEOPLAYER_MY_LABEL_H

#include <QLabel>
#include <QSlider>
#include "ascii_parser.h"


class MyLabel : public QLabel {
public:
    explicit MyLabel(QWidget *parent = nullptr);

    void draw_frame(const QPixmap &px);

    ~MyLabel() override;
};


#endif //ASCIIVIDEOPLAYER_MY_LABEL_H
