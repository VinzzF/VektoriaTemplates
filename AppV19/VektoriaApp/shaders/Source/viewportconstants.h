//--------------------------------------------------------------------------------------
// Viewport information variables
//--------------------------------------------------------------------------------------



cbuffer ViewportArt : register(b2)
{
	float4 f4SceneColorAmbient		: packoffset(c0);
	float4 f4FogParams				: packoffset(c1);

	uint uPostprocessing			: packoffset(c2.x);
	uint uStyleFog					: packoffset(c2.y);
	uint uStyleSnow					: packoffset(c2.z);
	float fFarClipping				: packoffset(c2.w);
	float fMistStartDistance			: packoffset(c3.x);
}
