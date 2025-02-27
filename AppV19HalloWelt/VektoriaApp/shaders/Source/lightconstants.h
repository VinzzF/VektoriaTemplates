//--------------------------------------------------------------------------------------
// Autor: Tobias Breiner
// Light information variables
//--------------------------------------------------------------------------------------
struct SLight
{
	float3 f3Position;				// all lights
	uint uType;						// all lights
	float4 f4Color;					// all lights
	float3 f3Direction;				// directional light, spot light
	float fInnerCosAngle;			// spot light
	float fOuterCosAngle;			// spot light
	float fAttenuationConstant;		// point light, spot light
	float fAttenuationLinear;		// point light, spot light
	float fAttenuationQuadratic;	// point light, spot light
	bool bCauseShadow;
	bool bSoftShadow;
	bool bCone;
	float frShadowStrength;
	float4x4 mLightViewProj;
};

StructuredBuffer<SLight> Lights : register (t10);

Texture2D shadowMap : register (t11);
