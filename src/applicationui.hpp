/*
 * Copyright (c) 2011-2014 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>
#include <QtNetwork/qnetworkaccessmanager.h>
//#include <QtNetwork/qnetworkreply.h>

#include <bb/cascades/Button>
#include <bb/cascades/Label>
#include <bb/cascades/TextField>

using namespace bb::cascades;

class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI();
private slots:
    void onGoPressed();
    void onReplyFinished();
private:
    //bool noFirstName, noLastName;
    QNetworkAccessManager networkManager;
    QStringList errorMessages, waitingMessages;

    Button *goButton;
    Label *infoLabel;
    TextField *nameField;
};

#endif /* ApplicationUI_HPP_ */
