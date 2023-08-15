//
// Created by Данил on 03.07.2023.
//

#ifndef ASCIIVIDEOPLAYER_PLAYER_H
#define ASCIIVIDEOPLAYER_PLAYER_H


#include "my_label.h"

class Player : public QObject {
public:
    explicit Player(MyLabel* label, QSlider *slider, AsciiParser *parser, QObject *parent = nullptr);

    ~Player() override;
public slots:
    int set_frame(int i);
private:
    int current_frame = 0;

    QSlider *slider;
    MyLabel *label;
    AsciiParser *parser;
    QTimer *timer;
private slots:
    void update_frame();
};


#endif //ASCIIVIDEOPLAYER_PLAYER_H
