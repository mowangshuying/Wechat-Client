#include <QDebug>

#include "QSelfSplit.h"
#include "QDataManager.h"
#include "QCommContactInfoWnd.h"
#include "QStyleSheetMgr.h"

QCommContactInfoWnd::QCommContactInfoWnd(QWidget* p /*= nullptr*/) : QWidget(p)
{
    setObjectName("QCommContactInfo");
    QStyleSheetObject object;
    object.m_qssFileName = "./stylesheet/" + objectName() + ".qss";
    object.m_widget = this;
    QStyleSheetMgr::getMgr()->reg(object.m_qssFileName, object);

    QFont font1;
    font1.setPointSize(15);

    QFont font2;
    font2.setPointSize(12);

    setMinimumSize(640, 600);

    m_vLayout = new QVBoxLayout(this);

    m_vLayout1 = new QVBoxLayout();
    m_hLayout0 = new QHBoxLayout();
    m_hLayout0->setContentsMargins(0, 0, 0, 0);
    m_hLayout0->setSpacing(0);
    m_minBtn = new QPushButton(this);
    m_minBtn->setIcon(QPixmap("./img/minBtn_.png"));
    m_minBtn->setIconSize(QSize(20, 20));
    m_maxBtn = new QPushButton(this);
    m_maxBtn->setIcon(QPixmap("./img/normalBtn_.png"));
    m_maxBtn->setIconSize(QSize(20, 20));
    m_closeBtn = new QPushButton(this);
    m_closeBtn->setIcon(QPixmap("./img/closeBtn_.png"));
    m_closeBtn->setIconSize(QSize(20, 20));
    m_minBtn->setFixedSize(20, 20);
    m_maxBtn->setFixedSize(20, 20);
    m_closeBtn->setFixedSize(20, 20);

    m_hLayout0->addStretch();
    m_hLayout0->addWidget(m_minBtn);
    m_hLayout0->addWidget(m_maxBtn);
    m_hLayout0->addWidget(m_closeBtn);

    m_hLayout0->setContentsMargins(0, 0, 0, 0);
    m_hLayout0->setSpacing(5);
    m_vLayout->addLayout(m_hLayout0);

    // m_vLayout->addLayout(m_vLayout1);

    m_contentWnd = new QWidget(this);
    m_contentWnd->setFixedSize(500, 500);
    m_contentWnd->setLayout(m_vLayout1);
    m_vLayout->addWidget(m_contentWnd, 0, Qt::AlignCenter);

    m_vLayout1->setContentsMargins(75, 0, 75, 0);
    m_vLayout1->addSpacing(100);

    m_hLayout1 = new QHBoxLayout();
    m_nickNameLabel = new QLabel("***昵称***");
    m_nickNameLabel->setFont(font1);

    m_headimgLabel = new QLabel();
    m_headimgLabel->setFixedSize(60, 60);

    m_hLayout1->addWidget(m_nickNameLabel);
    m_hLayout1->addWidget(m_headimgLabel);

    m_vLayout1->addLayout(m_hLayout1);
    m_vLayout1->addSpacing(50);

    m_hLayout2 = new QHBoxLayout();
    m_markNameLabel = new QLabel("备  注:");
    m_markNameFillLabel = new QLabel("***备注***");

    m_markNameLabel->setFont(font2);
    m_markNameFillLabel->setFont(font2);

    m_hLayout2->addSpacing(150);
    m_hLayout2->addWidget(m_markNameLabel);
    m_hLayout2->addSpacing(15);
    m_hLayout2->addWidget(m_markNameFillLabel);
    m_hLayout2->addStretch();
    m_vLayout1->addLayout(m_hLayout2);
    m_vLayout1->addSpacing(25);

    m_hLayout3 = new QHBoxLayout();
    m_rolenameLabel = new QLabel("微信号:");
    m_rolenameFillLabel = new QLabel("***微信号***");

    m_rolenameLabel->setFont(font2);
    m_rolenameFillLabel->setFont(font2);

    m_hLayout3->addSpacing(150);
    m_hLayout3->addWidget(m_rolenameLabel);
    m_hLayout3->addSpacing(15);
    m_hLayout3->addWidget(m_rolenameFillLabel);
    m_hLayout3->addStretch();

    m_vLayout1->addLayout(m_hLayout3);
    m_vLayout1->addSpacing(25);

    m_hLayout4 = new QHBoxLayout();
    m_channelLabel = new QLabel("渠  道:");
    m_channelFillLabel = new QLabel("***渠道***");

    m_channelLabel->setFont(font2);
    m_channelFillLabel->setFont(font2);

    m_hLayout4->addSpacing(150);
    m_hLayout4->addWidget(m_channelLabel);
    m_hLayout4->addSpacing(15);
    m_hLayout4->addWidget(m_channelFillLabel);
    m_hLayout4->addStretch();
    m_vLayout1->addLayout(m_hLayout4);

    m_vLayout1->addSpacing(25);

    m_hLayout5 = new QHBoxLayout();
    m_sendMsgBtn = new QPushButton("发送消息");
    m_sendMsgBtn->setFixedSize(140, 35);

    m_hLayout5->addSpacing(155);
    m_hLayout5->addWidget(m_sendMsgBtn);
    m_hLayout5->addStretch();

    m_vLayout1->addLayout(m_hLayout5);
    m_vLayout1->addStretch();

    setLayout(m_vLayout1);
    setAttribute(Qt::WA_StyledBackground);

    connect(m_sendMsgBtn, SIGNAL(clicked()), this, SLOT(slotSendMsgBtnClick()));

    showBgPng();
    setMouseTracking(true);
}

void QCommContactInfoWnd::slotContactInfoChange(QMap<QString, QString> map)
{
    LogDebug << "contactInfoChange map = " << map;
    //根据map中name字段修改昵称字段
    m_nickNameLabel->setText(map["name"]);
    //加载QDataManager中玩家头像数据
    int friendid = atoi(map["friendid"].toStdString().c_str());
    QPixmap pixmap = QDataManager::getMgr()->m_UserId2HeadImgMap[friendid];
    pixmap = pixmap.scaled(60, 60);
    m_headimgLabel->setPixmap(pixmap);
    hideBgPng();
}

void QCommContactInfoWnd::slotSendMsgBtnClick()
{
    //点击发送按钮，创建一个会话，并切换过去
    QMap<QString, QString> map;
    map["name"] = m_nickNameLabel->text();
    emit signalSendMsgBtnClick(map);
}

//显示空白背景图片
void QCommContactInfoWnd::showBgPng()
{
    m_nickNameLabel->hide();
    m_markNameLabel->hide();
    m_rolenameLabel->hide();  //角色名
    m_channelLabel->hide();
    m_markNameFillLabel->hide();
    m_rolenameFillLabel->hide();
    m_channelFillLabel->hide();
    m_headimgLabel->hide();
    //发送消息窗口
    m_sendMsgBtn->hide();
    // setStyleSheet("background-color:white;border-image:url(./img/emptybg.png)");
}

//隐藏空白背景图片
void QCommContactInfoWnd::hideBgPng()
{
    m_nickNameLabel->show();
    m_markNameLabel->show();
    m_rolenameLabel->show();  //角色名
    m_channelLabel->show();
    m_markNameFillLabel->show();
    m_rolenameFillLabel->show();
    m_channelFillLabel->show();
    m_headimgLabel->show();
    //发送消息窗口
    m_sendMsgBtn->show();
    // setStyleSheet("background-color:white;");
}