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

#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/ImageView>
#include <bb/cascades/Page>

#include <bb/data/JsonDataAccess>

#include <stdlib.h>
#include <time.h>

ApplicationUI::ApplicationUI() :QObject()
{
    srand(time(NULL));

    //noFirstName = noLastName = TRUE;

    errorMessages<<"Oops. Looks like I forgot a wire. Would you check the connection for me?"
            <<"I guess you know I need to connect to my brain. Please connect me to the Internet."
            <<"You did it, again. You forgot to connect me to the Internet."
            <<"I get an error called No Internet Connection. Would you take care of it for me?"
            <<"Just connect me to the Internet please."
            <<"Until and unless you connect me to the Internet, please don't press the button again.";

    waitingMessages<<"Loading. Loading. Loading."
            <<"I'm trying to connect. Please stay with me."
            <<"I think your internet connection is very slow."
            <<"Couldn't you have got a slower connection?"
            <<"I'm getting bored here, waiting for my brain to answer.";

    ImageView *smileyImage = ImageView::create().
            horizontal(HorizontalAlignment::Center).
            image("asset:///images/smiley.gif");

    infoLabel = Label::create().
            horizontal(HorizontalAlignment::Center).
            format(TextFormat::Html).
            multiline(TRUE).
            text("Enter your friend's name in the field below and press the button");
    infoLabel->textStyle()->setFontSize(FontSize::Large);
    infoLabel->textStyle()->setFontWeight(FontWeight::W100);
    infoLabel->textStyle()->setTextAlign(TextAlign::Center);

    nameField = TextField::create().
            horizontal(HorizontalAlignment::Center).
            hintText("Your friend's name here");

    goButton = Button::create().
            horizontal(HorizontalAlignment::Center).
            onClicked(this, SLOT(onGoPressed())).
            text("Tell me a joke");

    Container *contentC = Container::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            add(smileyImage).
            add(infoLabel).
            add(nameField).
            add(goButton);

    Container *rootC = Container::create().
            layout(DockLayout::create()).
            left(6).
            right(6).
            add(contentC);

    Page *rootPage = Page::create().
            content(rootC);

    Application::instance()->setScene(rootPage);
}

void ApplicationUI::onGoPressed()
{
    goButton->setEnabled(FALSE);

    int index = rand()%(waitingMessages.size());
    infoLabel->setText(waitingMessages.at(index));

    QNetworkRequest request;

    QStringList nameList = nameField->text().split(' ', QString::SkipEmptyParts);
    QString firstName, lastName;
    switch(nameList.size())
    {
        case 0:
            /*noFirstName = true;
            noLastName = true;*/

            firstName = "Santhosh";
            lastName = "Pandit";
            break;
        case 1:
            /*noFirstName = false;
            noLastName = true;*/

            firstName = nameList.at(0);
            lastName = "___";
            break;
        default:
            /*noFirstName = false;
            noLastName = false;*/

            lastName = nameList.last();
            for(int i=0; i<nameList.size()-1; i++)
                firstName = firstName.append(nameList.at(i));
    }
    request.setUrl(QString("http://api.icndb.com/jokes/random?lastName=" +
            lastName + "&firstName=" + firstName));

    QNetworkReply *reply = networkManager.get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(onReplyFinished()));
}

void ApplicationUI::onReplyFinished()
{
    goButton->setEnabled(TRUE);

    QNetworkReply *reply = static_cast<QNetworkReply*>(sender());
    if(!reply)
        return;

    if(reply->error()==QNetworkReply::NoError)
    {
        //qDebug()<<reply->readAll().trimmed();

        bb::data::JsonDataAccess jda;
        QVariantMap replyMap = jda.load(reply).toMap();
        QVariantMap valueMap = replyMap["value"].toMap();
        QString joke = valueMap["joke"].toString();

        if(joke.contains(" ___"))
        {
            joke = joke.replace(" ___", "");
        }

        /*if(!noFirstName && noLastName)
        {

        }*/

        infoLabel->setText(joke);
    }
    else
    {
        int index = rand()%(errorMessages.size());
        infoLabel->setText(errorMessages.at(index));
    }

    reply->deleteLater();
}
