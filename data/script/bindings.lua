--
-- Created by IntelliJ IDEA.
-- User: stephan
-- Date: 17.11.15
-- Time: 14:15
-- To change this template use File | Settings | File Templates.
--

local game = {}
local ffi = require("ffi")
ffi.cdef[[
void LoadGUI(const char * name);
]]

game.LoadGUI = ffi.C.LoadGUI

return game
