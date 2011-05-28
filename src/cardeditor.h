#ifndef CARDEDITOR_H
#define CARDEDITOR_H

#include <QDialog>
#include <QGraphicsView>
#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QTabWidget>
#include <QGraphicsPixmapItem>
#include <QFontDatabase>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QMainWindow>

class Pixmap;

class BlackEdgeTextItem: public QGraphicsObject{
    Q_OBJECT

public:
    BlackEdgeTextItem();  
    void setColor(const QColor &color);
    void setOutline(int outline);

public slots:
    void setText(const QString &text);
    void setFont(const QFont &font);
    void setSkip(int skip);

    virtual QRectF boundingRect() const;

protected:    
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QString text;
    QFont font;
    int skip;
    QColor color;
    int outline;
};

class SkillBox: public QGraphicsObject{
    Q_OBJECT

public:
    SkillBox();
    void setKingdom(const QString &kingdom);
    void setMiddleHeight(int height);

    virtual QRectF boundingRect() const;

public slots:
    void addSkill();
    void setSkillTitleFont(const QFont &font);
    void setSkillDescriptionFont(const QFont &font);
    void updateLayout();

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    int middle_height;
    QPixmap up, middle, down;
    QString kingdom;
    QList<QGraphicsTextItem *> skill_titles;
    QList<QGraphicsTextItem *> skill_descriptions;
};

class CardScene: public QGraphicsScene{
    Q_OBJECT

public:
    explicit CardScene();

    void setFrame(const QString &kingdom, bool is_lord);
    void setGeneralPhoto(const QString &filename);
    BlackEdgeTextItem *getNameItem() const;
    BlackEdgeTextItem *getTitleItem() const;
    SkillBox *getSkillBox() const;
    void save(const QString &filename, bool smooth = true);
    void saveConfig();
    void loadConfig();

public slots:
    void setRatio(int ratio);
    void setMaxHp(int max_hp);    

#ifdef QT_DEBUG
protected:
    virtual void keyPressEvent(QKeyEvent *);
#endif

private:
    Pixmap *photo;
    QGraphicsPixmapItem *frame;
    QList<QGraphicsPixmapItem *> magatamas;
    BlackEdgeTextItem *name, *title;
    SkillBox *skill_box;
};

class CardEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit CardEditor(QWidget *parent = 0);

private:
    CardScene *card_scene;
    QComboBox *kingdom_combobox;
    QCheckBox *lord_checkbox;
    QSpinBox *ratio_spinbox;

    QWidget *createLeft();
    QGroupBox *createTextItemBox(const QString &text,
                                 const QFont &font,
                                 int skip,
                                 BlackEdgeTextItem *item
                                 );
    QLayout *createGeneralLayout();
    QWidget *createSkillBox();

protected:
    virtual void closeEvent(QCloseEvent *);

private slots:
    void setCardFrame();
    void import();
    void saveImage();
};

#endif // CARDEDITOR_H