import QtQuick 2.9
import QtQuick.Controls.Material 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.4
import Randomizer 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 600
    height: 470
    title: qsTr("FMRandomizer")
    flags: Qt.FramelessWindowHint | Qt.Window

    property bool enRando: false
    property string path: "Nothing selected."
    property bool usedIso: false
    property bool enPatch: false
    property bool busy: false
    property string imgName: ""
    property int theme: Material.Dark
    property int accent: Material.Indigo
    property Config config: options.getConfig()//Qt.createQmlObject('import Randomizer 1.0; import QtQuick.Controls.Material 2.3; Config{ isoPath: ""; slusMrgPath: ""; winTheme: Material.Dark; winAccent: Material.Indigo; isoName: ""; isoNameFlags: 1}', window, "configObject")

    Material.theme: theme
    Material.accent: accent

    onThemeChanged: {
        config.winTheme = theme;
    }
    onAccentChanged: {
        config.winAccent = accent;
    }

    function formatPath(format_path, limit)
    {
        if (limit === undefined) limit = 75;
        var add_dots = format_path.length > limit;
        return format_path.substring(8, Math.min(limit,format_path.length)) + (add_dots ? "..." : "");
    }

    function setFileName(hForm)
    {
        if (hForm.rbPreset.checked){
            var randOptions = "";
            for(var key in hForm.randFlags)
            {
                if (hForm.randFlags[key]) randOptions += key + ",";
            }
            randOptions = randOptions.substring(0, randOptions.length - 1);
            var fn = "FMRandomizer";
            var today = new Date().toDateString();
            if (hForm.chkSeedFlag.checked) fn += "["+hForm.txtSeed.text+"]";
            if (hForm.chkRandOptions.checked) fn += "["+randOptions+"]";
            if (hForm.chkDate.checked) fn += "["+today+"]";
            hForm.txtFileName.text = fn;
        }
    }

    // Seperates logic from UI design
    HomeForm {
        id: hf

        // Give random seed on startup
        Component.onCompleted: {
            var new_seed = 1000000 + Math.floor(Math.random(51) * 59124519);
            txtSeed.text = new_seed;
            options.seed = txtSeed.text;
        }

        property HomeForm self: this
        property var randFlags: ({})
        property string actFileName: ""
        property string oldSeed: "7681239"

        btnSave.onClicked: {
            if (config.configPath.length !== 0) saveSettings.folder = "file:///" + config.configPath;
            saveSettings.open();
        }

        btnLoad.onClicked: {
            if (config.configPath.length !== 0) loadSettings.folder = "file:///" + config.configPath;
            loadSettings.open();
        }

        FileDialog {
            id: saveSettings
            title: "Choose where to save settings to..."
            selectExisting: false
            nameFilters: ["Config file (*.cfg)"]
            onAccepted: {
                var folderPath = folder.toString().substring(8, folder.toString().length);
                config.configPath = folderPath;
                var filePath = fileUrl.toString().substring(8, fileUrl.toString().length);
                options.saveSettings(filePath, config);
            }
        }

        FileDialog {
            id: loadSettings
            title: "Choose file to load settings from..."
            nameFilters: ["Config file (*.cfg)"]
            onAccepted: {
                var filePath = fileUrl.toString().substring(8, fileUrl.toString().length);
                var conf = options.loadSettings(filePath);
                if (conf) {
                    config = conf;

                    // Set the config to the required properties
                    theme = config.winTheme;
                    accent = config.winAccent;
                    var model = hf.cbAccent.model;
                    for (var i = 0; i < model.count; ++i){
                        if (model.get(i).color === accent){
                            hf.cbAccent.currentIndex = i;
                            break;
                        }
                    }
                    hf.chkSeedFlag.checked = (config.isoNameFlags & Config.SEED) !== 0;
                    hf.chkRandOptions.checked = (config.isoNameFlags & Config.RAND_FLAGS) !== 0;
                    hf.chkDate.checked = (config.isoNameFlags & Config.DATE) !== 0;
                    if (!hf.rbPreset.checked) hf.txtFileName.text = config.isoName
                    hf.chkVanillaDrops.checked = config.useVanillaDrops;
                    hf.chkIdToPass.checked = config.cardPassToId;
                    hf.chkSpoiler.checked = config.spoilerFiles;

                    successDial.text = "Successfully loaded settings!";
                    successDial.open();
                }
                else{
                    errorDial.text = "Failed to load given settings file!";
                    errorDial.open();
                }
            }
        }

        chkVanillaDrops.onCheckedChanged: {
            config.useVanillaDrops = chkVanillaDrops.checked;
        }

        chkIdToPass.onCheckedChanged: {
            config.cardPassToId = chkIdToPass.checked;
        }

        chkSpoiler.onCheckedChanged: {
            config.spoilerFiles = chkSpoiler.checked;
        }

        cbAccent.onCurrentIndexChanged: {
            accent = cbAccent.model.get(cbAccent.currentIndex).color;
        }

        rbDark.checked: theme == Material.Dark
        rbDark.onCheckedChanged: {
            if (rbDark.checked) {
                theme = Material.Dark;
            }
        }

        rbLight.checked: theme == Material.Light
        rbLight.onCheckedChanged: {
            if (rbLight.checked){
                theme = Material.Light;
            }
        }

        rbSystem.checked: theme == Material.System
        rbSystem.onCheckedChanged: {
            if (rbSystem.checked) theme = Material.System;
        }

        btnExit.onClicked: {
            window.close();
        }

        btnLoadSlusMrg.onClicked: {
            if (config.slusMrgPath.length !== 0) loadSlusMrg.folder = "file:///" + config.slusMrgPath;
            loadSlusMrg.open();
        }

        btnLoadGame.onClicked: {
            if (config.isoPath.length !== 0) loadBin.folder = "file:///" + config.isoPath;
            loadBin.open();
        }

        lblImagePath.text: "Path selected: " + path

        biHeavyProc.running: busy

        biHeavyProc.onRunningChanged: {
            if (!biHeavyProc.running)
            {
                btnPatchIso.enabled = false;
                btnRandomize.enabled = true;
                successDial.text = "Patching finished!";
                successDial.open();
            }
        }

        btnGenRand.onClicked: {
            var new_seed = 1000000 + Math.floor(Math.random(51) * 59124519);
            txtSeed.text = new_seed;
            options.seed = txtSeed.text;
        }

        FileDialog {
            id: getBinPath
            title: "Choose BIN file to copy..."
            nameFilters: ["BIN file (*.bin)"]
            onAccepted: {
                console.log(folder.toString());
                engine.saveImage(formatPath(fileUrl.toString(), 100000), imgName);
                busy = true;
            }
        }

        btnPatchIso.onClicked: {
            if (!usedIso)
            {
                engine.saveImage("", imgName);
                busy = true;
            }
            else{
                if (config.isoPath.length !== 0) getBinPath.folder = "file:///" + config.isoPath;
                getBinPath.open();
            }
        }

        btnPatchIso.enabled: enPatch

        btnRandomize.enabled: enRando
        btnRandomize.onClicked: {
            engine.shuffleData(options.seed);
            enPatch = true;
            enRando = false;
        }

        txtSeed.onTextChanged: {
            // Check for seed validity
            if (txtSeed.text !== oldSeed){
                var seedCheck = Number(txtSeed.text);
                console.log("New seed is " + seedCheck);
                if (Number.NaN.toString() === seedCheck.toString()){
                    console.log("Attempted set NaN as seed");
                    txtSeed.text = oldSeed;
                    return;
                }
            }

            if (txtSeed.text.length > 9) txtSeed.text = txtSeed.text.substring(0, 9);
            if (txtSeed.text.length === 0) txtSeed.text = "0";
            oldSeed = txtSeed.text;

            setFileName(self);
            options.seed = txtSeed.text;
        }

        rsStarCost.first.onValueChanged: {
            txtMinStarCost.text = rsStarCost.first.value;
        }

        rsStarCost.second.onValueChanged: {
            txtMaxStarCost.text = rsStarCost.second.value;
        }

        rsAttack.first.onValueChanged: {
            txtMinAtk.text = rsAttack.first.value;
        }

        rsAttack.second.onValueChanged: {
            txtMaxAtk.text = rsAttack.second.value;
        }

        rsDefense.first.onValueChanged: {
            txtMinDef.text = rsDefense.first.value;
        }

        rsDefense.second.onValueChanged: {
            txtMaxDef.text = rsDefense.second.value;
        }

        rsDropRate.first.onValueChanged: {
            txtMinDrop.text = rsDropRate.first.value;
        }

        rsDropRate.second.onValueChanged: {
            txtMaxDrop.text = rsDropRate.second.value;
        }

        txtMaxStarCost.onTextChanged: {
            if (txtMaxStarCost.text.length === 0) txtMaxStarCost.text = "0";
            if (txtMaxStarCost.text.length > 6) txtMaxStarCost.text = txtMaxStarCost.text.substring(0, 6);
            rsStarCost.second.value = Number(txtMaxStarCost.text);
            options.maxStarCost = txtMaxStarCost.text;
        }

        txtMinStarCost.onTextChanged: {
            if (txtMinStarCost.text.length === 0) txtMinStarCost.text = "0";
            if (txtMinStarCost.text.length > 6) txtMinStarCost.text = txtMinStarCost.text.substring(0, 6);
            options.minStarCost = txtMinStarCost.text;
        }

        txtMaxDrop.onTextChanged: {
            if (txtMaxDrop.text.length === 0) txtMaxDrop.text = "1";
            if (txtMaxDrop.text.length > 4) txtMaxDrop.text = txtMaxDrop.text.substring(0, 4);
            if (Number(txtMaxDrop.text) > 2048) txtMaxDrop.text = "2048";
            options.maxDrop = txtMaxDrop.text;
        }

        txtMinDrop.onTextChanged: {
            if (txtMinDrop.text.length === 0) txtMinDrop.text = "1";
            if (txtMinDrop.text.length > 4) txtMinDrop.text = txtMinDrop.text.substring(0, 4);
            if (Number(txtMinDrop.text) > 2048) txtMinDrop.text = "2048";
            options.minDrop = txtMinDrop.text;
        }

        txtMaxDef.onTextChanged: {
            if (txtMaxDef.text.length === 0) txtMaxDef.text = "0";
            if (txtMaxDef.text.length > 4) txtMaxDef.text = txtMaxDef.text.substring(0, 4);
            options.maxDef = txtMaxDef.text;
        }

        txtMinDef.onTextChanged: {
            if (txtMinDef.text.length === 0) txtMinDef.text = "0";
            if (txtMinDef.text.length > 4) txtMinDef.text = txtMinDef.text.substring(0, 4);
            options.minDef = txtMinDef.text;
        }

        txtMaxAtk.onTextChanged: {
            if (txtMaxAtk.text.length === 0) txtMaxAtk.text = "0";
            if (txtMaxAtk.text.length > 4) txtMaxAtk.text = txtMaxAtk.text.substring(0, 4);
            options.maxAtk = txtMaxAtk.text;
        }

        txtMinAtk.onTextChanged: {
            if (txtMinAtk.text.length === 0) txtMinAtk.text = "0";
            if (txtMinAtk.text.length > 4) txtMinAtk.text = txtMinAtk.text.substring(0, 4);
            options.minAtk = txtMinAtk.text;
        }

        chkRandAttrib.onCheckedChanged: {
            randFlags["Attributes"] = chkRandAttrib.checked;
            setFileName(self);
            options.randAttrib = chkRandAttrib.checked;
        }

        chkRandPass.onCheckedChanged: {
            randFlags["Passwords"] = chkRandPass.checked;
            setFileName(self);
            options.randPass = chkRandPass.checked;
        }

        chkRandStarCost.onCheckedChanged: {
            randFlags["Star Cost"] = chkRandStarCost.checked;
            setFileName(self);
            options.randStarCost = chkRandStarCost.checked;
        }

        chkRandFuse.onCheckedChanged: {
            randFlags["Fusions"] = chkRandFuse.checked;
            setFileName(self);
            options.randFuse = chkRandFuse.checked;
        }

        chkRandEquip.onCheckedChanged: {
            randFlags["Equips"] = chkRandEquip.checked;
            setFileName(self);
            options.randEquip = chkRandEquip.checked;
        }

        chkRandDuelistDeck.onCheckedChanged: {
            randFlags["Duelist Decks"] = chkRandDuelistDeck.checked;
            setFileName(self);
            options.randDuelistDeck = chkRandDuelistDeck.checked;
        }

        chkRandCardDrop.onCheckedChanged: {
            randFlags["Card Drops"] = chkRandCardDrop.checked;
            setFileName(self);
            options.randCardDrop = chkRandCardDrop.checked;
        }

        chkRandType.onCheckedChanged: {
            randFlags["Types"] = chkRandType.checked;
            setFileName(self);
            options.randType = chkRandType.checked;
        }

        chkZeroGlitchFuse.onCheckedChanged: {
            randFlags["000 Fusions"] = chkZeroGlitchFuse.checked;
            setFileName(self);
            options.zeroGlitchFuse = chkZeroGlitchFuse.checked;
        }

        chkEnAtkDefScramble.onCheckedChanged: {
            randFlags["AtkDef"] = chkEnAtkDefScramble.checked;
            setFileName(self);
            options.enAtkDefScramble = chkEnAtkDefScramble.checked;
        }

        chkAlGlitchGuardStars.onCheckedChanged: {
            randFlags["Glitch Guard Stars"] = chkAlGlitchGuardStars.checked;
            setFileName(self);
            options.alGlitchGuardStars = chkAlGlitchGuardStars.checked;
        }

        chkRandGuardStars.onCheckedChanged: {
            randFlags["Guard Stars"] = chkRandGuardStars.checked;
            setFileName(self);
            options.randGuardStars = chkRandGuardStars.checked;
        }

        rbPreset.onCheckedChanged: {
            if (!rbPreset.checked){
                txtFileName.text = config.isoName;
            }

            setFileName(self);
        }

        chkSeedFlag.onCheckedChanged: { config.isoNameFlags |= Config.SEED; setFileName(self); }
        chkDate.onCheckedChanged: { config.isoNameFlags |= Config.DATE; setFileName(self); }
        chkRandOptions.onCheckedChanged: { config.isoNameFlags |= Config.RAND_FLAGS; setFileName(self); }

        txtFileName.onTextChanged: {
            actFileName = txtFileName.text;
            imgName = actFileName;
            if (!rbPreset.checked) config.isoName = imgName;
            if (txtFileName.text.length > 61){
                console.log("Character limit reached on filename");
                txtFileName.text = txtFileName.text.substring(0, 61);
                if (rbPreset.checked) txtFileName.text += "...";
            }
            else if (txtFileName.text.length > 46){
                txtFileName.font.pixelSize = 10;
            }
            else if (txtFileName.text.length > 38){
                txtFileName.font.pixelSize = 14;
            }
            else{
                txtFileName.font.pixelSize = 18;
            }
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
                    config.slusMrgPath = folder.toString().substring(8, folder.toString().length);
                    var res = engine.loadSlusMrg(slus_path, mrg_str.substring(8, mrg_str.length))
                    if (!res)
                    {
                        errorDial.text = "Chosen files are not supported or can not be opened!";
                        errorDial.open();
                    }
                    else
                    {
                        enRando = true;
                        usedIso = true;
                        path = formatPath(folder.toString());
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

        MessageDialog {
            id: successDial
            title: "Patched successfully!"
            icon: StandardIcon.Information
            standardButtons: StandardButton.Ok
        }

        FileDialog {
            id: loadBin
            title: "Select BIN file to copy/extract from..."
            nameFilters: ["BIN file (*.bin)"]
            onAccepted: {
                var pth = fileUrl.toString();
                var res = engine.loadCueBin(pth.substring(8, pth.length));
                if (!res)
                {
                    errorDial.text = "Chosen file is not supported or can not be opened!";
                    errorDial.open();
                }
                else
                {
                    config.isoPath = folder.toString().substring(8, folder.toString().length);
                    usedIso = false;
                    enRando = true;
                    path = formatPath(pth);
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
