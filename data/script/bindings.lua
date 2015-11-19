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

ffi.cdef[[
void PrintRenderer();
]]
game.PrintRenderer = ffi.C.PrintRenderer

ffi.cdef[[
void AddTextureDir(const char* name);
]]
game.AddTextureDir = ffi.C.AddTextureDir

ffi.cdef[[
void AddMapDir(const char* name);
]]
game.AddMapDir = ffi.C.AddMapDir

ffi.cdef[[
void AddModelDir(const char* name);
]]
game.AddModelDir = ffi.C.AddModelDir
return game
