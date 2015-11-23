--
-- Created by IntelliJ IDEA.
-- User: stephan
-- Date: 17.11.15
-- Time: 14:15
-- To change this template use File | Settings | File Templates.
--

local game = {}
game.gui = {}

local ffi = require("ffi")
ffi.cdef[[
void LoadGUIByFile(const char * name);
]]
game.gui.LoadFile = ffi.C.LoadGUIByFile

ffi.cdef[[
void LoadGUIByURL(const char * name);
]]
game.gui.LoadURL = ffi.C.LoadGUIByURL

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
