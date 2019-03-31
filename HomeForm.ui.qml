import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

Page {
    id: page
    width: 600
    height: 470
    property alias chkVanillaDrops: chkVanillaDrops
    property alias btnSave: btnSave
    property alias btnLoad: btnLoad
    property alias cbAccent: cbAccent
    property alias rbLight: rbLight
    property alias rbSystem: rbSystem
    property alias rbDark: rbDark
    property alias chkSpoiler: chkSpoiler
    property alias chkDate: chkDate
    property alias chkRandOptions: chkRandOptions
    property alias chkSeedFlag: chkSeedFlag
    property alias chkIdToPass: chkIdToPass
    property alias rbPreset: rbPreset
    property alias txtFileName: txtFileName
    property alias txtMaxStarCost: txtMaxStarCost
    property alias txtMinStarCost: txtMinStarCost
    property alias txtMaxDrop: txtMaxDrop
    property alias txtMinDrop: txtMinDrop
    property alias txtMinDef: txtMinDef
    property alias txtMaxDef: txtMaxDef
    property alias txtMinAtk: txtMinAtk
    property alias txtMaxAtk: txtMaxAtk
    property alias lblTitle: lblTitle
    property alias lblImagePath: lblImagePath
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
        spacing: 3
        currentIndex: 0
        wheelEnabled: true
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
                    color: "#0797ab"
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
                clip: false
                hoverEnabled: true
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
                    id: lblImagePath
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
                    color: "#0797ab"
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
                    color: "#0797ab"
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
                    color: "#0797ab"
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
                    color: "#0797ab"
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
                    color: "#0797ab"
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
                    color: "#0797ab"
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
                    color: "#0797ab"
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
                    color: "#0797ab"
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

            GroupBox {
                id: gbFileName
                x: 0
                y: 54
                width: 580
                height: 115
                title: qsTr("File name")

                TextInput {
                    id: txtFileName
                    x: 0
                    y: 48
                    width: 540
                    height: 20
                    color: "#0797ab"
                    text: qsTr("FMRandomizer[7681239]")
                    passwordCharacter: ""
                    readOnly: rbPreset.checked
                    echoMode: TextInput.Normal
                    font.pixelSize: 18

                    MouseArea {
                        id: mouseArea21
                        x: -12
                        y: -35
                        anchors.fill: parent
                        cursorShape: Qt.IBeamCursor
                        acceptedButtons: Qt.NoButton
                    }
                }

                RadioButton {
                    id: rbCustom
                    x: 0
                    y: -6
                    text: qsTr("Custom")
                    checkable: true

                    MouseArea {
                        id: mouseArea29
                        x: -12
                        y: -35
                        cursorShape: Qt.PointingHandCursor
                        acceptedButtons: Qt.NoButton
                        anchors.fill: parent
                    }
                }

                RadioButton {
                    id: rbPreset
                    x: 97
                    y: -6
                    text: qsTr("Preset")
                    checked: true

                    MouseArea {
                        id: mouseArea30
                        x: -12
                        y: -35
                        cursorShape: Qt.PointingHandCursor
                        acceptedButtons: Qt.NoButton
                        anchors.fill: parent
                    }
                }

                GroupBox {
                    id: gbPresetFlags
                    x: 192
                    y: -6
                    width: 348
                    height: 48
                    enabled: rbPreset.checked
                    font.pointSize: 9
                    title: qsTr("Preset flags")

                    CheckBox {
                        id: chkSeedFlag
                        x: -12
                        y: -23
                        text: qsTr("Seed")
                        checked: true

                        MouseArea {
                            id: mouseArea22
                            x: -12
                            y: -35
                            cursorShape: Qt.PointingHandCursor
                            acceptedButtons: Qt.NoButton
                            anchors.fill: parent
                        }
                    }

                    CheckBox {
                        id: chkRandOptions
                        x: 62
                        y: -23
                        text: qsTr("Randomizer options")

                        MouseArea {
                            id: mouseArea23
                            x: -12
                            y: -35
                            cursorShape: Qt.PointingHandCursor
                            acceptedButtons: Qt.NoButton
                            anchors.fill: parent
                        }
                    }

                    CheckBox {
                        id: chkDate
                        x: 216
                        y: -22
                        text: qsTr("Date")

                        MouseArea {
                            id: mouseArea24
                            x: -12
                            y: -35
                            cursorShape: Qt.PointingHandCursor
                            acceptedButtons: Qt.NoButton
                            anchors.fill: parent
                        }
                    }
                }
            }

            GroupBox {
                id: gbLogic
                x: 0
                y: 175
                width: 290
                height: 142
                title: qsTr("Randomizer logic")

                CheckBox {
                    id: chkIdToPass
                    x: 0
                    y: 0
                    text: qsTr("Card passwords to card IDs")
                    padding: 1
                    checked: false

                    MouseArea {
                        id: mouseArea26
                        x: -12
                        y: -35
                        cursorShape: Qt.PointingHandCursor
                        acceptedButtons: Qt.NoButton
                        anchors.fill: parent
                    }
                }

                CheckBox {
                    id: chkTextHints
                    x: 0
                    y: 61
                    text: qsTr("In-game text hints(WIP)")
                    padding: 1
                    enabled: false
                    checkable: true

                    MouseArea {
                        id: mouseArea28
                        x: -12
                        y: -35
                        cursorShape: Qt.PointingHandCursor
                        acceptedButtons: Qt.NoButton
                        anchors.fill: parent
                    }
                }

                CheckBox {
                    id: chkVanillaDrops
                    x: 0
                    y: 31
                    text: qsTr("Use vanilla drop rates")
                    display: AbstractButton.TextBesideIcon
                    padding: 1

                    MouseArea {
                        id: mouseArea27
                        x: -12
                        y: -35
                        cursorShape: Qt.PointingHandCursor
                        acceptedButtons: Qt.NoButton
                        anchors.fill: parent
                    }
                }
            }

            GroupBox {
                id: gbMisc
                x: 296
                y: 175
                width: 284
                height: 253
                title: qsTr("Miscellaneous")

                CheckBox {
                    id: chkSpoiler
                    x: 0
                    y: 0
                    text: qsTr("Generate spoiler files")

                    MouseArea {
                        id: mouseArea25
                        x: -12
                        y: -35
                        cursorShape: Qt.PointingHandCursor
                        acceptedButtons: Qt.NoButton
                        anchors.fill: parent
                    }
                }

                GroupBox {
                    id: gbTheme
                    x: 0
                    y: 54
                    width: 260
                    height: 76
                    title: qsTr("Theme")

                    RadioButton {
                        id: rbDark
                        x: 82
                        y: -9
                        text: qsTr("Dark")
                        checked: true

                        MouseArea {
                            id: mouseArea32
                            x: -12
                            y: -35
                            cursorShape: Qt.PointingHandCursor
                            acceptedButtons: Qt.NoButton
                            anchors.fill: parent
                        }
                    }

                    RadioButton {
                        id: rbLight
                        x: 173
                        y: -9
                        text: qsTr("Light")

                        MouseArea {
                            id: mouseArea33
                            x: -12
                            y: -35
                            cursorShape: Qt.PointingHandCursor
                            acceptedButtons: Qt.NoButton
                            anchors.fill: parent
                        }
                    }

                    RadioButton {
                        id: rbSystem
                        x: -12
                        y: -9
                        text: qsTr("System")

                        MouseArea {
                            id: mouseArea31
                            x: -12
                            y: -35
                            cursorShape: Qt.PointingHandCursor
                            acceptedButtons: Qt.NoButton
                            anchors.fill: parent
                        }
                    }
                }

                ComboBox {
                    id: cbAccent
                    x: 0
                    y: 158
                    width: 260
                    height: 48
                    displayText: cbAccent.currentText
                    focusPolicy: Qt.WheelFocus
                    wheelEnabled: true
                    currentIndex: 9
                    textRole: "text"
                    model: ListModel {
                        id: cbLmColors
                        ListElement {
                            text: "Amber"
                            color: Material.Amber
                        }
                        ListElement {
                            text: "Blue"
                            color: Material.Blue
                        }
                        ListElement {
                            text: "Blue Grey"
                            color: Material.BlueGrey
                        }
                        ListElement {
                            text: "Brown"
                            color: Material.Brown
                        }
                        ListElement {
                            text: "Cyan"
                            color: Material.Cyan
                        }
                        ListElement {
                            text: "Deep Orange"
                            color: Material.DeepOrange
                        }
                        ListElement {
                            text: "Deep Purple"
                            color: Material.DeepPurple
                        }
                        ListElement {
                            text: "Green"
                            color: Material.Green
                        }
                        ListElement {
                            text: "Grey"
                            color: Material.Grey
                        }
                        ListElement {
                            text: "Indigo"
                            color: Material.Indigo
                        }
                        ListElement {
                            text: "Light Blue"
                            color: Material.LightBlue
                        }
                        ListElement {
                            text: "Light Green"
                            color: Material.LightGreen
                        }
                        ListElement {
                            text: "Lime"
                            color: Material.Lime
                        }
                        ListElement {
                            text: "Orange"
                            color: Material.Orange
                        }
                        ListElement {
                            text: "Pink"
                            color: Material.Pink
                        }
                        ListElement {
                            text: "Purple"
                            color: Material.Purple
                        }
                        ListElement {
                            text: "Red"
                            color: Material.Red
                        }
                        ListElement {
                            text: "Teal"
                            color: Material.Teal
                        }
                        ListElement {
                            text: "Yellow"
                            color: Material.Yellow
                        }
                    }

                    MouseArea {
                        id: mouseArea34
                        x: -12
                        y: -35
                        cursorShape: Qt.PointingHandCursor
                        acceptedButtons: Qt.NoButton
                        anchors.fill: parent
                    }
                }

                Label {
                    id: lblThemeAccent
                    x: 0
                    y: 136
                    width: 89
                    height: 16
                    text: qsTr("Theme accent")
                }
            }

            RowLayout {
                id: rowLayout
                x: 0
                y: 318
                width: 290
                height: 110

                Button {
                    id: btnSave
                    text: qsTr("Save")
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

                Button {
                    id: btnLoad
                    text: qsTr("Load")
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }
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

    Label {
        id: lblTitle
        x: 70
        y: -8
        text: qsTr("Yu-Gi-Oh! Forbidden Memories Randomizer")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        font.pointSize: 15
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
    D{i:15;anchors_height:44;anchors_width:580;anchors_x:0;anchors_y:0}D{i:14;anchors_y:54}
}
 ##^##*/
