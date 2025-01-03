struct VertexInput {
  float4 position : POSITION0;   // 정점 위치 "position"이라는 변수가 "POSITION0" 스트림의 위치에 대한 정보를 저장한다
  float2 uv : TEXCOORD0;         // 정점 색상
};

struct PixelInput {
  float4 position : SV_POSITION0;  // 픽셀 위치  픽셀의 위치를 나타내는 시스템
                                   // 값을 의미 ( SV = System Value )
  float2 uv : TEXCOORD0;  // 픽셀 색상
};




cbuffer WorldBuffer : register(b0) { matrix _world; }


cbuffer VPbuffer : register(b1) {
  matrix _view;
  matrix _projection;
}

cbuffer ProgressBuffer : register(b2)
{
    float _percent;
    uint _type;
}





PixelInput VS(VertexInput input) { 
  PixelInput output;

  output.position = mul(input.position, _world);           // 정점 위치에 월드 행렬을 곱함
  output.position = mul(output.position, _view);           // 결과에 뷰 행렬을 곱함
  output.position = mul(output.position, _projection);     // 결과에 프로젝션 행렬을 곱함

  output.uv = input.uv;
  return output;
}

Texture2D _sourceTex : register(t0);  
SamplerState _samp : register(s0);    

/*
0 = NONE
1 = LEFT TO RIGHT
2 = RIGHT TO LEFT
3 = UP TO DOWN
4 = DOWN TO UP
*/

float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp, (float2) input.uv);
    float4 zero = float4(0, 0, 0, 0);
    
    switch (_type)
    {
        case 1:{
                if (input.uv.x <= _percent)
                    return color;
                else
                    return zero;
            }
        case 2:{
                if (input.uv.x >= _percent)
                    return color;
                else
                    return zero;
            }
        case 3:{
                if (input.uv.y <= _percent)
                    return color;
                else
                    return zero;
            }
        case 4:{
                if (input.uv.y >= _percent)
                    return color;
                else
                    return zero;
            }
    }
    return color;
}
