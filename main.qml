import QtQuick 2.7
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.4

ApplicationWindow {
    id: window
    visible: true
    width: 600
    height: 470
    title: qsTr("FMScrambler")
    flags: Qt.FramelessWindowHint | Qt.Window


    // Seperates logic from UI design
    HomeForm {
        btnExit.onClicked: {
            window.close();
        }

        btnLoadSlusMrg.onClicked: {
            loadSlusMrg.open();
        }

        btnLoadGame.onClicked: {
            loadCue.open();
        }

        btnGenRand.onClicked: {
            var new_seed = 1000000 + Math.floor(Math.random(51) * 59124519);
            txtSeed.text = new_seed;
            options.seed = txtSeed.text;
        }

        txtSeed.onEditingFinished: {
            options.seed = txtSeed.text
        }

        chkRandAttrib.onCheckedChanged: {
            options.randAttrib = chkRandAttrib.checked;
        }

        chkRandPass.onCheckedChanged: {
            options.randPass = chkRandPass.checked;
        }

        chkRandStarCost.onCheckedChanged: {
            options.randStarCost = chkRandStarCost.checked;
        }

        chkRandFuse.onCheckedChanged: {
            options.randFuse = chkRandFuse.checked;
        }

        chkRandEquip.onCheckedChanged: {
            options.randEquip = chkRandEquip.checked;
        }

        chkRandDuelistDeck.onCheckedChanged: {
            options.randDuelistDeck = chkRandDuelistDeck.checked;
        }

        chkRandCardDrop.onCheckedChanged: {
            options.randCardDrop = chkRandCardDrop.checked;
        }

        chkRandType.onCheckedChanged: {
            options.randType = chkRandType.checked;
        }

        chkZeroGlitchFuse.onCheckedChanged: {
            options.zeroGlitchFuse = chkZeroGlitchFuse.checked;
        }

        chkEnAtkDefScramble.onCheckedChanged: {
            options.enAtkDefScramble = chkEnAtkDefScramble.checked;
        }

        chkAlGlitchGuardStars.onCheckedChanged: {
            options.alGlitchGuardStars = chkAlGlitchGuardStars.checked;
        }

        chkRandGuardStars.onCheckedChanged: {
            options.randGuardStars = chkRandGuardStars.checked;
        }

        FileDialog {
            property string slus_path: ""
            id: loadSlusMrg
            title: "Select SLUS file..."
            nameFilters: ["SLUS (SLUS_014.11)"]
            onAccepted: {
                if (nameFilters[0] !== "MRG file (WA_MRG.MRG)")
                {
                    var slus_str = fileUrl.toString();
                    slus_path = slus_str.substring(8, slus_str.length);
                    title = "Select MRG file...";
                    nameFilters = ["MRG file (WA_MRG.MRG)"];
                    open();
                }
                else
                {
                    var mrg_str = fileUrl.toString();
                    title = "Select SLUS file...";
                    nameFilters = ["SLUS (SLUS_014.11)"];
                    var res = loader.loadSlusMrg(slus_path, mrg_str.substring(8, mrg_str.length))
                    if (!res)
                    {
                        errorDial.text = "Chosen files are not supported or can not be opened!";
                        errorDial.open();
                    }
                }
            }
        }

        MessageDialog {
            id: errorDial
            title: "Error!"
            icon: StandardIcon.Critical
            standardButtons: StandardButton.Ok
        }

        FileDialog {
            id: loadCue
            title: "Select CUE file..."
            nameFilters: ["CUE file (*.cue)"]
            onAccepted: {
                var res = loader.loadCueBin(fileUrl);
                if (!res)
                {
                    errorDial.text = "Chosen file is not supported or can not be opened!";
                    errorDial.open();
                }
            }
        }
    }

    //Ability to drag the window
    MouseArea {
        x: 0
        y: 0
        width: 561
        height: 26
        property point clickPos: "1,1"

        onPressed: {
            clickPos  = Qt.point(mouse.x,mouse.y);
        }

        onPositionChanged: {
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y);
            window.x += delta.x;
            window.y += delta.y;
        }
    }
}
