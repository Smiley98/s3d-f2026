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
		for (int x = 0; x < renderer->width; x++)
		{
			for (int y = 0; y < renderer->height; y++)
			{
				float u = x / (float)(renderer->width - 1);
				float v = y / (float)(renderer->height - 1);
				Vector3 ndc = S3D_ScreenToNDC(renderer, { x, y }); // [-1..1]

				// Visualize how S3D_ScreenToNDC transforms uvs to screen centre
				//ndc = Vector3Clamp(ndc, Vector3Zeros, Vector3Ones);
				//Color color = ColorFromNormalized({ ndc.x, ndc.y, 0.0f, 1.0f });

				// ColorFromNormalized will overflow unless we clamp!
				float d = Vector3Length(ndc);
				d = fminf(d, 1.0f);
				Color color = ColorFromNormalized({ d, d, d, 1.0f });
				S3D_SetPixelColor(renderer->color_buffer, x, y, color);
			}
		}
	}
};

// Lab 3 (pre-Thursday the 19th at 8am)
class Demo3 : public Demo
{
public:
	void Update(S3D_Renderer* renderer) final
	{
		S3D_ClearColor(renderer, BLACK);

		S3D_Rectangle rec{};
		rec.min.x = renderer->width * 0.4f;
		rec.min.y = renderer->height * 0.4f;
		rec.max.x = renderer->width * 0.6f;
		rec.max.y = renderer->height * 0.6f;

		// Functions you need to implement and test:
		S3D_DrawLineX(renderer, 100, 0, renderer->width - 1, RED);
		S3D_DrawLineY(renderer, 100, 0, renderer->height - 1, GREEN);
		S3D_DrawRectangle(renderer, rec, BLUE);
		S3D_DrawRectangleLines(renderer, rec, MAGENTA);

		Vector2i mouse = S3D_GetMousePosition(renderer);
		S3D_DrawLine(renderer, renderer->width / 2, renderer->height / 2, mouse.x, mouse.y, MAROON, PURPLE);

		int radius = 5;
		if (S3D_CheckScreenContainsCircle(renderer, mouse.x, mouse.y, radius))
		{
			S3D_DrawCircle(renderer, mouse.x, mouse.y, 5, VIOLET);
		}
	}
};

// Alternate lab 3 (After Thursday the 19th at 8am)
class Demo4 : public Demo
{
public:
	std::vector<Vector3> triangle_vertices;
	std::vector<Vector3> plane_vertices;
	std::vector<uint16_t> plane_indices;

	S3D_Mesh sphere;

	void Load(S3D_Renderer* renderer) final
	{
		triangle_vertices.resize(3);
		triangle_vertices[0] = {  0.0f, 0.5f, 0.0f };
		triangle_vertices[1] = { -0.5f, -0.5f, 0.0f };
		triangle_vertices[2] = {  0.5f, -0.5f, 0.0f };

		plane_vertices.resize(4);
		plane_vertices[0] = {  0.75f,  0.75f, 0.0f };	// top-right
		plane_vertices[1] = { -0.75f,  0.75f, 0.0f };	// top-left
		plane_vertices[2] = { -0.75f, -0.75f, 0.0f };	// bottom-left
		plane_vertices[3] = {  0.75f, -0.75f, 0.0f };	// bottom-right

		plane_indices.resize(6);
		plane_indices[0] = 0;
		plane_indices[1] = 1;
		plane_indices[2] = 2;
		plane_indices[3] = 0;
		plane_indices[4] = 2;
		plane_indices[5] = 3;

		S3D_LoadMeshSphere(&sphere);
		TraceLog(LOG_INFO, "RENDER THIS SPHERE!!!");
	}

	void Update(S3D_Renderer* renderer) final
	{
		S3D_ClearColor(renderer, BLACK);
		//S3D_DrawTriangleWireframes(renderer, triangle_vertices[0], triangle_vertices[1], triangle_vertices[2], RED);

		for (size_t i = 0; i < plane_indices.size(); i += 3)
		{
			uint16_t index0 = plane_indices[i + 0];
			uint16_t index1 = plane_indices[i + 1];
			uint16_t index2 = plane_indices[i + 2];

			Vector3 ndc0 = plane_vertices[index0];
			Vector3 ndc1 = plane_vertices[index1];
			Vector3 ndc2 = plane_vertices[index2];

			S3D_DrawTriangleWireframes(renderer, ndc0, ndc1, ndc2, RED);
		}

		// Render the sphere by sampling its index buffer by Thursday the 19th at midnight!
		// Remove junk files from your project, and upload as a .zip (just download your project from GitHub)!
	}
};
