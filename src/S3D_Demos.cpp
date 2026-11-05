class Demo
{
public:
	virtual void Load(S3D_Renderer* renderer) {}
	virtual void Unload(S3D_Renderer* renderer) {}

	virtual void Update(S3D_Renderer* renderer) {}
	virtual void Draw(S3D_Renderer* renderer) {}
};

// Screen-space gradient, https://www.shadertoy.com/view/4XcfWl
class Demo1 : public Demo
{
public:
	void Update(S3D_Renderer* renderer) final
	{
		// Hint: you'll need to write a nested for-loop that runs width * height amount of pixels!
		Color color = ColorFromNormalized({ 0.0f, 1.0f, 0.5f, 1.0f });
		S3D_ClearColor(renderer, color);
	}
};

// NDC circle, https://www.shadertoy.com/view/fcfXWj
class Demo2 : public Demo
{
public:
	void Update(S3D_Renderer* renderer) final
	{
		// Hint: you'll need to write a nested for-loop that runs width * height amount of pixels!
		S3D_ClearColor(renderer, GREEN);
	}
};
