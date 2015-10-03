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

import bb.cascades 1.2

Page {
    Container {
        layout: DockLayout {
            
        }
        leftPadding: 6
        rightPadding: 6
        Container {
            horizontalAlignment: HorizontalAlignment.Center
            verticalAlignment: VerticalAlignment.Center
            Label {
                horizontalAlignment: HorizontalAlignment.Center
                textStyle.fontSize: FontSize.Large
                textStyle.fontWeight: FontWeight.W100
                textStyle.textAlign: TextAlign.Center
                multiline: true
                text: "This comedy is somewhat hilarious right."
                + " What if it's not hilarious and that is what I am"
                + " about to do now."
            
            }
            TextField {
                horizontalAlignment: HorizontalAlignment.Center
            }
            Button {
                horizontalAlignment: HorizontalAlignment.Center
                text: "Go"
            }   
        }
    }
}
