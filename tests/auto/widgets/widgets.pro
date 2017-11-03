QT_FOR_CONFIG += webengine

TEMPLATE = subdirs

SUBDIRS += \
    qwebenginedefaultsurfaceformat \
    qwebenginedownloads \
    qwebenginefaviconmanager \
    qwebenginepage \
    qwebenginehistory \
    qwebenginehistoryinterface \
    qwebengineinspector \
    qwebengineprofile \
    qwebengineschemes \
    qwebenginescript \
    qwebenginesettings \
    qwebengineview

qtConfig(accessibility) {
    SUBDIRS += qwebengineaccessibility
}

qtConfig(spellchecker):!cross_compile {
    !qtConfig(native-spellchecker) {
        SUBDIRS += qwebenginespellcheck
    } else {
        message("Spellcheck test will not be built because it depends on usage of Hunspell dictionaries.")
    }
}

# QTBUG-60268
boot2qt: SUBDIRS -= qwebengineaccessibility qwebenginedefaultsurfaceformat \
                    qwebenginefaviconmanager qwebenginepage qwebenginehistory \
                    qwebengineprofile qwebengineschemes qwebenginescript \
                    qwebengineview qwebenginedownloads

