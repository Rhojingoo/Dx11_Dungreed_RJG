#include "ContentShaderBase.hlsli"

struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};


ImageVSOutPut FadeInOut_VS(FEngineVertex _Input)
{
    ImageVSOutPut Out = (ImageVSOutPut) 0;
    Out.POSITION = _Input.POSITION;
    Out.TEXCOORD = _Input.TEXCOORD;
    return Out;
}

struct ImagePSOutPut
{
    float4 COLOR : SV_Target0;
};

TextureSet(Image, 0)


ImagePSOutPut FadeInOut_PS(ImageVSOutPut _Input)
{
    ImagePSOutPut Out = (ImagePSOutPut) 0;
    Out.COLOR.rgba = float4(0.f, 0.f, 0.f, 1.f);
    
    // 텍스처 좌표 가져오기
    float2 uv = _Input.TEXCOORD.xy;

    float upperLimit = 0.20f;
    float lowerLimit = 0.80f;
    //    if (uv.y > upperLimit && uv.y < lowerLimit)
    if (uv.y > upperLimit && uv.y < lowerLimit)
    {
        Out.COLOR.rgba = Image.Sample(Image_Sampler, uv);
    }
    
    if (3 < 0.5f * AccTime)
    {
        Out.COLOR.rgba = Image.Sample(Image_Sampler, _Input.TEXCOORD.xy);
    }
    
    return Out;
}
