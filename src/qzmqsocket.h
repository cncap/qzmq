/*
 * Copyright (C) 2012 Justin Karneges
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef QZMQSOCKET_H
#define QZMQSOCKET_H

#include <QObject>

namespace QZmq {

class Context;

class Socket : public QObject
{
	Q_OBJECT

public:
	enum Type
	{
		Pair,
		Dealer,
		Router,
		Req,
		Rep,
		Push,
		Pull,
		Pub,
		Sub
	};

	Socket(Type type, QObject *parent = 0);
	Socket(Type type, Context *context, QObject *parent = 0);
	~Socket();

	void setShutdownWaitTime(int msecs); // 0 means drop queue and don't block, -1 means infinite (default = -1)

	void subscribe(const QByteArray &filter);
	void unsubscribe(const QByteArray &filter);

	QByteArray identity() const;
	void setIdentity(const QByteArray &id);

	void connectToAddress(const QString &addr);
	bool bind(const QString &addr);

	bool canRead() const;

	QList<QByteArray> read();
	void write(const QList<QByteArray> &message);

signals:
	void readyRead();
	void messagesWritten(int count);

private:
	Q_DISABLE_COPY(Socket)

	class Private;
	friend class Private;
	Private *d;
};

}

#endif
