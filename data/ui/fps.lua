function UpdateFPS(document)
	local fps = document.context.focus_element
	fps.inner_rml = Game.GetFPS()
end