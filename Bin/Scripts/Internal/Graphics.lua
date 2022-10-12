----------------------------------------------------------------------
--| * Graphics.lua *
----------------------------------------------------------------------

---- Defines
-- Location
TW_LOCATION = SCREEN_WIDTH
TH_LOCATION = SCREEN_HEIGHT

GW_LOCATION = TW_LOCATION
GH_LOCATION = TH_LOCATION

-- Actor
TW_ACTOR = 16
TH_ACTOR = 16

GW_ACTOR = TW_ACTOR
GH_ACTOR = TH_ACTOR

-- Car
TW_CAR = 75
TH_CAR = 21

GW_CAR = TW_CAR
GH_CAR = TH_CAR

-- Dialog
TW_DIALOG = 320
TH_DIALOG = 200

GW_DIALOG = 32
GH_DIALOG = 20

---- Singleton
Graphics = {}

function Graphics.setDrawColor(R, G, B, A)
    setDrawColor(R, G, B, A)
end

--- *** Rect[1] = X, Rect[2] = Y, Rect[3] = W, Rect[4] = H *** ---
function Graphics.drawFrame(RenderMode, ZIndex, IsHUD, Rect, Texture, Row, Frame)
    drawFrame(RenderMode, ZIndex, IsHUD, Rect[1], Rect[2], Rect[3], Rect[4], Texture, Row, Frame)
end

function Graphics.drawText(RenderMode, ZIndex, IsHUD, Rect, Text)
    drawText(RenderMode, ZIndex, IsHUD, Rect[1], Rect[2], Rect[3], Rect[4], Text)
end

function Graphics.fillRect(RenderMode, ZIndex, IsHUD, Rect)
    fillRect(RenderMode, ZIndex, IsHUD, Rect[1], Rect[2], Rect[3], Rect[4])
end

function Graphics.drawRect(RenderMode, ZIndex, IsHUD, Rect)
    drawRect(RenderMode, ZIndex, IsHUD, Rect[1], Rect[2], Rect[3], Rect[4])
end

