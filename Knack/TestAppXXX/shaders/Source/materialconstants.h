
//--------------------------------------------------------------------------------------
// Material & Texture Information Variables
//--------------------------------------------------------------------------------------

cbuffer TexInfo : register(b1)
{
	matrix mColor					: packoffset(c0);

	float fBumpStrength				: packoffset(c4);
	float fHeightStrength			: packoffset(c4.y);
	float fGlowStrength             : packoffset(c4.z);
	float fSpecularStrength			: packoffset(c4.w);

	float fSpecularSharpness		: packoffset(c5);
	float fDiffuseSharpness			: packoffset(c5.y);
	float fGlowSharpness			: packoffset(c5.z);
	float frTransparency			: packoffset(c5.w);

	float fHazeStrength				: packoffset(c6.x);
	float fFresnel					: packoffset(c6.y);
	float fRefractionRatio			: packoffset(c6.z);
	float frTransparencyEdge		: packoffset(c6.w);

	float3 f3ColorSSS				: packoffset(c7);	
	float  fDummy3				    : packoffset(c7.w);

//	float4 f4SSSBRDFParams			: packoffset(c8);

	float fMaterialThickness		: packoffset(c8.x);
	float fRimScalar			: packoffset(c8.y);
	float fStrengthSSSHighlight		: packoffset(c8.z);
	float fSSSDummy		: packoffset(c8.w);


	uint uImage						: packoffset(c9);
	uint uGlow						: packoffset(c9.y);
	uint uSpecular					: packoffset(c9.z);
	uint uBump						: packoffset(c9.w);
	uint uImageBlack				: packoffset(c10);
	uint uGlowAsImage				: packoffset(c10.y);
	uint uSpecularAsImage			: packoffset(c10.z);
	uint uHeightAsImage				: packoffset(c10.w);
	uint uImageWhite				: packoffset(c11);
	uint uGlowWhite					: packoffset(c11.y);
	uint uSpecularWhite				: packoffset(c11.z);
	uint uHeight					: packoffset(c11.w);
	uint uShadingOn					: packoffset(c12);
	uint uGlowAsAmbient				: packoffset(c12.y);
	uint uChromaKeying				: packoffset(c12.z);
	uint uEnvironment				: packoffset(c12.w);
	uint uPOM						: packoffset(c13);
	uint uPostprocessingFlags		: packoffset(c13.y);
	uint uTexSSS					: packoffset(c13.z);
	uint uReflectionMap				: packoffset(c13.w);
	uint uAni						: packoffset(c14);
	float fPic						: packoffset(c14.y);
	uint uixPics					: packoffset(c14.z);
	uint uiyPics					: packoffset(c14.w);

	uint uiTextureAdressMode		: packoffset(c15.x);
	uint uLightScattering			: packoffset(c15.y);
	float fPOMDistanceMax			: packoffset(c15.z);
	float fHazeDummy2				: packoffset(c15.w);
}

//--------------------------------------------------------------------------------------
// Textur Buffer
// 0=Diffuse, 1=Glow(emissive), 2=Specular, 3=DotBumpMap, 4 = Environmental 5= iPOM 6 = Thickness
//--------------------------------------------------------------------------------------

Texture2D tex2D[7] : register (t15); // texture
