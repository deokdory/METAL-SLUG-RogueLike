struct VertexInput {
  float4 position : POSITION0;   // ���� ��ġ "position"�̶�� ������ "POSITION0" ��Ʈ���� ��ġ�� ���� ������ �����Ѵ�
  float2 uv : TEXCOORD0;         // ���� ����
};

struct PixelInput {
  float4 position : SV_POSITION0;  // �ȼ� ��ġ  �ȼ��� ��ġ�� ��Ÿ���� �ý���
                                   // ���� �ǹ� ( SV = System Value )
  float2 uv : TEXCOORD0;  // �ȼ� ����
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

  output.position = mul(input.position, _world);           // ���� ��ġ�� ���� ����� ����
  output.position = mul(output.position, _view);           // ����� �� ����� ����
  output.position = mul(output.position, _projection);     // ����� �������� ����� ����

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
