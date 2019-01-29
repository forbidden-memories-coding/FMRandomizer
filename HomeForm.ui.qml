import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Page {
    id: page
    width: 600
    height: 470
    property alias biHeavyProc: biHeavyProc
    property alias rsDefense: rsDefense
    property alias rsAttack: rsAttack
    property alias rsStarCost: rsStarCost
    property alias rsDropRate: rsDropRate
    property alias chkRandPass: chkRandPass
    property alias chkRandStarCost: chkRandStarCost
    property alias chkRandFuse: chkRandFuse
    property alias chkRandEquip: chkRandEquip
    property alias chkRandDuelistDeck: chkRandDuelistDeck
    property alias chkRandCardDrop: chkRandCardDrop
    property alias chkRandType: chkRandType
    property alias chkZeroGlitchFuse: chkZeroGlitchFuse
    property alias chkEnAtkDefScramble: chkEnAtkDefScramble
    property alias chkAlGlitchGuardStars: chkAlGlitchGuardStars
    property alias chkRandGuardStars: chkRandGuardStars
    property alias btnPatchIso: btnPatchIso
    property alias btnLoadGame: btnLoadGame
    property alias btnLoadSlusMrg: btnLoadSlusMrg
    property alias btnRandomize: btnRandomize
    property alias txtSeed: txtSeed
    property alias btnGenRand: btnGenRand
    property alias chkRandAttrib: chkRandAttrib
    property alias btnExit: btnExit
    enabled: !biHeavyProc.running
    padding: 10
    wheelEnabled: false
    hoverEnabled: true
    spacing: 0
    title: qsTr("Action")

    TabBar {
        id: tabBar
        x: 0
        y: 22
        width: 580
        height: 44
        currentIndex: 1
        wheelEnabled: false
        visible: true

        TabButton {
            id: tabAction
            x: 0
            y: 0
            text: qsTr("Action")
            visible: true
        }

        TabButton {
            id: tabRandomizer
            x: 72
            y: 0
            text: qsTr("Randomizer")
        }

        TabButton {
            id: tabSettings
            x: 183
            y: 0
            text: qsTr("Settings")
        }

        TabButton {
            id: tabCredits
            x: 270
            y: 0
            text: qsTr("Credits / Help")
        }
    }

    StackLayout {
        id: stackLay
        x: 0
        y: 22
        width: parent.width
        currentIndex: tabBar.currentIndex
        Item {
            id: action

            GroupBox {
                id: gbAction
                x: 297
                y: 201
                width: 283
                height: 233
                title: qsTr("Action")

                Button {
                    id: btnRandomize
                    x: 0
                    y: 0
                    width: 259
                    height: 186
                    text: qsTr("Randomize")
                    enabled: false
                    wheelEnabled: false
                }
            }

            GroupBox {
                id: gbSeedOptions
                x: 0
                y: 201
                width: 281
                height: 233
                title: qsTr("Seed Options")

                Button {
                    id: btnGenRand
                    x: 0
                    y: 33
                    width: 257
                    height: 153
                    text: qsTr("Generate Random")
                }

                TextInput {
                    id: txtSeed
                    width: 257
                    height: 27
                    color: "#ffffff"
                    text: qsTr("7681239")
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20

                    MouseArea {
                        id: mouseArea
                        x: -12
                        y: -35
                        anchors.fill: parent
                        cursorShape: Qt.IBeamCursor
                        acceptedButtons: Qt.NoButton
                    }
                }
            }

            GroupBox {
                id: gbFileOptions
                x: 0
                y: 54
                width: 580
                height: 141
                topPadding: 10
                padding: 10
                visible: true
                wheelEnabled: false
                title: qsTr("File Options")

                Button {
                    id: btnLoadSlusMrg
                    x: 0
                    y: 14
                    width: 165
                    height: 84
                    text: qsTr("Load SLUS/MRG")
                }

                Button {
                    id: btnLoadGame
                    x: 171
                    y: 14
                    width: 165
                    height: 84
                    text: qsTr("Load Game (.cue/.bin)")
                }

                Label {
                    id: label
                    x: 0
                    y: 104
                    text: qsTr("Path: Nothing selected.")
                }

                Button {
                    id: btnPatchIso
                    x: 342
                    y: 14
                    width: 218
                    height: 84
                    text: qsTr("Patch ISO")
                    enabled: false
                }
            }
        }
        Item {
            id: randomizer

            GroupBox {
                id: gbOptions
                x: 0
                y: 53
                width: 405
                height: 263
                title: qsTr("Options")

                CheckBox {
                    id: chkRandAttrib
                    x: 0
                    y: 0
                    text: qsTr("Randomize attributes")
                    padding: 0

                    MouseArea {
                        id: mouseArea9
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.PointingHandCursor
                        anchors.fill: parent
                    }
                }

                CheckBox {
                    id: chkRandGuardStars
                    x: 0
                    y: 38
                    text: qsTr("Randomize guardian stars")
                    padding: 0

                    MouseArea {
                        id: mouseArea10
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.PointingHandCursor
                        anchors.fill: parent
                    }
                }

                CheckBox {
                    id: chkAlGlitchGuardStars
                    x: 0
                    y: 76
                    text: qsTr("Allow glitch guardian stars")
                    padding: 0

                    MouseArea {
                        id: mouseArea11
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.PointingHandCursor
                        anchors.fill: parent
                    }
                }

                CheckBox {
                    id: chkEnAtkDefScramble
                    x: 0
                    y: 111
                    text: qsTr("Enable ATK/DEF scramble")
                    padding: 0

                    MouseArea {
                        id: mouseArea12
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.PointingHandCursor
                        anchors.fill: parent
                    }
                }

                CheckBox {
                    id: chkZeroGlitchFuse
                    x: 0
                    y: 149
                    text: qsTr("'000' glitch fusions")
                    padding: 0

                    MouseArea {
                        id: mouseArea13
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.PointingHandCursor
                        anchors.fill: parent
                    }
                }

                CheckBox {
                    id: chkRandType
                    x: 203
                    y: 0
                    text: qsTr("Randomize types")
                    padding: 0

                    MouseArea {
                        id: mouseArea14
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.PointingHandCursor
                        anchors.fill: parent
                    }
                }

                CheckBox {
                    id: chkRandCardDrop
                    x: 203
                    y: 38
                    text: qsTr("Randomize card drops")
                    padding: 0

                    MouseArea {
                        id: mouseArea15
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.PointingHandCursor
                        anchors.fill: parent
                    }
                }

                CheckBox {
                    id: chkRandDuelistDeck
                    x: 203
                    y: 76
                    text: qsTr("Randomize duelist decks")
                    padding: 0

                    MouseArea {
                        id: mouseArea16
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.PointingHandCursor
                        anchors.fill: parent
                    }
                }

                CheckBox {
                    id: chkRandEquip
                    x: 203
                    y: 114
                    text: qsTr("Randomize equips")
                    padding: 0

                    MouseArea {
                        id: mouseArea17
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.PointingHandCursor
                        anchors.fill: parent
                    }
                }

                CheckBox {
                    id: chkRandFuse
                    x: 203
                    y: 149
                    text: qsTr("Randomize fusions")
                    padding: 0

                    MouseArea {
                        id: mouseArea18
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.PointingHandCursor
                        anchors.fill: parent
                    }
                }

                CheckBox {
                    id: chkRandStarCost
                    x: 203
                    y: 187
                    text: qsTr("Randomize starchip costs")
                    padding: 0

                    MouseArea {
                        id: mouseArea19
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.PointingHandCursor
                        anchors.fill: parent
                    }
                }

                CheckBox {
                    id: chkRandPass
                    x: 0
                    y: 187
                    text: qsTr("Randomize passwords")
                    padding: 0

                    MouseArea {
                        id: mouseArea20
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.PointingHandCursor
                        anchors.fill: parent
                    }
                }
            }

            GroupBox {
                id: gbDropRate
                x: 0
                y: 322
                width: 205
                height: 110
                enabled: chkRandCardDrop.checked
                title: qsTr("Drop rate")

                RangeSlider {
                    id: rsDropRate
                    x: -12
                    y: 17
                    width: 205
                    height: 58
                    second.value: txtMaxDrop.text
                    first.value: txtMinDrop.text
                    snapMode: RangeSlider.SnapAlways
                    stepSize: 1
                    to: 2048
                    from: 1
                }

                TextInput {
                    id: txtMinDrop
                    y: 0
                    width: 35
                    height: 20
                    color: "#ffffff"
                    text: Math.floor(rsDropRate.first.value)
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 15

                    MouseArea {
                        id: mouseArea1
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.IBeamCursor
                        anchors.fill: parent
                    }
                }

                TextInput {
                    id: txtMaxDrop
                    x: 150
                    y: 0
                    width: 31
                    height: 20
                    color: "#ffffff"
                    text: Math.floor(rsDropRate.second.value)
                    horizontalAlignment: Text.AlignRight
                    font.pixelSize: 15

                    MouseArea {
                        id: mouseArea2
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.IBeamCursor
                        anchors.fill: parent
                    }
                }
            }

            GroupBox {
                id: gb
                x: 211
                y: 322
                width: 194
                height: 110
                enabled: chkRandStarCost.checked
                title: qsTr("Starchip cost")

                RangeSlider {
                    id: rsStarCost
                    x: -12
                    y: 18
                    width: 194
                    height: 57
                    second.value: txtMaxStarCost.text
                    first.value: txtMinStarCost.text
                    stepSize: 5
                    to: 999999
                    snapMode: RangeSlider.SnapAlways
                }

                TextInput {
                    id: txtMinStarCost
                    x: 0
                    y: 0
                    width: 57
                    height: 20
                    color: "#ffffff"
                    text: Math.floor(rsStarCost.first.value)
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 15

                    MouseArea {
                        id: mouseArea3
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.IBeamCursor
                        anchors.fill: parent
                    }
                }

                TextInput {
                    id: txtMaxStarCost
                    x: 119
                    y: 0
                    width: 51
                    height: 20
                    color: "#ffffff"
                    text: Math.floor(rsStarCost.second.value)
                    horizontalAlignment: Text.AlignRight
                    font.pixelSize: 15

                    MouseArea {
                        id: mouseArea4
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.IBeamCursor
                        anchors.fill: parent
                    }
                }
            }

            GroupBox {
                id: gbAtkDef
                x: 411
                y: 53
                width: 169
                height: 379
                enabled: chkEnAtkDefScramble.checked
                title: qsTr("ATK/DEF options")

                RangeSlider {
                    id: rsAttack
                    x: 0
                    y: 66
                    width: 48
                    height: 240
                    second.value: txtMaxAtk.text
                    first.value: txtMinAtk.text
                    stepSize: 1
                    to: 9999
                    orientation: Qt.Vertical
                }

                RangeSlider {
                    id: rsDefense
                    x: 98
                    y: 66
                    width: 48
                    height: 240
                    second.value: txtMaxDef.text
                    first.value: txtMinDef.text
                    stepSize: 1
                    to: 9999
                    orientation: Qt.Vertical
                }

                Label {
                    id: label1
                    x: 5
                    y: 0
                    text: qsTr("Attack")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                Label {
                    id: label2
                    x: 93
                    y: 0
                    text: qsTr("Defense")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                TextInput {
                    id: txtMaxAtk
                    x: -1
                    y: 40
                    width: 50
                    height: 20
                    color: "#ffffff"
                    text: Math.floor(rsAttack.second.value)
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 15

                    MouseArea {
                        id: mouseArea5
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.IBeamCursor
                        anchors.fill: parent
                    }
                }

                TextInput {
                    id: txtMinAtk
                    x: -2
                    y: 312
                    width: 53
                    height: 20
                    color: "#ffffff"
                    text: Math.floor(rsAttack.first.value)
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 15

                    MouseArea {
                        id: mouseArea6
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.IBeamCursor
                        anchors.fill: parent
                    }
                }

                TextInput {
                    id: txtMaxDef
                    x: 101
                    y: 40
                    width: 41
                    height: 20
                    color: "#ffffff"
                    text: Math.floor(rsDefense.second.value)
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 15

                    MouseArea {
                        id: mouseArea7
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.IBeamCursor
                        anchors.fill: parent
                    }
                }

                TextInput {
                    id: txtMinDef
                    x: 95
                    y: 312
                    width: 53
                    height: 20
                    color: "#ffffff"
                    text: Math.floor(rsDefense.first.value)
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 15

                    MouseArea {
                        id: mouseArea8
                        x: -12
                        y: -35
                        acceptedButtons: Qt.NoButton
                        cursorShape: Qt.IBeamCursor
                        anchors.fill: parent
                    }
                }

                ToolSeparator {
                    id: toolSeparator
                    x: 60
                    y: -10
                    width: 25
                    height: 354
                }
            }
        }
        Item {
            id: settings
        }
        Item {
            id: credits
        }
    }

    Button {
        id: btnExit
        x: 552
        y: -16
        width: 38
        height: 38
        text: qsTr("X")
    }

    BusyIndicator {
        id: biHeavyProc
        x: -10
        y: -10
        width: 600
        height: 470
        running: false
        enabled: true
    }
}


/*##^## Designer {
    D{i:15;anchors_height:44;anchors_width:580;anchors_x:0;anchors_y:0}
}
 ##^##*/
