
void S3D_DrawTriangleWireframes(S3D_Renderer* renderer, Vector3 ndc0, Vector3 ndc1, Vector3 ndc2, Color color0, Color color1 = BLANK, Color color2 = BLANK)
{
	Vector2i v0 = S3D_NDCToScreen(renderer, ndc0);
	Vector2i v1 = S3D_NDCToScreen(renderer, ndc1);
	Vector2i v2 = S3D_NDCToScreen(renderer, ndc2);

	S3D_DrawLine(renderer, v0.x, v0.y, v1.x, v1.y, color0);
	S3D_DrawLine(renderer, v1.x, v1.y, v2.x, v2.y, color0);
	S3D_DrawLine(renderer, v2.x, v2.y, v0.x, v0.y, color0);
}

void S3D_DrawMeshWireframes(S3D_Renderer* renderer, const S3D_Mesh& mesh, Matrix mvp, Color color)
{
	
}

void S3D_DrawMeshWireframesColor(S3D_Renderer* renderer, const S3D_Mesh& mesh, Matrix mvp, const std::vector<Color>& colors)
{
	
}

void S3D_DrawMesh(S3D_Renderer* renderer, const S3D_Mesh& mesh, S3D_UniformData uniform, S3D_FragmentShader shader)
{	
	
}
