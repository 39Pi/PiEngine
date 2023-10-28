max_mov = 1
current_mov = 1
mov_speed = 2

max_rot = 3.14
current_rot = 1
rot_speed = 1

function onAttach(object)
	print("onAttach()")

	print("object = ", object)
	print("object.rot = ", object.rot)
	
	object.rot = rot.new(0, 0, 0)
end

function loop(renderObject, deltaTime)
	-- print("loop()")
	local rot = renderObject.rot
	rot = rot + rot.new(rot_speed * deltaTime * current_rot)
	if(rot.around_x > max_rot) then
		current_rot = -1
	elseif(rot.around_x < -max_rot) then
		current_rot = 1
	end

	local pos = renderObject.pos
	pos = pos + pos.new(mov_speed * deltaTime * current_mov)
	if(pos.x > max_mov) then
		current_mov = -1
	elseif(pos.x < -max_mov) then
		current_mov = 1
	end

	renderObject.rot = rot
	renderObject.pos = pos
end
