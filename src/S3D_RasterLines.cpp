
void S3D_DrawLineX(S3D_Renderer* renderer, int row, int x0, int x1, Color color)
{
	if (x0 > x1) std::swap(x0, x1);

	S3D_Rectangle bounds;
	bounds.min.x = x0;
	bounds.max.x = x1;
	bounds.min.y = row;
	bounds.max.y = row;
	assert(S3D_CheckScreenContainsRec(renderer, bounds));

	// for x in x0 to x1:
	//		set pixel at x, row
}

void S3D_DrawLineY(S3D_Renderer* renderer, int col, int y0, int y1, Color color)
{
	if (y0 > y1) std::swap(y0, y1);

	S3D_Rectangle bounds;
	bounds.min.y = y0;
	bounds.max.y = y1;
	bounds.min.x = col;
	bounds.max.x = col;
	assert(S3D_CheckScreenContainsRec(renderer, bounds));

	// for y in y0 to y1:
	//		set pixel at col, y
}

void S3D_DrawLine(S3D_Renderer* renderer, int x0, int y0, int x1, int y1, Color color0, Color color1 = BLANK)
{
	int dx = x1 - x0;
	int dy = y1 - y0;

	S3D_Rectangle bounds;
	bounds.min.x = x0 < x1 ? x0 : x1;
	bounds.min.y = y0 < y1 ? y0 : y1;
	bounds.max.x = bounds.min.x + abs(dx);
	bounds.max.y = bounds.min.y + abs(dy);
	if (!S3D_CheckScreenContainsRec(renderer, bounds)) return;

	// let steps = abs dx if abs dx > abs dy, else abs dy
	// abs = "absolute value"

	// let xStep = dx / steps as float
	// let yStep = dy / steps as float

	// x = x0
	// y = y0
	// set pixel at x, y
	// for i in steps:
	//		x += xStep
	//		y += yStep
	//		set pixel at x, y
}
