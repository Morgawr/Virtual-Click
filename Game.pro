HEADERS += \
    Game/stdafx.h \
    Angel/Angel.h \
    Game/include/ScreenManager.h \
    Game/include/Screen.h \
    Game/include/Screens/TestScreen.h \
    Game/include/Screens/TestScreen2.h \
    Game/include/Screens/BackgroundScreen.h \
    Game/include/Screens/DialogueScreen.h \
    Angel/Scripting/LuaModule.h \
    Game/include/Entities/Player.h \
    Game/include/Entities/Item.h \
    Game/include/PathNames.h \
    Game/include/Screens/TransitionScreen.h \
    Game/include/Utils/LuaManager.h \
    Game/include/Entities/ItemState.h

SOURCES += \
    Angel/Scripting/Interfaces/AngelLuaWrapping.cpp \
    Game/stdafx.cpp \
    Game/Main.cpp \
    Game/src/ScreenManager.cpp \
    Game/src/Screen.cpp \
    Game/src/Screens/TestScreen.cpp \
    Game/src/Screens/TestScreen2.cpp \
    Game/src/Screens/BackgroundScreen.cpp \
    Game/src/Screens/DialogueScreen.cpp \
    Game/src/Entities/Player.cpp \
    Game/src/Entities/Item.cpp \
    Game/src/Screens/TransitionScreen.cpp \
    Game/src/Utils/LuaManager.cpp \
    Game/src/Entities/ItemState.cpp

OTHER_FILES +=
