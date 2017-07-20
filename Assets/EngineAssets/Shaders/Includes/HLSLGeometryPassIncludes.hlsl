//HLSLGeometryPassIncludes.h
//Created 20/07/17
//Created By Daniel Bowler
//
//Globals for GeometryPass HLSL shaders - All shaders
//will include this as it will contain the vital code
//to pack the GBuffer with data and the like. 

//
//Defines
//
#define SPEC_POWER_RANGE_MIN 10.0f
#define SPEC_POWER_RANGE_MAX 250.0f

//
//Engine provided CBuffers
//

//
//Output from geometry pas pixel shaders - GBuffer format
//
struct GeometryPassPackedGBufferPSOutput
{
    float4 ColourSpecInt : SV_TARGET0;
    float4 NormalW       : SV_TARGET1;
    float4 SpecPower     : SV_TARGET2;
};

//
//VS Helper functions
//

float4 LocalPositionToWorldSpace(float3 local, float4x4 world)
{
    return mul(float4(local, 1.0f), world);
}

float4 LocalPositionToClipSpace(float3 local, float4x4 world, float4x4 viewProj)
{
    float4 w = mul(float4(local, 1.0f), world);
    return (mul(w, viewProj));
}

float4 LocalPositionToClipSpace(float3 local, float4x4 wvp)
{
    return (mul(float4(local, 1.0f), wvp));
}

float4 WorldPositionToClipSpace(float4 world, float4x4 viewProj)
{
    return (mul(world, viewProj));
}

float3 LocalNormalToWorldSpace(float3 localNormal, float4x4 world)
{
    return (mul(localNormal, (float3x3) world));
}

float3 LocalNormalToWorldSpace(float3 localNormal, float3x3 world)
{
    return (mul(localNormal, world));
}

//
//PS Helper functions
//

GeometryPassPackedGBufferPSOutput PackGBuffer(float3 diffuse, float3 normalW,
	float specularIntensity, float specPower)
{
    //Packs the GBuffer to be returned from the 
    //geometry pass pixel shaders
    //
    //Normalize specular power [0.0f,1.0f]
    float specPowerNormalized = max(0.0001, (specPower - SPEC_POWER_RANGE_MIN) / SPEC_POWER_RANGE_MAX);

    //Fill GBuffer for this pixel.
    GeometryPassPackedGBufferPSOutput o;
    o.ColourSpecInt = float4(diffuse.rgb, specularIntensity);
    o.NormalW = float4((normalW.xyz * 0.5f + 0.5f), 0.0f); //[0-1] range (.w ignored) -> Assumes normal has been normalized prior to calling function
    o.SpecPower = float4(specPowerNormalized, 0.0f, 0.0f, 0.0f);

    //Return the filled GBuffer
    return o;
}