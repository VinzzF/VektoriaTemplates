#include "materialconstants.h"
#include "viewportconstants.h"
#include "lightconstants.h"


//--------------------------------------------------------------------------------------
// Copyright (c) Tobias Breiner, Vektoria UG (haftungsbeschränkt)
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Shadow Map Samplers
//--------------------------------------------------------------------------------------

SamplerComparisonState shadowSampler : register(s2);

SamplerState pointSampler : register(s1);

SamplerState linearSampler : register(s0);

//--------------------------------------------------------------------------------------
// Information that are provided by object
// ie: position in world space and lights affecting its surface
//--------------------------------------------------------------------------------------
cbuffer ObjectInfo : register(b0)
{
	matrix mWorld;
	matrix mView;
	matrix mViewInv;
	matrix mProjection;
	vector<uint, 4> iLightsAffecting;
	uint uLights;
}


//--------------------------------------------------------------------------------------
// Light information variables
//--------------------------------------------------------------------------------------

struct SAffectingLight
{
	float fLuminosity;
	float3 f3Direction;
	float4 f4Color;
	float3 f3SpotDirection;
	float fSpotInnerCosAngle;
	float fSpotOuterCosAngle;
	bool bCauseShadow;
	bool bSoftShadow;
	bool bCascadedShadow;
	uint uId;
	uint uType;
	float4 f4LightPos : TEXCOORD0;
};

//--------------------------------------------------------------------------------------

struct VS_INPUT
{
	float4 f4Pos : POSITION;
	float3 f3Normal : NORMAL;
	float2 f2TexCoord : TEXCOORD;
	float3 f3Tangent : TANGENT;
	float3 f3Bitangent : BITANGENT;
};

struct PS_INPUT
{
	float4 f4Pos : SV_POSITION0;
	float3 f3Normal : NORMAL;
	float3 f3Tangent : TANGENT0;
	float3 f3Bitangent : BITANGENT0;
	float2 f2TexCoord : TEXCOORD0;
	float3 f3CamPos : TEXCOORD1;
	float4 f4VertexPos : TEXCOORD2;
	SAffectingLight aafffectinglight[4] : LIGHTS; // Zurzeit können maximal 4 Lichter berrechnet werden
	uint uLights : COUNT;	// Anzahl der Lichter in der Szene
};

//--------------------------------------------------------------------------------------
// Phong Lighting Reflection Model
//--------------------------------------------------------------------------------------
struct DirectionalLight
{
	float4 f4Color;
	float3 f3Dir;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{


	PS_INPUT output = (PS_INPUT)0;

	output.f4Pos = mul(input.f4Pos, mWorld);
	output.f4VertexPos = output.f4Pos; // Speiechere die ursprüngliche Vertex-Position in einer anderen Variablen ab, man wird sie später für die Lichtberechnung im Pixelshader nochmal brauchen
	output.f2TexCoord = input.f2TexCoord; // Reiche die UV-Koordinaten an den Pixelshader weiter!
	matrix mViewProj = mul(mView, mProjection); // Berechne die ViewProjection-Matrix ...
	output.f4Pos = mul(output.f4Pos, mViewProj); // ... und positioniere damit die Vertex-Position 
	output.f3CamPos = mViewInv._41_42_43;

	output.f3Normal = normalize(mul(input.f3Normal, (float3x3)mWorld)); // Multipliziere die Normale des Vertex mit der World-Matrix
	output.f3Tangent = normalize(mul(input.f3Tangent, (float3x3)mWorld)); // Multipliziere die Tangente des Vertex mit der World-Matrix
	output.f3Bitangent = normalize(mul(input.f3Bitangent, (float3x3)mWorld)); // Multipliziere die Biteangente des Vertex mit der World-Matrix

	SLight lightCurrent;
	int lightCurrentId = iLightsAffecting[0]; // Wir gehen vereinfachend davon aus: Es gäbe nur ein Parallellicht
	lightCurrent = Lights[lightCurrentId];
	output.aafffectinglight[0].f3Direction = normalize(lightCurrent.f3Direction);  // die Lichtrichtung f3Direction muss normalisiert werden 
	output.aafffectinglight[0].fLuminosity = 1; // Vereinfachend: Stärke des Lichtes gleich 1 



	/*

	output.f4Pos = mul(input.f4Pos, mWorld);
	output.f4VertexPos = output.f4Pos; // Speiechere die ursprüngliche Vertex-Position in einer anderen Variablen ab, man wird sie später für die Lichtberechnung im Pixelshader nochmal brauchen
	output.f2TexCoord = input.f2TexCoord; // Reiche die UV-Koordinaten an den Pixelshader weiter!
	matrix mViewProj = mul(mView, mProjection); // Berechne die ViewProjection-Matrix ...
	output.f4Pos = mul(output.f4Pos, mViewProj); // ... und positioniere damit die Vertex-Position 

	output.f3CamPos = mViewInv._41_42_43; 

	output.f3Normal = normalize(mul(input.f3Normal, (float3x3)mWorld)); // Multipliziere die Normale des Vertex mit der World-Matrix
	output.f3Tangent = normalize(mul(input.f3Tangent, (float3x3)mWorld)); // Multipliziere die Tangente des Vertex mit der World-Matrix
	output.f3Bitangent = normalize(mul(input.f3Bitangent, (float3x3)mWorld)); // Multipliziere die Biteangente des Vertex mit der World-Matrix

	SLight lightCurrent;
	int lightCurrentId = iLightsAffecting[0]; // Wir gehen vereinfachend davon aus: Es gäbe nur ein Parallellicht
	lightCurrent = Lights[lightCurrentId];
	output.aafffectinglight[0].f3Direction = normalize(lightCurrent.f3Direction);  // die Lichtrichtung f3Direction muss normalisiert werden 
	output.aafffectinglight[0].fLuminosity = 1; // Vereinfachend: Stärke des Lichtes gleich 1 

	*/
	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
	float4 f4ColorOut;
	f4ColorOut.rgb = 0;


	float fShading = saturate(dot(-input.aafffectinglight[0].f3Direction, input.f3Normal));

	f4ColorOut = tex2D[0].Sample(linearSampler, input.f2TexCoord)*fShading;

		f4ColorOut.w = 1;


	/*
	if (uBump)  // Ist Bumpmapping dabei?
	{
		float3 f3BumpNormal = ((2 * (tex2D[3].Sample(linearSampler, input.f2TexCoord))) - 1.0).xyz; // Hole Pixelfarbe und berechne daraus den Beugungsvektor
		f3BumpNormal *= fBumpStrength; // Gewichte Beugungsvektor mit der gewünschten Bumpmapping-Stärke
		input.f3Normal = f3BumpNormal.r*input.f3Tangent + f3BumpNormal.g*input.f3Bitangent + f3BumpNormal.b*input.f3Normal; // Berechne aus dem Beugungsvektor die neue Oberflächennormale 
		input.f3Normal = normalize(input.f3Normal); // Normalisiere zur Sicherheit die Oberflächennormale (es könnte ja sein, dass die Bumpmap falsche Werte hat)
	}


	float fShading = saturate(dot(-input.aafffectinglight[0].f3Direction, input.f3Normal)); // Berechne, wie "zugewandt" die Oberflächennormale zum Licht ist

	float4 f4ColorOut = tex2D[0].Sample(linearSampler, input.f2TexCoord)*fShading; // Hole Pixelfarbe und berechne daraus den Beugungsvektor
	f4ColorOut.a = 1;

	float fSpecular;
	float3 f3EyeVector = normalize(input.f3CamPos - input.f4VertexPos.xyz); // Berechne die Blickrichtung!
	float4 f4Specular = 0; // Setze die Spekulare Textur auf schwarz!
	if (uSpecular) // Gibt es eine spekulare Textur? 
	{
		float3 f3Half = normalize(-input.aafffectinglight[0].f3Direction + f3EyeVector);
		fSpecular = pow(saturate(dot(input.f3Normal, f3Half)), fSpecularSharpness); // Empirische Formel
		f4Specular.rgb = fSpecular;
	}
	f4ColorOut.rgb *= f4Specular.rgb + float3(1,1,1);
	*/

	/*
	float fSpecular = 0;
	// Berechne Entfernung zwischen Kamera und Vertex:
	float3 f3Distance = input.f3CamPos - input.f4VertexPos.xyz; // Berechne den Entfernungvektor zwischen der Kamera und der Vertex-Position
		float fDistance = length(f3Distance); // Speichere den Betrag (=Länge) des Vektors

	float3 f3EyeVector = normalize(input.f3CamPos - input.f4VertexPos.xyz); // Berechne die Blickrichtung!

		float4 f4ColorOut; // Ausgangsfarbe des Pixels
	f4ColorOut.xyzw = 0; // Setze Ausgangsfarbe auf schwarz
	float2 f2ParallaxTex = input.f2TexCoord; // UV-Koordinaten
	if (uBump)  // Ist Bumpmapping dabei?
	{
		float3 f3BumpNormal = ((2 * (tex2D[3].Sample(linearSampler, f2ParallaxTex))) - 1.0).xyz; // Hole Pixelfarbe und berechne daraus den Beugungsvektor
			f3BumpNormal *= fBumpStrength; // Gewichte Beugungsvektor mit der gewünschten Bumpmapping-Stärke
		input.f3Normal = f3BumpNormal.r*input.f3Tangent + f3BumpNormal.g*input.f3Bitangent + f3BumpNormal.b*input.f3Normal; // Berechne aus dem Beugungsvektor die neue Oberflächennormale 
		input.f3Normal = normalize(input.f3Normal); // Normalisiere zur Sicherheit die Oberflächennormale (es könnte ja sein, dass die Bumpmap falsche Werte hat)
	}
	float fShading = saturate(dot(-input.aafffectinglight[0].f3Direction, input.f3Normal)); // Berechne, wie "zugewandt" die Oberflächennormale zum Licht ist
	float4 f4ColGlow;
	f4ColGlow.rgba = 0;
	if (uGlow)// Ist Glowmapping dabei?
	{
		f4ColGlow = tex2D[1].Sample(linearSampler, f2ParallaxTex)*(1 - fShading); // ´(1-fShading) ist die "Licht-Abgewandtheit", gewichte damit die Glow-Map!
	}
	float4 f4Specular;
	f4Specular.rgba = 0; // Setze die Spekulare Textur auf schwarz!
	if (uSpecular) // Gibt es eine spekulare Textur? 
	{
		float3 f3Half = normalize(-input.aafffectinglight[0].f3Direction + f3EyeVector);
			fSpecular = pow(saturate(dot(normalize(input.f3Normal), f3Half)), fSpecularSharpness); // Empirische Formel
		f4Specular.rgb = fSpecular;
	}

	f4ColorOut = tex2D[0].Sample(linearSampler, f2ParallaxTex);
	f4ColorOut.rgb = fShading*f4ColorOut.rgb + f4ColGlow.rgb + f4Specular.rgb; // Addiere sinnfällig die spekulare, die glow-mäßige und die diffusen Textur!
	*/
	/* 
	// Goldshader
	f4ColorOut.r *= 2;
	f4ColorOut.g *= 1.5;
	*/
	/*
	// Nachtsichtgerät
	f4ColorOut.g = 1.0f - 2*f4ColorOut.r-fDistance*0.002;
	f4ColorOut.rb = 0;
	*/

	/*
	// Entfernungslaser zum Debuggen:
	if (fDistance > 100 && fDistance < 101)
		f4ColorOut.r = 1.0f;
		*/
	/*
	// Usprungslaser zum Debuggen:
	float fLen = length(input.f4VertexPos);
	if (fLen > 100 && fLen < 101)
		f4ColorOut.b = 1.0f;
	if (fLen > 0 && fLen < 5)
		f4ColorOut.r = 1.0f;
	*/

	/*
	// Schneeshader
	if (input.f3Normal.y > 0.3f)
		f4ColorOut.rgb += (input.f3Normal.y - 0.3)*1.5f;
	f4ColorOut.rgb += fDistance*0.001;
	*/

	/*
	int4 i4Toon = (int4)(f4ColorOut * 3);
	f4ColorOut = ((float4)i4Toon)/3.0f;
	*/
	return f4ColorOut; // Gib die Ausgangspixelfarbe aus!
}













/*
// Nebelshader:
f4ColorOut.rgb += fDistance*0.05f;
*/

/*
f4ColorOut.r *= 2.5f;
f4ColorOut.g *= 2.0f;
*/
/*
// Nachtsichtgerät:
f4ColorOut.rb = 0.0f;
f4ColorOut.g = f4ColorOut.y * 2.0f;
*/
/*
// Rauchshader:
f4ColorOut.rgb -= fDistance*0.002f;
*/
/*
// Toon-Stufen:
int4 i4ColorOut = (int4)(f4ColorOut * 3);
f4ColorOut = (float4)i4ColorOut;
f4ColorOut /= 3.0f;
*/

/*
f4ColorOut.r *= 5.0f;
f4ColorOut.g *= 3.0f;
f4ColorOut.b *= 0.8f;
*/




/* Blaudunstshader:
f4ColorOut.b *= 1.0f+fDistance*0.005;
f4ColorOut.g *= 1.0f + fDistance*0.003;
f4ColorOut.r *= 1.0f + fDistance*0.001;
*/

/*
// Entfernungslaser:
if (fDistance>50 && fDistance < 50.3)
f4ColorOut.r = 1.0f;
*/
/*
// Schneeshader:
if (input.f3Normal.y>0.3)
f4ColorOut.rgb += 2 * (input.f3Normal.y - 0.3f);
*/

/*
float3 f3Hilf = input.f3CamPos - (float3)input.f4VertexPos;
f4ColorOut.z = length(f3Hilf)*0.0002;
f4ColorOut.xy = 1 - f4ColorOut.z;
f4ColorOut = saturate(f4ColorOut); // Beschneide die Ausgangspixelfarbe, die Pixelwerte dürfen nur zwischen 0.0 und 1.0 liegen

*/

/*
// Ursprungssuchlaser
float fHilf = length((float3)input.f4VertexPos);
if (fHilf > 100 && fHilf < 110)
f4ColorOut.b = 1;
if (fHilf > 10 && fHilf < 11)
f4ColorOut.r = 1;

*/

/*
float fLen = length(input.f3CamPos - (float3)input.f4VertexPos)*0.002;
f4ColorOut.rg += fLen;
f4ColorOut.b += fLen*1.2f;
*/

// f4ColorOut.r = fBumpStrength;



/*
f4ColorOut.r *= 3.0f;
f4ColorOut.g *= 2.0f;
f4ColorOut.b *= 0.8f;
*/


/*
// Toon-Stufen:
int4 i4ColorOut = (int4)(f4ColorOut * 3);
f4ColorOut = (float4)i4ColorOut;
f4ColorOut /= 3.0f;
*/
