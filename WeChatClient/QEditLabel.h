#pragma once

#include "QPch.h"
#include <QLabel>
#include <QLineEdit>
#include <QEvent>
#include <QObject>
#include <QStackedLayout>

class QEditLabel : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool showLabel READ getShowLabel WRITE setShowLabel)
  public:
    QEditLabel(QWidget* parent = nullptr);

    void setText(const char* text);
    QString getText();

    bool getShowLabel()
    {
        return m_bShowLable;
    }

    void setShowLabel(bool bShowLable)
    {
        m_bShowLable = bShowLable;
    }
  signals:
    void saveText();

  protected:
    bool eventFilter(QObject* obj, QEvent* e);

  private:
    QStackedLayout* m_StackLayout;
    QLabel* m_label;
    QLineEdit* m_lineEdit;

    bool m_bShowLable;
};