import qbs 1.0

StaticLibrary {
    name: "qsyncable"
    Depends { name: "cpp" }
    cpp.cxxLanguageVersion:"c++14"
    cpp.includePaths: sourceDirectory
    Depends { name: "Qt"; submodules: ["core", "qml"] }
    files: [
        "qsdiffrunner.h",
        "qspatch.h",
        "qspatchable.h",
        "qslistmodel.h",
        "qsuuid.h",
        "priv/qsdiffrunneralgo_p.h",
        "priv/qstree.h",
        "priv/qstreenode.h",
        "qsjsonlistmodel.h",
        "QSDiffRunner",
        "QSListModel",
        "qsyncablefunctions.h",
        "qsyncableqmlwrapper.h",
        "priv/qsalgotypes_p.h",
        "priv/qsimmutablewrapper_p.h",
        "priv/qsfastdiffrunneralgo_p.h",
        "qsfastdiffrunner.h",
        "qsdiffrunner.cpp",
        "qspatch.cpp",
        "qslistmodel.cpp",
        "qsuuid.cpp",
        "qsdiffrunneralgo.cpp",
        "qstree.cpp",
        "qstreenode.cpp",
        "qsjsonlistmodel.cpp",
        "qsyncableqmltypes.cpp",
        "qsyncablefunctions.cpp",
        "qsyncableqmlwrapper.cpp"
    ]

    Export {
        Depends { name: "Qt.quick" }
        Depends { name: "cpp" }
        cpp.includePaths: [ "" ]
    }
}
