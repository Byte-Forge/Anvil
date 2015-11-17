--
-- Created by IntelliJ IDEA.
-- User: stephan
-- Date: 27.10.15
-- Time: 10:36
-- To change this template use File | Settings | File Templates.
--
print("Starting HPSE ")
print("System Information:")
print("Operating System: " .. jit.os)
print("Architecture: " .. jit.arch)

-- Load our gui
local game = require("script.bindings")
game.LoadGUI("ui/index.html")


