states = { "Open" }

--- Default State

default_spriteWorld = "Box.png"
default_spriteInventory = "Box.png"
default_messageOnSuccess = "BoxSuccess.lua"
default_messageOnFailure = "BoxFailure.lua"
default_messageOnExamine = "Box.lua"
default_workOnItem = "null"
default_combinedItem = "null"
default_generatedEvent = "OpenBox"
default_pickUpAble = true
default_events = { "OpenBox" }
default_OpenBox = "Open"

--- Open State

Open_spriteWorld = "BoxOpen.png"
Open_spriteInventory = "BoxOpen.png"
Open_messageOnSuccess = "OpenBoxSuccess.lua"
Open_messageOnFailure = "BoxFailure.lua"
Open_messageOnExamine = "BoxOpened.lua"
Open_workOnItem = "null"
Open_combinedItem = "null"
Open_generatedEvent = "BoxClosed"
Open_pickUpAble = true
Open_events = { "BoxClosed" }
Open_BoxClosed = "default"
