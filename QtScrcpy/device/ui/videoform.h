#ifndef VIDEOFORM_H
#define VIDEOFORM_H

#include <QWidget>
#include <QPointer>

#include "keymap.h"

namespace Ui {
class videoForm;
}

struct AVFrame;
class ToolForm;
class Controller;
class FileHandler;
class VideoForm : public QWidget
{
    Q_OBJECT
public:
    explicit VideoForm(bool skin = true, QWidget *parent = nullptr);
    ~VideoForm();

    void switchFullScreen();    
    void staysOnTop(bool top = true);
    void updateScreenRatio(const QSize &newSize);
    void updateShowSize(const QSize &newSize);
    void updateRender(const AVFrame *frame);
    void setController(Controller *controller);
    Controller* getController();
    void setFileHandler(FileHandler *fileHandler);
    void setSerial(const QString &serial);

public slots:
    void onGrabCursor(bool grab);
    void close_keymapform();
    //void updateKeyMapForm();

private:    
    void updateStyleSheet(bool vertical);
    QMargins getMargins(bool vertical);
    void initUI();
    
    void showToolForm(bool show = true);
    void showKeyMapForm(bool show = true);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void paintEvent(QPaintEvent *);
    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);




private:
    // ui
    Ui::videoForm *ui;    
    QPointer<ToolForm> m_toolForm;
    QPointer<QWidget> m_loadingWidget;
    std::vector<QWidget*> m_keyWidget;
    KeyMap* m_keyMap = nullptr;
    QPoint m_videoWidgetOffset;

    //inside member
    QSize m_frameSize;
    QPoint m_dragPosition;
    float m_widthHeightRatio = 0.5f;
    bool m_skin = true;
    bool m_readState = true;

    //outside member
    QString m_serial = "";
    QPointer<Controller> m_controller;
    QPointer<FileHandler> m_fileHandler;
};

#endif // VIDEOFORM_H
