#pragma once

struct RenderObject {
	virtual void draw() = 0;
	virtual ~RenderObject() = default;
};
