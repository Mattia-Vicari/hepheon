local exports = {}

local width = 1080
local height = 720
local fullscreen = false 
local window_title = "Hepheon - Game Engine"

local function set()
    _set_width(width)
    _set_height(height)
    _set_fullscreen(fullscreen)
    _set_window_title(window_title)
end

exports.set = set

return exports