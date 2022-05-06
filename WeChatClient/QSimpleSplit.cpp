#include "QSimpleSplit.h"

QSimpleSplit::QSimpleSplit(QWidget* p /*= nullptr*/, QSimpleSplit_direction d/* = QSimpleSplit_direction_v*/)
{
	setAttribute(Qt::WA_StyledBackground);
	//设置一些样式
	//无焦点
	setFocusPolicy(Qt::NoFocus);
	if (d == QSimpleSplit_direction_v) {
		//设置高度为2
		setFixedHeight(1);
	}
	else {
		setFixedWidth(1);
	}
	//设置分割线的颜色
	// 灰色的分割线
	//setStyleSheet("background-color:#E7E7E;border:none");
	
	// 红色的分割线
	setStyleSheet("background-color:#FF0000;border:none");
}

