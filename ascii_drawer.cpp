//
// Created by Данил on 03.07.2023.
//

#include <QPixmap>
#include <QPainter>
#include "ascii_drawer.h"

QPixmap AsciiDrawer::DrawFrame(const QString &qs, int aw, int ah, int w, int h) {
    QFontMetrics metrics(font);
    QPixmap pix(aw * metrics.averageCharWidth(), ah * metrics.height());
    pix.fill(QColor(0, 0, 0));

    QPainter painter(&pix);
    painter.setPen(QPen(QColor(255, 255, 255)));
    painter.setFont(font);
    painter.drawText(pix.rect(), Qt::AlignTop | Qt::AlignHCenter, qs);
    return pix.scaled(w, h);
//    return pix;
}
