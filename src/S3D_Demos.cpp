class Demo
{
public:
	virtual void Load(S3D_Renderer* renderer) {}
	virtual void Unload(S3D_Renderer* renderer) {}

	virtual void Update(S3D_Renderer* renderer) {}
	virtual void Draw(S3D_Renderer* renderer) {}
};

// Screen-space gradient
class Demo1 : public Demo
{
public:
	void Update(S3D_Renderer* renderer) final
	{
		float t = sinf(GetTime()) * 0.5f + 0.5f;
		//Color color = WHITE;
		//color.g++; // "Overflow"  -- wraps from highest (255) to lowest (0)
		//color.g--; // "Underflow" -- wraps from lowest (0) to 255 (highest)
		// If you pass a value less than 0.0 or greater than 1.0 to ColorFromNormalized, expect problems!
		for (int x = 0; x < renderer->width; x++)
		{
			for (int y = 0; y < renderer->height; y++)
			{
				float u = x / (float)(renderer->width  - 1);
				float v = y / (float)(renderer->height - 1);
				Color color = ColorFromNormalized({ u, v, t, 1.0f });
				S3D_SetPixelColor(renderer->color_buffer, x, y, color);
			}
		}
	}
};

// NDC circle
class Demo2 : public Demo
{
public:
	void Update(S3D_Renderer* renderer) final
	{
		for (int y = 0; y < renderer->height; y++)
		{
			for (int x = 0; x < renderer->width; x++)
			{
				// ColorFromNormalized will overflow unless we clamp!
				float d = fminf(Vector3Length(S3D_ScreenToNDC(renderer, { x, y })), 1.0f);
				Color color = ColorFromNormalized({ d, d, d, d });
				S3D_SetPixelColor(renderer->color_buffer, x, y, color);
			}
		}
	}
};

class Demo3 : public Demo
{
public:
	void Update(S3D_Renderer* renderer) final
	{
		S3D_ClearColor(renderer, BLACK);
	}
};
