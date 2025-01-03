struct VertexInput {
  float4 position : POSITION0;   // ���� ��ġ "position"�̶�� ������ "POSITION0" ��Ʈ���� ��ġ�� ���� ������ �����Ѵ�
  float2 uv : TEXCOORD0;         // ���� ����
};

struct PixelInput {
  float4 position : SV_POSITION0;  // �ȼ� ��ġ  �ȼ��� ��ġ�� ��Ÿ���� �ý���
                                   // ���� �ǹ� ( SV = System Value )
  float2 uv : TEXCOORD0;  // �ȼ� ����
};

// cbuffer : constance buffer ��� ���� ��������
// ��� ���� �������� b0�� �Ҵ�� ���� ����� �����ϴ� ��� ����
// 0 ~ 127
cbuffer WorldBuffer : register(b0) { matrix _world; }

// ��� ���� �������� b1�� �Ҵ�� ��, �������� ����� �����ϴ� ��� ����
cbuffer VPbuffer : register(b1) {
  matrix _view;
  matrix _projection;
}

// ���� ���̴� �Լ�
// �Է����� VertexInput�� �ް� PixelInput ����ü�� ��ȯ
// VS�� EntryName
PixelInput VS(VertexInput input) { 
  PixelInput output;

  output.position = mul(input.position, _world);           // ���� ��ġ�� ���� ����� ����
  output.position = mul(output.position, _view);           // ����� �� ����� ����
  output.position = mul(output.position, _projection);     // ����� �������� ����� ����

  output.uv = input.uv;
  return output;
}

Texture2D _sourceTex : register(t0);  // �ؽ��� �����͸� ����
SamplerState _samp : register(s0);    // ���ø��ϴ� ��� ����

// �ȼ� ���̴� �Լ�
// �Է����� PixelInput ����ü�� �ް� float4 ������ �ȼ� ������ ��ȯ
float4 PS(PixelInput input) : SV_Target {
  float4 color = _sourceTex.Sample(_samp, (float2)input.uv);
    float3 grayScale = 0;
    
    // Line
    {
        if (input.uv.x < .01f || input.uv.x > .99f || input.uv.x < .01f || input.uv.y > .99f)
            return float4(1, 1, 1, 1);

        if (input.uv.x < 0.505f && input.uv.x > .495f)
            return float4(1, 1, 1, 1);
        
        if (input.uv.y < .505f && input.uv.y > .495f)
            return float4(1, 1, 1, 1);
    }
    
   {
        if (input.uv.x < .5f && input.uv.y < .5f)
        {
            color = _sourceTex.Sample(_samp, float2(input.uv.x * 2.0f, input.uv.y * 2.0f));
            grayScale = dot(color.rgb, float3(.299f, .587f, .114f));
            
            color = float4(grayScale, 1);
        }
        else if (input.uv.x >= .5f && input.uv.y < .5f)
        {
            color = _sourceTex.Sample(_samp, float2((input.uv.x - .5f) * 2.f, input.uv.y * 2.f));
            
            float r, g, b;
            r = dot(color.rgb, float3(.393f, .769f, .189f));
            g = dot(color.rgb, float3(.393f, .686f, .168f));
            b = dot(color.rgb, float3(.272f, .534f, .131f));
            
            grayScale = float3(r, g, b);
            color = float4(grayScale, 1);
        }
        else if (input.uv.x < .5f && input.uv.y >= .5f)
        {
            color = _sourceTex.Sample(_samp, float2(input.uv.x * 2.f, (input.uv.y - .5f) * 2.f));
        }
        else if (input.uv.x >= .5f && input.uv.y >= .5f)
        {
            color = _sourceTex.Sample(_samp, float2((input.uv.x - .5f) * 2.f, (input.uv.y - .5f) * 2.f));

        }

    }
    
  return color;
}
/*
Semantic ����ƽ
- HLSL ���̴����� �������� �ǹ̸� �����ϴµ� ���
- ���̴��� �Է� �����Ϳ� ��� �����͸� �ùٸ��� �ؼ��ϰ� ó���� �� �ֵ��� ����
- ���� �̸� �ڿ� ':' ��ȣ�� �Բ� ����
- �ý��� �� ����ƽ�� 'SV_' ���λ�� �����ϸ� Direct3D���� ���ǵ� Ư���� �ǹ̸� ����
- �ý��� �� ����ƽ�� ���̴� �������� ���� �����͸� �����ϴµ� ���

slot
- GPU ���� ����ϴ� ��� ����, �ؽ���, ���÷� ���� �ڿ����� �ĺ��ϴ� �ε���
- �� ������ ������ ��ȣ�� ������, �ش� �ڿ��� ������ ���ҿ� ���� �ٸ��� �Ҵ��
- register��� Ű���带 ����Ͽ� ����
- �� �ڿ��� � ���Կ� �Ҵ�� ������ ��������� ������ �� ����

- �ֿ� ����
  1) ��� ���� ����
  - ��� �����͸� �����ϴµ� ���, VS�� PS���� ������ �� �ִ�
  - ��� ���� ������ register(b#)�� ����Ͽ� ����

  2) �ؽ��� ����
  - �̹��� �����͸� �����ϴµ� ���
  - �ؽ��� ���� ������ register(t#)�� ����Ͽ� ����

  3) ���÷� ����
  - �ؽ��ĸ� ���ø��ϴ� �� ���
  - ���÷� ������ register(s#)�� ����Ͽ� ����

cbuffer = Constance Buffer : ��� ����
- ���̴����� ����ϴ� ���� ������ �����ϴµ� ���
- �� ��� ���� �������Ϳ��� �� ���� ��� ���۸� �Ҵ��� �� ����
- ��� ���� ���ο��� ���� ���� ������ ������ �� �ִ�.

Sampler : ���÷�
- �ؽ��Ŀ��� �ȼ� ���� �������� ����� �����ϴ� ��ü
- �ؽ��� ���ø��� �ؽ��� �̹����� ���� �ؼ� ���� ����ϴ� �۾�
(�ؼ� : �ؽ����� �ȼ� ��)
*/