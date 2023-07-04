//
// Created by Данил on 03.07.2023.
//

#ifndef ASCIIVIDEOPLAYER_PLAYER_H
#define ASCIIVIDEOPLAYER_PLAYER_H


#include "my_label.h"

class Player : public QObject {
public:
    explicit Player(MyLabel* label, AsciiParser *parser, QObject *parent = nullptr);

    ~Player() override;
private:
    int current_frame = 0;

    MyLabel *label;
    AsciiParser *parser;
    QTimer *timer;
private slots:
    void update_frame();
};


#endif //ASCIIVIDEOPLAYER_PLAYER_H
