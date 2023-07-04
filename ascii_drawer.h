//
// Created by Данил on 03.07.2023.
//

#ifndef ASCIIVIDEOPLAYER_ASCII_DRAWER_H
#define ASCIIVIDEOPLAYER_ASCII_DRAWER_H


#include <QFont>

class AsciiDrawer {
public:
    AsciiDrawer() = default;

    static QPixmap DrawFrame(const QString &qs, int aw, int ah, int w, int h);
private:
    static inline QFont font = QFont("Consolas", 14);
};


#endif //ASCIIVIDEOPLAYER_ASCII_DRAWER_H
