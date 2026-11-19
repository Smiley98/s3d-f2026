
void S3D_DrawLineX(S3D_Renderer* renderer, int row, int x0, int x1, Color color)
{
	if (x0 > x1) std::swap(x0, x1);

	S3D_Rectangle bounds;
	bounds.min.x = x0;
	bounds.max.x = x1;
	bounds.min.y = row;
	bounds.max.y = row;
	assert(S3D_CheckScreenContainsRec(renderer, bounds));

	for (int x = x0; x <= x1; x++)
	{
		S3D_SetPixelColor(renderer->color_buffer, x, row, color);
	}
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

	for (int y = y0; y <= y1; y++)
	{
		S3D_SetPixelColor(renderer->color_buffer, col, y, color);
	}
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
	assert(S3D_CheckScreenContainsRec(renderer, bounds));

	if (ColorIsEqual(color1, BLANK))
	{
		color1 = color0;
	}

	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	float x_step = dx / (float)steps;
	float y_step = dy / (float)steps;

	float x = (float)x0;
	float y = (float)y0;
	// set pixel at x, y
	S3D_SetPixelColor(renderer->color_buffer, x, y, color0);
	for (int i = 0; i < steps; i++)
	{
		x += x_step;
		y += y_step;
		Color color = ColorLerp(color0, color1, i / (float)steps);
		S3D_SetPixelColor(renderer->color_buffer, x, y, color);
	}
}
