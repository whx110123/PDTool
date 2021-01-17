#include "dialogdealdata.h"
#include "ui_dialogdealdata.h"
#include "quiwidget.h"
#include "globaldefine.h"

DialogDealData::DialogDealData(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogDealData)
{
	ui->setupUi(this);
	initfrom();
}

DialogDealData::~DialogDealData()
{
	delete ui;
}

void DialogDealData::initfrom()
{
	ui->cbcrc->addItems(App::CRClst);
	ui->cbtransform->addItems(App::Transfermode);
}

void DialogDealData::on_pbcrc_clicked()
{

	QString data = ui->textsource->toPlainText().trimmed();
	QByteArray ba = QUIHelper::hexStrToByteArray(data);
	uchar crcarray[2] = {0};
	int crclen = 0;
	if(ui->cbcrc->currentText().contains("CRC 16 低位在前"))
	{
		crclen = 2;
		ushort crc = crc16((uchar *)ba.data(), ba.length());
		crcarray[0] = crc & 0xff;
		crcarray[1] = (crc >> 8) & 0xff;
	}
	else if(ui->cbcrc->currentText().contains("CRC 16 高位在前"))
	{
		crclen = 2;
		ushort crc = crc16((uchar *)ba.data(), ba.length());
		crcarray[1] = crc & 0xff;
		crcarray[0] = (crc >> 8) & 0xff;
	}
	else if(ui->cbcrc->currentText().contains("总加和"))
	{
		crclen = 1;
		for(int i = 0; i < ba.length(); i++)
		{
			crcarray[0] += *(uchar *)(ba.data() + i);
		}
	}
	else if(ui->cbcrc->currentText().contains("加总异或"))
	{
		crclen = 1;
		for(int i = 0; i < ba.length(); i++)
		{
			crcarray[0] ^= *(uchar *)(ba.data() + i);
		}
	}


	for(int i = 0; i < crclen; i++)
	{
		data.append(" " + CharToHexStr(crcarray[i]));
	}
	ui->textdestination->setText(data.toUpper());

}

void DialogDealData::on_pbtransform_clicked()
{
	QString data = ui->linesource->text().trimmed();
	QString dataout;
	float datafloat = 0;
	double datadouble = 0;
	uint datauint = 0;
	int dataint = 0;
	if(ui->cbtransform->currentText().contains("浮点数转四字节"))
	{
		datafloat = data.toFloat();
		QByteArray ba((char *)&datafloat, 4);
		if(!ui->checkreverse->isChecked())
		{
			BaReverse(ba);
		}
		dataout.append(CharToHexStr(ba.data(), 4));
	}
	else if(ui->cbtransform->currentText().contains("四字节转浮点数"))
	{
		QByteArray ba = QUIHelper::hexStrToByteArray(data);
		if(ba.length() == 4)
		{
			int model = 1;
			if(ui->checkreverse->isChecked())
			{
				model = 0;
			}
			datafloat = charTofloat((uchar *)ba.data(), model);
			dataout = QString::number(datafloat, 'g', 10);
		}
	}
	else if(ui->cbtransform->currentText().contains("带符号整数转四字节"))
	{
		dataint = data.toInt();
		QByteArray ba((char *)&dataint, 4);
		if(!ui->checkreverse->isChecked())
		{
			BaReverse(ba);
		}
		dataout.append(CharToHexStr(ba.data(), 4));

	}
	else if(ui->cbtransform->currentText().contains("四字节转带符号整数"))
	{
		QByteArray ba = QUIHelper::hexStrToByteArray(data);
		if(ba.length() == 4)
		{
			int model = 1;
			if(ui->checkreverse->isChecked())
			{
				model = 0;
			}
			dataint = charToint((uchar *)ba.data(), 4, model);
			dataout = QString::number(dataint);
		}
	}
	else if(ui->cbtransform->currentText().contains("四字节转无符号整数"))
	{
		QByteArray ba = QUIHelper::hexStrToByteArray(data);
		if(ba.length() == 4)
		{
			int model = 1;
			if(ui->checkreverse->isChecked())
			{
				model = 0;
			}
			datauint = charTouint((uchar *)ba.data(), 4, model);
			dataout = QString::number(datauint);
		}
	}
	if(ui->cbtransform->currentText().contains("双精度浮点数转八字节"))
	{
		datadouble = data.toDouble();
		QByteArray ba((char *)&datadouble, 8);
		if(!ui->checkreverse->isChecked())
		{
			BaReverse(ba);
		}
		dataout.append(CharToHexStr(ba.data(), 8));

	}
	else if(ui->cbtransform->currentText().contains("八字节转双精度浮点数"))
	{
		QByteArray ba = QUIHelper::hexStrToByteArray(data);
		if(ba.length() == 8)
		{
			if(!ui->checkreverse->isChecked())
			{
				BaReverse(ba);
			}
			dataout = QString::number(*(double *)ba.data(), 'g', 20);
		}
	}
	ui->linedestination->setText(dataout.trimmed());

}

void DialogDealData::on_Bt1_clicked()
{
	QString text = ui->Le1->toPlainText();
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
	QString tmpgbk;
	QString tmputf8;
	QString tmpunicode;
	QByteArray hex_data;
	for(QChar byte : text)
	{
		tmpgbk.append(gbk->fromUnicode(byte).toHex() + " ");
		tmputf8.append(utf8->fromUnicode(byte).toHex() + " ");
		tmpunicode.append(QString::number(byte.unicode(), 16) + " ");
	}
	ui->Le2->setText(tmpgbk.trimmed().toUpper());
	ui->Le3->setText(tmputf8.trimmed().toUpper());
	ui->Le4->setText(tmpunicode.trimmed().toUpper());
}

void DialogDealData::on_Bt2_clicked()
{
	QString tmp;
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
	QString tmpgbk;
	QString tmputf8;
	QString tmpunicode;
	QByteArray ba = QUIHelper::hexStrToByteArray(ui->Le2->text());
	tmp = gbk->toUnicode(ba);
	for(QChar byte : tmp)
	{
		tmputf8.append(utf8->fromUnicode(byte).toHex() + " ");
		tmpunicode.append(QString::number(byte.unicode(), 16) + " ");
	}

	ui->Le1->setPlainText(tmp);
	ui->Le3->setText(tmputf8.trimmed().toUpper());
	ui->Le4->setText(tmpunicode.trimmed().toUpper());
}

void DialogDealData::on_Bt3_clicked()
{
	QString tmp;
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
	QString tmpgbk;
	QString tmputf8;
	QString tmpunicode;
	QByteArray ba = QUIHelper::hexStrToByteArray(ui->Le3->text());
	tmp = utf8->toUnicode(ba);
	for(QChar byte : tmp)
	{
		tmpgbk.append(gbk->fromUnicode(byte).toHex() + " ");
		tmpunicode.append(QString::number(byte.unicode(), 16) + " ");
	}

	ui->Le1->setPlainText(tmp);
	ui->Le2->setText(tmpgbk.trimmed().toUpper());
	ui->Le4->setText(tmpunicode.trimmed().toUpper());
}

void DialogDealData::on_Bt4_clicked()
{
	QString tmp;
	QStringList strlst = ui->Le4->text().split(" ");
	strlst.removeAll("");
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
	QString tmpgbk;
	QString tmputf8;
	for(QString str : strlst)
	{
		QChar byte(str.toUInt(0, 16));
		tmp.append(byte);
		tmpgbk.append(gbk->fromUnicode(byte).toHex() + " ");
		tmputf8.append(utf8->fromUnicode(byte).toHex() + " ");
	}

	ui->Le1->setPlainText(tmp);
	ui->Le2->setText(tmpgbk.trimmed().toUpper());
	ui->Le3->setText(tmputf8.trimmed().toUpper());
}


void DialogDealData::on_Bt_clear_clicked()
{
	ui->Le1->clear();
	ui->Le2->clear();
	ui->Le3->clear();
	ui->Le4->clear();
	ui->textsource->clear();
	ui->textdestination->clear();
	ui->linesource->clear();
	ui->linedestination->clear();
}
